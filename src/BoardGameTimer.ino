#include <Arduino.h>
#include <Timer.h>
#include <Player.h>
#include <RgbLed.h>
#include <PlayerManager.h>
#include <BleClient.h>

const int sensorPin = A0;

BleClient bleSerial(2, 3);

RgbLed *rgb = new RgbLed(7, 6, 8);
Timer *timer = new Timer();
PlayerManager *playerManager = new PlayerManager();

int maxLight = 0;

bool paused = true;
bool timing = false;

void calibrateLightSensor() {
  while(millis() < 3000){
    rgb -> flash(0,0,255,20);
    maxLight = getBrightness();
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
    // ------------ Finish Last Player's Turn
    long turnMillis = timer -> getElapsedTime();
    currentPlayer.totalTime += turnMillis;
    currentPlayer.totalTurns++;
    playerManager -> updateCurrentPlayer(currentPlayer);

    // ----------- Send Status Report
    sendPlayerTimes();

    // ----------- Start New Players Turn
    playerManager -> nextPlayer();
    timer -> markTurnStart();
    currentPlayer = playerManager -> getCurrentPlayer();
  }

  lightPlayerColor(playerManager -> getCurrentPlayer().color);
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

  flashPlayerColor(playerManager -> getCurrentPlayer().color, 250);
}

void sendPlayerTimes(){
  String status = "";

  int playerCount = playerManager -> getPlayerCount();
  for (int i = 0; i < playerCount; i++){
    Player player = playerManager -> getPlayer(i);
    status += player.id;
    status += ",";
    status += player.totalTurns;
    status += ",";
    status += player.totalTime;
    if (playerCount != i+1){
      status += ":";
    }
  }
  bleSerial.write(status);
}

void initGame(){
  // Get all players and add them to player manager
  String info = "";
  rgb -> on(0, 255, 0);

  while(info.length() == 0){
    info = bleSerial.read();
  }

  int playerCount = info.length() / 11; //String Length of player info

  for (int i = 0; i < playerCount; i++){
    playerManager -> addPlayer(new Player(
      info.substring(i + 2, i + 5).toInt(),
      info.substring(i + 5, i + 8).toInt(),
      info.substring(i + 8, i + 11).toInt(),
      info.substring(i, i + 2).toInt()
    ));
    rgb -> flash(0,0,255,20);
  }

  rgb -> off();
}

bool runOnce = true;
void setup() {
  calibrateLightSensor();
  initGame();
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

  delay(50); //Runs too fast without serial printing
}
