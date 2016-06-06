#include "PlayerManager.h"

PlayerManager::PlayerManager(){
  _totalPlayersPointer = 0;
  _currentPlayerNum = 0;
}

unsigned char PlayerManager::getPlayerCount(){
  return _totalPlayersPointer;
}

unsigned char PlayerManager::getCurrentPlayerNum(){
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

Player PlayerManager::getPlayer(unsigned char index){
  return *_players[index];
}

Player PlayerManager::getCurrentPlayer(){
  return getPlayer(_currentPlayerNum);
}

void PlayerManager::updateCurrentPlayer(Player player){
  *_players[_currentPlayerNum] = player;
}
