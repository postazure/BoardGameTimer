#include <Arduino.h>
#include "Player.h"

Player::Player(int r, int g, int b, char * playerName) {
  color[0] = r;
  color[1] = g;
  color[2] = b;

  totalTime = 0;
  totalTurns = 0;

  name = playerName;
}

long Player::getTotalTime(){
  return totalTime;
}

long Player::getTotalTurns(){
  return totalTurns;
}

void Player::increaseTotalTurns(){
  totalTurns++;
}

void Player::addToTotalTime(long millis){
  totalTime += millis;

  Serial.print("Millis: ");
  Serial.print(millis);
  Serial.print(" | Total Time: ");
  Serial.println(totalTime);
}

int * Player::getColor(){
  return color;
}

char * Player::getName(){
  return name;
}
