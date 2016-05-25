#include "PlayerManager.h"

PlayerManager::PlayerManager(){
  _totalPlayersPointer = 0;
  _currentPlayerNum = 0;
}

int PlayerManager::getPlayerCount(){
  return _totalPlayersPointer;
}

int PlayerManager::getCurrentPlayerNum(){
  return _currentPlayerNum;
}

void PlayerManager::addPlayer(Player* player) {
  _players[_totalPlayersPointer] = player;
  _totalPlayersPointer++;
}

void PlayerManager::nextPlayer(){
  _currentPlayerNum++;
  if (_currentPlayerNum > _totalPlayersPointer - 1) {
    _currentPlayerNum = 0;
  }
}

Player PlayerManager::getPlayer(int index){
  return *_players[index];
}

Player PlayerManager::getCurrentPlayer(){
  return getPlayer(_currentPlayerNum);
}

void PlayerManager::updateCurrentPlayer(Player player){
  *_players[_currentPlayerNum] = player;
}
