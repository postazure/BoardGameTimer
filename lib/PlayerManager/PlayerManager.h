#ifndef PlayerManager_h
#define PlayerManager_h

#include <Player.h>

class PlayerManager {
  public:
    PlayerManager();
    void addPlayer(Player *player);
    unsigned char getPlayerCount();
    void nextPlayer();
    Player getCurrentPlayer();
    unsigned char getCurrentPlayerNum();
    Player getPlayer(unsigned char index);
    void updateCurrentPlayer(Player player);

  private:
    Player *_players[4];
    unsigned char _currentPlayerNum;
    unsigned char _totalPlayersPointer;
};

#endif
