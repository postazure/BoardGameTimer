#ifndef PlayerManager_h
#define PlayerManager_h

#include <Player.h>

class PlayerManager {
  public:
    PlayerManager();
    void addPlayer(Player* player);
    int getPlayerCount();
    void nextPlayer();
    Player getCurrentPlayer();
    int getCurrentPlayerNum();

  private:
    Player *_players[10];
    int _currentPlayerNum;
    int _totalPlayersPointer;
};

#endif
