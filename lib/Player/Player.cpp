#include "Player.h"

Player::Player(int r, int g, int b) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

int * Player::getColor(){
  return color;
}
