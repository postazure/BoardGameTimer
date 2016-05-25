#ifndef Player_h
#define Player_h

class Player {
  public:
    Player(int r, int g, int b, char * playerName);
    int * getColor();
    void increaseTotalTurns();
    void addToTotalTime(long millis);
    char * getName();
    long getTotalTime();
    long getTotalTurns();

  private:
    int color[3];
    long totalTime;
    int totalTurns;
    char * name;
};

#endif
