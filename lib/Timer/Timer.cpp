#include "Timer.h"
#include <Arduino.h>

Timer::Timer(){
  lastPause = 0;
  turnStart = 0;
  turnEnd = 0;
  nonCountableMillis = 0;
}

long Timer::getElapsedTime(){
  long total = (turnEnd - turnStart);

  total -= nonCountableMillis;

  reset();
  return total;
}

void Timer::reset(){
  lastPause = 0;
  nonCountableMillis = 0;
}

void Timer::markTurnStart(){
  turnStart = millis();
}

void Timer::markTurnEnd(){
  turnEnd = millis();
}

void Timer::markPauseIfUnpaused(){
  if (lastPause == 0) {
    lastPause = millis();
  }
}

void Timer::markResumeIfPaused(){
  if (lastPause > 0) {
    nonCountableMillis += millis() - lastPause;
    lastPause = 0;
  }
}
