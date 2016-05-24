#include "Player.h"
#include "RgbLed.h"

int ledPin = 13;
int sensorPin = A0;

RgbLed *rgb = new RgbLed(10, 9, 11);

int totalPlayers = 4;
float playerTimes[4] = {0, 0, 0, 0};
int currentPlayer;

bool paused = true;
bool timing = false;

int maxLight = 0;

int * currentPlayerColor;

void setup() {
  Serial.begin(9600);
  calibrateLightSensor();

  setRandomStartPlayer();
  
  Serial.println("STARTING...");
}

void loop() {
  int brightness = getBrightness();

  // minLight ---timing---|----passing----|---paused---maxLight

  if (brightness < maxLight * 0.05) {
    //    facedown | players turn
    if (!timing) {
      timingSeq();
    }
  } else if (brightness > maxLight * 0.95) {
    //    faceup | pause
    pausedSeq();
  } else if (!paused) {
    //    passing?
    passingSeq();
  }

  Serial.print("current: ");
  Serial.print(getBrightness());
  Serial.print(" max: ");
  Serial.println(maxLight);
}

void timingSeq() {
  Serial.print("Timing ");
   
  if (!paused) {
    nextPlayer(); 
  }

    //    resume timer
  
  currentPlayerColor = getColorsForPlayer(currentPlayer);
  lightPlayerColor(currentPlayerColor);
  paused = false;
  timing = true;
}

void passingSeq() {
  rgb -> off();
  Serial.println("Passing");
  timing = false;
}

void pausedSeq() {
  paused = true;
  timing = false;
  Serial.println("Paused");
  flashPlayerColor(currentPlayerColor, 250);
}


