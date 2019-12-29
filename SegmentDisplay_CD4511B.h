#ifndef SegmentDisplay_CD4511B_h
#define SegmentDisplay_CD4511B_h

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class SegmentDisplay_CD4511B {
  public:

    // Constructor parameters: 
    //    a, b, c, d - the arduino pins that correspond with the A,B,C,D inputs of the CD4511B chip(s)
    //    latchPins - the number of latch pins used and implicitly the number of CD4511B chips and segment displays used
    //    ... - the actual latch pin numbers connected to the arduino
    SegmentDisplay_CD4511B(int a, int b, int c, int d, int latchPins, ...);

    // Unexpected results occur if the number of digits is greater than the number of chips/displays
    void showNumber(int number);

  private:
    void setDisplayControlPins(int a, int b, int c, int d);
    void setLatchControlPins(int count, va_list pins);
    void enablePinsForPutput();
    void showNumber(int number, int digits, int currentDigit);
    void showNumberUsingLedDriverPins(int number, int pins[4], int latchingPin);

};

#endif
