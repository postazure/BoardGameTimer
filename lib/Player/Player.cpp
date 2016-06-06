#include "Player.h"

Player::Player(unsigned char r, unsigned char g, unsigned char b, unsigned char playerId) {
  color[0] = r;
  color[1] = g;
  color[2] = b;

  totalTime = 0;
  totalTurns = 0;

  id = playerId;
}
