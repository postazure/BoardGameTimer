#ifndef PlayerManager_h
#define PlayerManager_h

#include <Player.h>

class PlayerManager {
  public:
    PlayerManager();
    void addPlayer(Player *player);
    int getPlayerCount();
    void nextPlayer();
    Player getCurrentPlayer();
    int getCurrentPlayerNum();
    Player getPlayer(int index);
    void updateCurrentPlayer(Player player);

  private:
    Player *_players[4];
    int _currentPlayerNum;
    int _totalPlayersPointer;
};

#endif
