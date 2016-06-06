#ifndef BleClient_h
#define BleClient_h

#include <SoftwareSerial.h>

class BleClient {
  public:
    BleClient(unsigned char RX, unsigned char TX);
    void write(String msg);
    String read();

  private:
    SoftwareSerial btSerial;
};

#endif
