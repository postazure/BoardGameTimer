#include "Player.h"

Player::Player(int r, int g, int b, int playerId) {
  color[0] = r;
  color[1] = g;
  color[2] = b;

  totalTime = 0;
  totalTurns = 0;

  id = playerId;
}
