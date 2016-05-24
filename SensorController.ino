

int getBrightness(){
  return analogRead(sensorPin);
}

void calibrateLightSensor() {
  Serial.println("calibrating/bright");
  while(millis() < 3000){
    rgbFlash(0,0,255,50);
    maxLight = analogRead(sensorPin);
  }

  rgbFlash(0,255,0,1000);
}
