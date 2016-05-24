int pc1[] = {0,255,0};
int pc2[] = {255,0,0};
int pc3[] = {0,0,255};
int pc4[] = {255,165,0};

void setRandomStartPlayer(){
  randomSeed(getBrightness() + millis());
  currentPlayer = random(totalPlayers - 1);
  currentPlayerColor = getColorsForPlayer(currentPlayer);
}

int * getColorsForPlayer(int playerNum){
  switch(playerNum){
    case 0:
      Serial.println("player 0 | Green");
      return pc1;

    case 1:
      Serial.println("player 1 | Red");
      return pc2;
      
    case 2:
      Serial.println("player 2 | Blue");
      return pc3;

    case 3:
      Serial.println("player 3 | Orange");
      return pc4;
  }
}

void lightPlayerColor(int *pc){
  rgbOn(pc[0], pc[1], pc[2]);
}

void flashPlayerColor(int *pc, int duration){
  rgbFlash(pc[0], pc[1], pc[2], duration);
}

void nextPlayer(){
  currentPlayer += 1;
  if ( currentPlayer > totalPlayers - 1 ){
    currentPlayer = 0;
  }
}

void timePlayer(){
  
}


