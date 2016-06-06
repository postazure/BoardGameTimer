#ifndef BleClient_h
#define BleClient_h

#include <SoftwareSerial.h>

class BleClient {
  public:
    BleClient(int RX, int TX);
    void write(String msg);
    String read();

  private:
    SoftwareSerial btSerial;
};

#endif
