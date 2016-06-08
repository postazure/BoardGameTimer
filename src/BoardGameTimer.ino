#include <Arduino.h>
#include <Timer.h>
#include <Player.h>
#include <RgbLed.h>
#include <PlayerManager.h>
#include <SoftwareSerial.h>

const int sensorPin = A0;
const byte RX = 9;
const byte TX = 10;

SoftwareSerial btSerial(RX, TX);

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

void lightPlayerColor(byte *pc){
  rgb -> on(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(byte *pc, byte duration){
  rgb -> flash(pc[0], pc[1], pc[2], duration);
}

void sendPlayerTimes(){
  byte playerCount = playerManager -> getPlayerCount();

  for(byte i = 0; i < playerCount; i++){
    Player player = playerManager -> getPlayer(i);
    btSerial.print(player.id);
    btSerial.print(',');
    btSerial.print(player.totalTurns);
    btSerial.print(',');
    btSerial.print(player.totalTime);

    if (i < playerCount - 1){
      btSerial.print(':');
    }
  }
  btSerial.print(';');
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

void initGame(){
  rgb -> on(0, 255, 0);

  boolean waitingForData = true;
  byte playerInfo[4];
  do {
    while(btSerial.available()){
      btSerial.readBytes(playerInfo, 4);
      byte id = playerInfo[0];
      byte r = playerInfo[1];
      byte g = playerInfo[2];
      byte b = playerInfo[3];

      Serial.print(id);
      Serial.print(" ");
      Serial.print(r);
      Serial.print(" ");
      Serial.print(g);
      Serial.print(" ");
      Serial.println(b);

      playerManager -> addPlayer(new Player(r, g, b, id));
      delay(20);
      waitingForData = false;
    }
  } while (waitingForData);
}

bool runOnce = true;
void setup() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  btSerial.begin(9600);

  Serial.begin(9600); //Debug

  calibrateLightSensor();
  initGame();
  sendPlayerTimes();
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
    //Paused
    timer -> markPauseIfUnpaused();
    paused = true;
    timing = false;

    flashPlayerColor(playerManager -> getCurrentPlayer().color, 250);

  } else if (!paused) {
    //Passing
    rgb -> off();
    timing = false;
  }

  delay(50); //Runs too fast without serial printing
}
