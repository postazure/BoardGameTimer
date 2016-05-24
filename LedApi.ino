/*---------Regular LED-------*/
void statusLedFlash(int duration){
  statusLedOn();
  delay(duration);
  statusLedOff();
  delay(duration);
}

void statusLedOn(){
  digitalWrite(ledPin, HIGH);
}

void statusLedOff(){
  digitalWrite(ledPin, LOW);
}

/*----------RGB LED-----------*/
void rgbOn(int r, int g, int b){
  digitalWrite(redLed, r);
  digitalWrite(greenLed, g);
  digitalWrite(blueLed, b);
}

void rgbOff(){
  digitalWrite(redLed, 0);
  digitalWrite(greenLed, 0);
  digitalWrite(blueLed, 0);
}

void rgbFlash(int r, int g, int b, int duration){
  rgbOn(r, g, b);
  delay(duration);
  rgbOff();
  delay(duration);
}

void rgbFlash(int r, int g, int b, int duration, int times){
  for(int i = 0; i < times; i++){
    rgbFlash(r, g, b, duration);
  }
}

