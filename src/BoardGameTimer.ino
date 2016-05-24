#include <Arduino.h>

#include <Player.h>
#include <RgbLed.h>

int ledPin = 13;
int sensorPin = A0;
int maxLight = 0;

RgbLed *rgb = new RgbLed(10, 9, 11);

//Todo: Create a wrapper around array to manage players.
int playersCount = 4;
Player *players[] = {
  new Player(0,255,0),
  new Player(255,0,0),
  new Player(0,0,255),
  new Player(255,165,0)
};

int currentPlayer;
int * currentPlayerColor;

bool paused = true;
bool timing = false;


int * getColorsForPlayer(int playerNum){
  return players[playerNum] -> color;
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



void setRandomStartPlayer(){
  randomSeed(getBrightness() + millis());
  currentPlayer = random(playersCount - 1);
  currentPlayerColor = getColorsForPlayer(currentPlayer);
}


void lightPlayerColor(int *pc){
  rgb -> on(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(int *pc, int duration){
  rgb -> flash(pc[0], pc[1], pc[2], duration);
}

void nextPlayer(){
  currentPlayer += 1;
  if ( currentPlayer > playersCount - 1 ){
    currentPlayer = 0;
  }
}

void timePlayer(){

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
