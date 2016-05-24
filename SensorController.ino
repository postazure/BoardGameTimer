int getBrightness(){
  return analogRead(sensorPin);
}

void calibrateLightSensor() {
  Serial.println("calibrating/bright");
  while(millis() < 3000){
    rgbFlash(0,0,255,20);
    maxLight = analogRead(sensorPin);
  }
}
