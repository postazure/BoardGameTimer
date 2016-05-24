#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(int r, int g, int b);
    int color[3];
    int totalTurns;
    long totalTime;
};

#endif
