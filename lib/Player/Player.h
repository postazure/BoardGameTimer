#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(int r, int g, int b);
    int * getColor();
    int totalTurns;
    long totalTime;
  private:
    int color[3];
};

#endif
