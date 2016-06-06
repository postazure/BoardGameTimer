#ifndef RgbLed_h
#define RgbLed_h

class RgbLed {
  public:
    RgbLed(unsigned char redPin, unsigned char greenPin, unsigned char bluePin);
    void on(unsigned char r, unsigned char g, unsigned char b);
    void off();
    void flash(unsigned char r, unsigned char g, unsigned char b, int duration);

  private:
    unsigned char _redPin;
    unsigned char _greenPin;
    unsigned char _bluePin;
};

#endif
