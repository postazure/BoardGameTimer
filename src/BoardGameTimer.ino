#include <Arduino.h>
#include <Player.h>
#include <RgbLed.h>
#include <PlayerManager.h>

const int sensorPin = A0;

RgbLed *rgb = new RgbLed(10, 9, 11);
PlayerManager *playerManager = new PlayerManager();

int maxLight = 0;

bool paused = true;
bool timing = false;

void timingSeq() {
  if (!paused) {
    playerManager -> nextPlayer();
  }
    //    resume timer
  // Serial.print("Current Player: ");
  // Serial.print(playerManager -> getCurrentPlayer().getName());
  // Serial.print(" | ");
  // Serial.println(playerManager -> getCurrentPlayerNum());

  lightPlayerColor(playerManager -> getCurrentPlayer().getColor());
  paused = false;
  timing = true;
}

void passingSeq() {
  rgb -> off();
  timing = false;
}

void pausedSeq() {
  paused = true;
  timing = false;

  flashPlayerColor(playerManager -> getCurrentPlayer().getColor(), 250);
}

void lightPlayerColor(int *pc){
  rgb -> on(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(int *pc, int duration){
  rgb -> flash(pc[0], pc[1], pc[2], duration);
}

int getBrightness(){
  return analogRead(sensorPin);
}

void calibrateLightSensor() {
  while(millis() < 3000){
    rgb -> flash(0,0,255,20);
    maxLight = analogRead(sensorPin);
  }
}

void setup() {
  Serial.begin(9600);

  playerManager -> addPlayer(new Player(0,255,0, "Green"));
  playerManager -> addPlayer(new Player(255,0,0, "Red"));
  playerManager -> addPlayer(new Player(0,0,255, "Blue"));
  playerManager -> addPlayer(new Player(255,165,0, "Orange"));

  calibrateLightSensor();

  // Serial.println("STARTING...");
  // Serial.print("Current Player: ");
  // Serial.print(playerManager -> getCurrentPlayer().getName());
  // Serial.print(" | ");
  // Serial.println(playerManager -> getCurrentPlayerNum());
}

void loop() {
  // minLight ---timing---|----passing----|---paused---maxLight

  if (getBrightness() < maxLight * 0.10) {
    if (!timing) {
      timingSeq();
    }

  } else if (getBrightness() > maxLight * 0.95) {
    pausedSeq();

  } else if (!paused) {
    passingSeq();
  }

  delay(50); //Runs too fast without Serial printing
}
