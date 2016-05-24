int getBrightness(){
  return analogRead(sensorPin);
}

void calibrateLightSensor() {
  Serial.println("calibrating/dark");
  while(millis() < 2000){
    rgbFlash(0,0,255,50);
    minLight = analogRead(sensorPin);
  } 
  
  rgbFlash(0,255,0,500, 4);

  Serial.println("calibrating/bright");
  while(millis() < 8000){
    rgbFlash(0,0,255,50);
    maxLight = analogRead(sensorPin);
  }

  rgbFlash(0,255,0,1000);
}
