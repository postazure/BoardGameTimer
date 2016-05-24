int pc1[] = {0,255,0};
int pc2[] = {255,0,0};
int pc3[] = {0,0,255};
int pc4[] = {255,165,0};

Player *players[4] = {
  new Player(0,255,0), 
  new Player(255,0,0),
  new Player(0,0,255),
  new Player(255,165,0)
};

void setRandomStartPlayer(){
  randomSeed(getBrightness() + millis());
  currentPlayer = random(totalPlayers - 1);
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
  if ( currentPlayer > totalPlayers - 1 ){
    currentPlayer = 0;
  }
}

void timePlayer(){
  
}


