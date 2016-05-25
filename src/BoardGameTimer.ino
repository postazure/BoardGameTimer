#include <Arduino.h>
#include <Timer.h>
#include <Player.h>
#include <RgbLed.h>
#include <PlayerManager.h>

const int sensorPin = A0;

RgbLed *rgb = new RgbLed(10, 9, 11);
Timer *timer = new Timer();
PlayerManager *playerManager = new PlayerManager();

int maxLight = 0;

bool paused = true;
bool timing = false;

void calibrateLightSensor() {
  while(millis() < 3000){
    rgb -> flash(0,0,255,20);
    maxLight = analogRead(sensorPin);
  }
}

int getBrightness(){
  return analogRead(sensorPin);
}

void lightPlayerColor(int *pc){
  rgb -> on(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(int *pc, int duration){
  rgb -> flash(pc[0], pc[1], pc[2], duration);
}

void timingSeq() {
  Player currentPlayer = playerManager -> getCurrentPlayer();

  if (!paused) {
    long turnMillis = timer -> getElapsedTime();
    currentPlayer.addToTotalTime(turnMillis);
    currentPlayer.increaseTotalTurns();
    playerManager -> updateCurrentPlayer(currentPlayer);

    Serial.print("END Player: ");
    Serial.println(currentPlayer.getName());
    Serial.print("Turn took: ");
    Serial.println(turnMillis);

    Serial.print(playerManager -> getPlayer(0).getTotalTime());
    Serial.print(" (");
    Serial.print(playerManager -> getPlayer(0).getTotalTurns());
    Serial.println(")");

// -----------New Players Turn Starts--------------------
    playerManager -> nextPlayer();
    timer -> markTurnStart();
    currentPlayer = playerManager -> getCurrentPlayer();
    
    Serial.print("START Player: ");
    Serial.println(currentPlayer.getName());
  }

  lightPlayerColor(playerManager -> getCurrentPlayer().getColor());
  paused = false;
  timing = true;
}

void passingSeq() {
  rgb -> off();
  timing = false;
}

void pausedSeq() {
  timer -> markPauseIfUnpaused();
  paused = true;
  timing = false;

  flashPlayerColor(playerManager -> getCurrentPlayer().getColor(), 250);
}

bool runOnce = true;
void setup() {
  Serial.begin(19200);
  playerManager -> addPlayer(new Player(0,255,0, "Green"));
  playerManager -> addPlayer(new Player(255,0,0, "Red"));
  playerManager -> addPlayer(new Player(0,0,255, "Blue"));
  playerManager -> addPlayer(new Player(255,165,0, "Orange"));

  calibrateLightSensor();

  Serial.println("STARTING...");
}

void loop() {
  // minLight ---timing---|----passing----|---paused---maxLight

  if (getBrightness() < maxLight * 0.10) {
    if (runOnce) {
      runOnce = false;
      //reset counter when play starts for the first time.
      timer -> getElapsedTime();
      timer -> markTurnStart();
    }

    if (!timing) {
      timer -> markResumeIfPaused();
      timingSeq();
    }
    timer -> markTurnEnd();

  } else if (getBrightness() > maxLight * 0.95) {
    pausedSeq();

  } else if (!paused) {
    passingSeq();
  }

  delay(50); //Runs too fast without Serial printing
}
