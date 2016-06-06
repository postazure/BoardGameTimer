#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(unsigned char r, unsigned char g, unsigned char b, unsigned char playerId);
    unsigned char color[3];
    long totalTime;
    int totalTurns;
    unsigned char id;
};

#endif
