#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(int r, int g, int b, char * playerName);
    int * getColor();
    int totalTurns;
    long totalTime;
    char * getName();
  private:
    int color[3];
    char * name;
};

#endif
