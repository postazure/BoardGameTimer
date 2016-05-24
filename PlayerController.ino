void setRandomStartPlayer(){
  randomSeed(getBrightness() + millis());
  currentPlayer = random(playersCount - 1);
  currentPlayerColor = getColorsForPlayer(currentPlayer);
}

int * getColorsForPlayer(int playerNum){
  return players[playerNum] -> color;
}

void lightPlayerColor(int *pc){
  rgb -> on(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(int *pc, int duration){
  rgb -> flash(pc[0], pc[1], pc[2], duration);
}

void nextPlayer(){
  currentPlayer += 1;
  if ( currentPlayer > playersCount - 1 ){
    currentPlayer = 0;
  }
}

void timePlayer(){
  
}


