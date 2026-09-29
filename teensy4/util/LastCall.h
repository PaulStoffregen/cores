
#ifdef __cplusplus

#ifndef lastCall_h_
#define lastCall_h_

//#include <WProgram.h>   //for debug prints

#include <arm_math.h>
#include <array>
#include <numeric>
#include <functional>

struct QR {
  uint32_t q;
  int32_t  r;
};

template <uint32_t N>
static inline __attribute__((always_inline)) QR getQR(uint32_t d){
    QR qr;
    qr.q = d / N;
    qr.r = int32_t(d -qr.q* N);
    return qr;
}

template <uint32_t N>
static inline __attribute__((always_inline)) void subtract(const QR& q0, const QR& q1, QR& res){
    res.q = q0.q - q1.q;
    res.r = q0.r - q1.r;
    constexpr int32_t NSigned=int32_t(N);
    if (res.r < 0) {
        res.r += NSigned;
        res.q--;
    }
}

template <uint32_t N>
static inline __attribute__((always_inline)) void add(const QR& q0, const QR& q1, QR& res){
    res.q = q0.q + q1.q;
    res.r = q0.r + q1.r;
    constexpr int32_t NSigned=int32_t(N);
    if (res.r >=NSigned) {
        res.r -= NSigned;
        res.q++;
    }
}

//This class is used to estimate last call of a function that is called at a high frequency.
//It smoothes the time of the last call by means of history buffer that stores the time of the e.g. last 7 calls.
//Important: The class detects up to two outliers in the history and ignores them at the computation of the time of the last call
template <uint32_t HL>
struct History{
    std::array<uint32_t,HL> data;
    std::array<QR,HL> dataQR;
    std::array<int8_t,HL> state;   //-1...not set yet (after reset), 0...default, 1...evaluated
    std::array<uint32_t,HL> errors;            
    std::array<int32_t, HL> sortedIdx;

    QR com;
    uint32_t comOffset;
    bool valid=false;
    int32_t currentWriteIndex=0;
};
inline double toInt32Range(double x){
	constexpr double pow2_32 = double(UINT32_MAX)+1.;
	constexpr double pow2_31 = 0.5*pow2_32;
	if (x < -pow2_31){
		x += pow2_32;
	}
	if (x > pow2_31){
		x -= pow2_32;
	}
	return x;
}
template <int32_t N>
static inline __attribute__((always_inline)) int32_t increment(int32_t n){
    return (n == N-1) ? 0 : (n + 1);
}
template <int32_t N>
static inline __attribute__((always_inline)) int32_t decrement(int32_t n){
    return (n == 0) ? (N - 1) : (n - 1);
}

template <uint32_t N>
class LastCall
{
    public:
        LastCall() {
            resetHistory();
        }

        void updateExpectedTimeStep(double expectedTimeStep, bool setBoundary=true) { 
            if (setBoundary){
                _boundaryFraction= uint32_t(UINT32_MAX- (3.*expectedTimeStep*N))/N; //3. is the safety factor
                _boundary= _boundaryFraction*N;  //boundary % N ==0 is handy because we then don't need to update the reminders
            }
            //make the perfect sequence
            _comPerfect.q=0;
            _comPerfect.r=0;
            for (uint32_t i =0; i< N; i++){
                _dataPerfect[i] = uint32_t(i*expectedTimeStep+0.5);
                _dataPerfectQR[i] = getQR<N>(_dataPerfect[i]);
                add<N>(_comPerfect, _dataPerfectQR[i], _comPerfect);
            }
        }
        void resetHistory() {
            memset(_history.data.data(), 0, _history.data.size()*sizeof(_history.data[0]));
            QR qr;
            qr.q=0;
            qr.r=0;
            std::fill(_history.dataQR.begin(), _history.dataQR.end(), qr);            
            std::fill(_history.state.begin(), _history.state.end(), -1);            
            std::fill(_history.sortedIdx.begin(), _history.sortedIdx.end(), -1);

            _history.com.q=0;
            _history.com.r=0;
            _history.comOffset = 0;
            _history.valid=false;
            _history.currentWriteIndex=0;
        }
        void reset(double expectedTimeStep){
            updateExpectedTimeStep(expectedTimeStep);
            resetHistory();            
        }
        
        void addCall(uint32_t time){
            constexpr int32_t NSIGNED = int32_t(N);

            time -= _history.comOffset;
            int32_t& w=_history.currentWriteIndex;
            // Remember old oldest before overwriting
            const uint32_t oldOldest = _history.data[w];
            
            //remove the contribution of the old data point
            QR& dataQr=_history.dataQR[w];
            subtract<N>(_history.com, dataQr, _history.com);
            _history.state[w] = 0;               
            //==============================================
            dataQr = getQR<N>(time);
            _history.data[w]=time;

            if(!_history.valid){
                //we make sure that from the beginning on com is in the interval [_history.data[(w+1)%N], _history.data[w]]
                //Otherwise com can be relatively small and an underrun can occur when _boundary is subtracted
                _history.valid=true;        
                _history.com.q =time;
                _history.com.r =0;
                int32_t idx = w;
                for (uint32_t i =1; i < N; i++){
                    idx = increment<NSIGNED>(idx);
                    _history.dataQR[idx] = dataQr;
                    _history.data[idx]=time;
                }
            }
            else {         
                add<N>(_history.com, dataQr, _history.com);       
            }
            w = increment<NSIGNED>(w);
                     
            const uint32_t newOldest = _history.data[w];

            // Two distinct reasons to "rebase"
            const bool nearTop = (newOldest >= _boundary);
            const bool wrapSplit = (oldOldest > newOldest);  // rare "true wrap" indicator

            if (nearTop || wrapSplit) {
                // Always rebase data by subtracting boundary (mod 2^32 rotation)
                for (uint32_t i = 0; i < N; i++) {
                    _history.data[i] -= _boundary;
                }

                // Update comOffset (external epoch correction)
                _history.comOffset += _boundary;

                if (!wrapSplit) {
                    // Fast path: safe because all entries are >= boundary in linear sense
                    for (uint32_t i = 0; i < N; i++) {
                        _history.dataQR[i].q -= _boundaryFraction;
                    }
                    _history.com.q -= _boundary;  // because boundary == N * boundaryFraction
                    // reminders unchanged since boundary % N == 0
                }
                else {
                    // Slow but safe path: recompute everything from rebased data[]
                    _history.com.q = 0;
                    _history.com.r = 0;

                    for (uint32_t i = 0; i < N; i++) {
                        const uint32_t t = _history.data[i];
                        _history.dataQR[i] = getQR<N>(t);
                        add<N>(_history.com, _history.dataQR[i], _history.com);
                    }

                    // If you cache errors via state/map, you must invalidate them here:
                    std::fill(_history.state.begin(), _history.state.end(), 0);
                }
            }
            //========================== 
        }

        History<N> getHistory() const {
            return _history;
        }

        bool isHistoryValid() const {
            return _history.valid;
        }

        uint32_t getLastDuration()const{
            constexpr int32_t NSIGNED = int32_t(N);
            int32_t upperIdx = decrement<NSIGNED>(_history.currentWriteIndex);
            int32_t lowerIdx = decrement<NSIGNED>(upperIdx);
            return _history.data[upperIdx] - _history.data[lowerIdx];
        }
        template <uint32_t O>
        double getLastCall(History<N>&h) const { 
            constexpr int32_t halfN = int32_t(N / 2);
            constexpr int32_t NSigned = int32_t(N);

            int32_t idx= decrement<NSigned>(h.currentWriteIndex);
            if (h.state[h.currentWriteIndex] ==-1){
                //h is not completely filled and the algorithm can't work properly -> we just return the latest value
                return double(h.data[idx] + h.comOffset);
            }

            //remove all non-evaluated data
            int32_t validSortedEnd=0;
            for (int32_t i =0; i < NSigned; i++){
                if (h.sortedIdx[i] != -1 && h.state[h.sortedIdx[i]] > 0) {
                    if (validSortedEnd < i) {
                        h.sortedIdx[validSortedEnd] = h.sortedIdx[i];
                    }
                    validSortedEnd++;
                }
            }
            // =============================
           
            uint32_t shift = _comPerfect.q - h.com.q;
            int32_t shiftReminder = _comPerfect.r - h.com.r;
            if (shiftReminder > halfN){
                shift++;
            }
            else if (shiftReminder < -halfN) {
                shift--;
            }
            
            for (int32_t i =NSigned-1; i >=0; i--) {
                if (h.state[idx] > 0) {
                    //already evaluated
                    break;
                }
                uint32_t dataS= h.data[idx] + shift; 
                uint32_t error = dataS - _dataPerfect[i];
                if (error > UINT32_MAX/2) {
                    error = _dataPerfect[i] - dataS;
                }
                h.errors[idx] = error;
                h.state[idx] = 1;
                
                // add the new data point to the sorted index array                
                for (int32_t posSorted =0; posSorted< NSigned; posSorted++){
                    if (posSorted == validSortedEnd){
                        h.sortedIdx[posSorted] = idx;
                        validSortedEnd++;
                        break;
                    }
                    int32_t hIdx = h.sortedIdx[posSorted];
                    if (h.errors[idx] > h.errors[hIdx]){
                        if (posSorted < validSortedEnd) {
                            //shift all remaining indices back and make space for the new entry
                            size_t numBytes = sizeof(h.sortedIdx[0])*(validSortedEnd-posSorted);
                            memmove(&(h.sortedIdx[posSorted+1]), &(h.sortedIdx[posSorted]), numBytes);
                        }
                        h.sortedIdx[posSorted] = idx;
                        validSortedEnd++;
                        break;
                    }
                }
                idx=decrement<NSigned>(idx);
            }

            if(h.errors[h.sortedIdx[0]] == 0){
                //the data seems to be perfect and we can just return the last sample
                int32_t idx=decrement<NSigned>(h.currentWriteIndex);
                return double(h.data[idx]+h.comOffset);
            }

            //Now we compute the center of mass for a second time.
            //It's more efficient to just remove the contributions of the outliers from the center of masses
            QR com=h.com;
            QR comPerfect =_comPerfect;

            for (uint32_t i =0; i < O; i++){
                int32_t outlierIdx = h.sortedIdx[i];
                subtract<N>(com, h.dataQR[outlierIdx], com);
                                
                int32_t idxPerfect=outlierIdx - h.currentWriteIndex;
                if (idxPerfect < 0){
                    idxPerfect += NSigned;
                }
                subtract<N>(comPerfect, _dataPerfectQR[idxPerfect], comPerfect);
            }

            constexpr double NInv = 1./double(N);
            constexpr double f = double(N)/double(N-O);

            double shiftToCom = (com.q > comPerfect.q ?
                double(com.q - comPerfect.q) : -1.*(comPerfect.q-com.q))
                +double(com.r-comPerfect.r)*NInv;

            double correctedSample = shiftToCom*f + _dataPerfect[N-1] + h.comOffset;

            constexpr double pow2_32= double(UINT32_MAX)+1.;
            if (correctedSample > UINT32_MAX){
                correctedSample -= pow2_32;
            }
            else if(correctedSample < 0) {
                correctedSample += pow2_32;
            }
            return correctedSample;
        }

        template <uint32_t O>
        double getLastCall() { 
            return getLastCall<O>(_history);
        }
    private:
       
        History<N> _history;  
        uint32_t _boundaryFraction;
        uint32_t _boundary;   
        
        std::array<uint32_t,N> _dataPerfect;
        std::array<QR,N> _dataPerfectQR;
        QR _comPerfect;
};
#endif
#endif