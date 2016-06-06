#include "RgbLed.h"
#include "Arduino.h"

RgbLed::RgbLed(int redPin, int greenPin, int bluePin){
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void RgbLed::on(int r, int g, int b){
  digitalWrite(_redPin, r);
  digitalWrite(_greenPin, g);
  digitalWrite(_bluePin, b);
}

void RgbLed::off(){
  digitalWrite(_redPin, 0);
  digitalWrite(_greenPin, 0);
  digitalWrite(_bluePin, 0);
}

void RgbLed::flash(int r, int g, int b, int duration){
  on(r, g, b);
  delay(duration);
  off();
  delay(duration);
}
