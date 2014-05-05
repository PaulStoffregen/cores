#ifdef __cplusplus

#ifndef server_h
#define server_h
#if ARDUINO >= 100

class Server : public Print {
public:
  virtual void begin() =0;
};

#endif
#endif
