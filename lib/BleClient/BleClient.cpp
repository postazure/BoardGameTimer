#include "BleClient.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

BleClient::BleClient(int RX, int TX) : btSerial(SoftwareSerial(RX, TX)){
    btSerial.begin(9600);
}

void BleClient::write(String msg){
  msg += ";";
  btSerial.write(msg.c_str());
}

String BleClient::read(){
  String messageBuffer = "";

  while(btSerial.available()){
    messageBuffer.concat(btSerial.readString());
    delay(20);
  }

  return messageBuffer;
}
