#ifndef Timer_h
#define Timer_h

class Timer {
  public:
    Timer();
    long getElapsedTime();
    void markPauseIfUnpaused();
    void markResumeIfPaused();
    void markTurnStart();
    void markTurnEnd();

  private:
    void reset();
    long lastPause;
    long turnStart;
    long turnEnd;
    long nonCountableMillis;
};

#endif
