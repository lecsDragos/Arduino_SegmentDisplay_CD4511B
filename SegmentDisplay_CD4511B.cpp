#include "SegmentDisplay_CD4511B.h"
// This sketch uses CD4511B chip to drive the seven segment displays;

// Constants
const int ledDriverInputTable[10][4] = {
  {0, 0, 0, 0}, // 0
  {1, 0, 0, 0}, // 1
  {0, 1, 0, 0}, // 2
  {1, 1, 0, 0}, // 3
  {0, 0, 1, 0}, // 4
  {1, 0, 1, 0}, // 5
  {0, 1, 1, 0}, // 6
  {1, 1, 1, 0}, // 7
  {0, 0, 0, 1}, // 8
  {1, 0, 0, 1}  // 9
};

// Configuration
int *latchPins;
int displayPins[4];
int digits;

// Public methods
SegmentDisplay_CD4511B::SegmentDisplay_CD4511B(int a, int b, int c, int d, int pinCount, ...) {
  setDisplayControlPins(a, b, c, d); 

  va_list latchPins;
  va_start(latchPins, pinCount);
  setLatchControlPins(pinCount, latchPins);
  va_end(latchPins);

  enablePinsForPutput();
}

void SegmentDisplay_CD4511B::setDisplayControlPins(int a, int b, int c, int d) {
  displayPins[0] = a;
  displayPins[1] = b;
  displayPins[2] = c;
  displayPins[3] = d;
}

void SegmentDisplay_CD4511B::setLatchControlPins(int count, va_list pins) {
  latchPins = (int *) malloc(count * sizeof(int));
  digits = count;
  for (int index = 0; index < count; index++) {
    latchPins[index] = va_arg(pins, int);
  }
}

void SegmentDisplay_CD4511B::enablePinsForPutput() {
  for (int index = 0; index < 4; index++) {
    pinMode(displayPins[index], OUTPUT);
  }

  for (int index = 0; index < digits; index++) {
    pinMode(latchPins[index], OUTPUT);
  }
}

// Display logic
void SegmentDisplay_CD4511B::showNumber(int number) {
  showNumber(number, digits, 0);
}

void SegmentDisplay_CD4511B::showNumber(int number, int digits, int currentDigit) {
    int divider = pow(10, digits - 1);
    int numberToDisplay = number / divider;
   
    showNumberUsingLedDriverPins(numberToDisplay, displayPins, latchPins[currentDigit]);

    if (digits > 1) {
      int rest = number % divider;
      showNumber(rest, digits - 1, currentDigit + 1);
    }
}

void SegmentDisplay_CD4511B::showNumberUsingLedDriverPins(int number, int pins[4], int latchingPin) {
  digitalWrite(latchingPin, LOW);

  Serial.println(latchingPin);
  
  for (int index = 0; index < 4; index++) { 
    int pin = pins[index];
    int value = ledDriverInputTable[number][index];
    digitalWrite(pin, value);
  }
  
  digitalWrite(latchingPin, HIGH);
}
