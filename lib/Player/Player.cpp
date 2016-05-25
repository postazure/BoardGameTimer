#include "Player.h"

Player::Player(int r, int g, int b, char * playerName) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
  name = playerName;
}

void Player::increaseTotalTurns(){
  totalTurns++;
}

void Player::addToTotalTime(long millis){
  totalTime += millis;
}

int * Player::getColor(){
  return color;
}

char * Player::getName(){
  return name;
}
