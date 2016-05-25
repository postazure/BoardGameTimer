#include <Arduino.h>

#include <Player.h>
#include <RgbLed.h>
#include <PlayerManager.h>

int sensorPin = A0;
int maxLight = 0;

RgbLed *rgb = new RgbLed(10, 9, 11);

PlayerManager *playerManager = new PlayerManager();

bool paused = true;
bool timing = false;

void timingSeq() {
  if (!paused) {
    playerManager -> nextPlayer();
  }
    //    resume timer
  Serial.print("Current Player: ");
  Serial.println(playerManager -> getCurrentPlayerNum());

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
  Serial.println("calibrating/bright");
  while(millis() < 3000){
    rgb -> flash(0,0,255,20);
    maxLight = analogRead(sensorPin);
  }
}

void setup() {
  Serial.begin(9600);

  playerManager -> addPlayer(new Player(0,255,0));
  playerManager -> addPlayer(new Player(255,0,0));
  playerManager -> addPlayer(new Player(0,0,255));
  playerManager -> addPlayer(new Player(255,165,0));

  calibrateLightSensor();

  Serial.println("STARTING...");
}

void loop() {
  // minLight ---timing---|----passing----|---paused---maxLight

  if (getBrightness() < maxLight * 0.05) {
    if (!timing) {
      Serial.print("Timing ");
      timingSeq();
    }

  } else if (getBrightness() > maxLight * 0.95) {
    // Serial.println("Paused");
    pausedSeq();

  } else if (!paused) {
    passingSeq();
  }
  delay(10);

  // Serial.print("current: ");
  // Serial.print(getBrightness());
  // Serial.print(" max: ");
  // Serial.println(maxLight);
}
