#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(int r, int g, int b, int playerId);
    int color[3];
    long totalTime;
    int totalTurns;
    int id;
};

#endif
