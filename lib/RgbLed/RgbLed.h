#ifndef RgbLed_h
#define RgbLed_h

class RgbLed {
  public:
    RgbLed(int redPin, int greenPin, int bluePin);
    void on(int r, int g, int b);
    void off();
    void flash(int r, int g, int b, int duration);

  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif
