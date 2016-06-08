#include "RgbLed.h"
#include "Arduino.h"

RgbLed::RgbLed(unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void RgbLed::on(unsigned char r, unsigned char g, unsigned char b){
  digitalWrite(_redPin, r);
  digitalWrite(_greenPin, g);
  digitalWrite(_bluePin, b);

  // digitalWrite(_redPin, 255-r);
  // digitalWrite(_greenPin, 255-g);
  // digitalWrite(_bluePin, 255-b);
}

void RgbLed::off(){
  digitalWrite(_redPin, 0);
  digitalWrite(_greenPin, 0);
  digitalWrite(_bluePin, 0);

  // digitalWrite(_redPin, 255);
  // digitalWrite(_greenPin, 255);
  // digitalWrite(_bluePin, 255);
}

void RgbLed::flash(unsigned char r, unsigned char g, unsigned char b, int duration){
  on(r, g, b);
  delay(duration);
  off();
  delay(duration);
}
