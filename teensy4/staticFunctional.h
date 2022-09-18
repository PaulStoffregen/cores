/**
 * Based on code found here:
 * https://www.c-plusplus.net/forum/topic/344451/std-function-und-std-bind-durch-einfachere-eigene-variante-ersetzen-signal-slot/17
 *
 **/

// as usual, Arduino macros clash with the standard library
#pragma push_macro("F")
#undef F
#pragma push_macro("min")
#undef min
#pragma push_macro("max")
#undef max

#include <memory>
#include <type_traits>

namespace staticFunctional
{

// we need to supply some utilities for toolchains < c++17
#if (__cplusplus <= 201402L)

    // std::launder ==================================================
    template <typename _Tp>
    [[nodiscard]] constexpr _Tp*
    launder(_Tp* __p) noexcept
    {
        return __builtin_launder(__p);
    }

    // The program is ill-formed if T is a function type or
    // (possibly cv-qualified) void.
    template <typename _Ret, typename... _Args>
    void launder(_Ret (*)(_Args...)) = delete;

    template <typename _Ret, typename... _Args>
    void launder(_Ret (*)(_Args......)) = delete;

    void launder(void*)                = delete;
    void launder(const void*)          = delete;
    void launder(volatile void*)       = delete;
    void launder(const volatile void*) = delete;

    // invoke_result_t ==================================================
    template <typename F, typename... a>
    using invoke_result_t = typename std::__invoke_result<F, a...>::type;

    // decay_t ==========================================================
    template <typename F>
    using decay_t = typename std::decay<F>::type;

#else // resort to the standard versions for >= c++17
    using std::decay_t;
    using std::invoke_result_t;
    using std::launder;
#endif

    template <typename Signature, std::size_t N = 16>
    class function;

    template <typename R, typename... Args, std::size_t N>
    class function<R(Args...), N>
    {
        struct InvokerBase
        {
            virtual R operator()(void const*, Args...) const   = 0;
            virtual void destroy(void*)                        = 0;
            virtual void copy(void const*, void*, void*) const = 0;
            virtual void move(void*, void*, void*) const       = 0;
        };

        template <typename F>
        struct Invoker : InvokerBase
        {
            static_assert(sizeof(F) <= N, "memory error");

            R operator()(void const* p, Args... args) const override
            {
                return (*(F const*)p)(std::forward<Args>(args)...);
            }
            void destroy(void* p) override
            {
                launder((F*)p)->~F();
            }
            void copy(void const* s, void* d, void* invoker_d) const override
            {
                new (d) F(*launder((F const*)s));
                new (invoker_d) Invoker;
            }
            void move(void* s, void* d, void* invoker_d) const override
            {
                new (d) F(std::move(*launder((F*)s)));
                new (invoker_d) Invoker;
            }
        };

        typename std::aligned_storage<N>::type _storage;
        typename std::aligned_storage<sizeof(Invoker<char>), alignof(Invoker<char>)>::type _invoker_storage;

        InvokerBase const& _invoker_base() const noexcept
        {
            return *launder((InvokerBase*)&_invoker_storage);
        }
        InvokerBase& _invoker_base() noexcept
        {
            return *launder((InvokerBase*)&_invoker_storage);
        }
        bool _empty = true;

        void _clear()
        {
            if (!empty())
            {
                _invoker_base().destroy(&_storage);
                _empty = true;
            }
        }

        template <typename F>
        struct _is_callable
        {
            // static const bool value = std::is_convertible<invoke_result_t<decay_t<F>, Args...>, R>::value;
            static const bool value = true; // hack, need to fix that...
        };

        template <typename F>
        struct _participate
        {
            static const bool value = _is_callable<decay_t<F>>::value && !std::is_same<decay_t<F>, function>::value;
        };

        template <typename>
        struct _is_function_spec : std::false_type
        {
        };
        template <typename X, std::size_t M>
        struct _is_function_spec<function<X, M>> : std::true_type
        {
        };

        // template <typename F>
        // void _emplace(F f)
        // {
        //     using T = decay_t<F>;
        //     if constexpr (std::is_pointer<T>::value || std::is_member_function_pointer<T>::value || _is_function_spec<T>{})
        //         if (!f)
        //             return;

        //     static_assert(sizeof(Invoker<F>) <= sizeof(_invoker_storage), "Memory");
        //     new (&_storage) F(std::move(f));
        //     new (&_invoker_storage) Invoker<F>;
        //     _empty = false;
        // }
        // ....................................................................................
        // original _emplace uses "constexpr if" which does not exist in c++11 -> replace by SFINAE version

        template <typename F>
        typename std::enable_if<std::is_pointer<decay_t<F>>::value || std::is_member_function_pointer<decay_t<F>>::value || _is_function_spec<decay_t<F>>{}, void>::type
        _emplace(F f)
        {
            if (!f) return;

            static_assert(sizeof(Invoker<F>) <= sizeof(_invoker_storage), "Memory");
            new (&_storage) F(std::move(f));
            new (&_invoker_storage) Invoker<F>;
            _empty = false;
        }

        template <typename F>
        typename std::enable_if<!(std::is_pointer<decay_t<F>>::value || std::is_member_function_pointer<decay_t<F>>::value || _is_function_spec<decay_t<F>>{}), void>::type
        _emplace(F f)
        {
            static_assert(sizeof(Invoker<F>) <= sizeof(_invoker_storage), "Memory");
            new (&_storage) F(std::move(f));
            new (&_invoker_storage) Invoker<F>;
            _empty = false;
        }

     public:
        using result_type = R;

        function() noexcept = default;
        function(std::nullptr_t) noexcept {}

        function(function&& other) : _empty(other.empty())
        {
            if (!empty())
                other._invoker_base().move(&other._storage, &_storage, &_invoker_storage);
        }

        function(function const& other) : _empty(other.empty())
        {
            if (!empty())
                other._invoker_base().copy(&other._storage, &_storage, &_invoker_storage);
        }

        template <typename F, typename = typename std::enable_if<_participate<F>::value>::type>
        function(F&& f) : _empty(false)
        {
            _emplace(std::forward<F>(f));
        }

        ~function()
        {
            _clear();
        }

        bool empty() const noexcept { return _empty; }
        operator bool() const noexcept { return !empty(); }

        function& operator=(function const& other)
        {
            _clear();
            _empty = other.empty();
            if (!empty())
                other._invoker_base().copy(&other._storage, &_storage, &_invoker_storage);
            return *this;
        }

        function& operator=(function&& other)
        {
            _clear();
            _empty = other.empty();
            if (!empty())
                other._invoker_base().move(&other._storage, &_storage, &_invoker_storage);
            return *this;
        }

        function& operator=(std::nullptr_t)
        {
            _clear();
            return *this;
        }

        template <typename F, typename = typename std::enable_if<_participate<F>::value>::type>
        function& operator=(F&& f)
        {
            _clear();
            _emplace(std::forward<F>(f));
            return *this;
        }

        template <typename F>
        function& operator=(std::reference_wrapper<F> f)
        {
            _clear();
            _emplace(f.get());
            return *this;
        }

        void swap(function& other)
        {
            std::swap(*this, other); // Best that can be done.
        }

        R operator()(Args... args) const
        {
            return _invoker_base()(&_storage, std::forward<Args>(args)...);
        }
    };

    template <typename R, typename... Args, std::size_t N>
    bool operator==(function<R(Args...), N> const& f, std::nullptr_t) noexcept
    {
        return !f;
    }
    template <typename R, typename... Args, std::size_t N>
    bool operator==(std::nullptr_t, function<R(Args...), N> const& f) noexcept
    {
        return !f;
    }
    template <typename R, typename... Args, std::size_t N>
    bool operator!=(function<R(Args...), N> const& f, std::nullptr_t) noexcept
    {
        return f;
    }
    template <typename R, typename... Args, std::size_t N>
    bool operator!=(std::nullptr_t, function<R(Args...), N> const& f) noexcept
    {
        return f;
    }

    template <typename R, typename... Args, std::size_t N>
    void swap(function<R(Args...), N>& lhs, function<R(Args...), N>& rhs)
    {
        lhs.swap(rhs);
    }
}
#pragma pop_macro("max")
#pragma pop_macro("min")
#pragma pop_macro("F")
