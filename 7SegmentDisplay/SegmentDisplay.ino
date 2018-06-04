int ledDriverPins[4] = {6, 8, 7, 5};

int led1LatchPin = 9;
int led2LatchPin = 10;

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

int number = 0;

void displayNumber(int n) {
  int firstDigit = firstDigitFromNumber(n);
  displayNumberUsingLedDriverPins(firstDigit, ledDriverPins, led1LatchPin);

  int secondDigit = secondDigitFromNumber(n);
  displayNumberUsingLedDriverPins(secondDigit, ledDriverPins, led2LatchPin);
}

void displayNumberUsingLedDriverPins(int number, int pins[4], int latchingPin) {
  digitalWrite(latchingPin, LOW);
  
  for (int index = 0; index < 4; index++) { 
    int pin = pins[index];
    int value = ledDriverInputTable[number][index];
    digitalWrite(pin, value);
  }
  
  digitalWrite(latchingPin, HIGH);
}

int firstDigitFromNumber(int n) {
  return n / 10;
}

int secondDigitFromNumber(int n) {
  return n % 10;
}

void setup() {
  enablePinsForPutput();
}

void enablePinsForPutput() {
  for (int index = 0; index < 4; index++) {
    int ld1Pin = ledDriverPins[index];
    pinMode(ld1Pin, OUTPUT);
  }

  pinMode(led1LatchPin, OUTPUT);
  pinMode(led2LatchPin, OUTPUT);
}

void loop() {
  if (number > 99) { number = 0; }
  
  displayNumber(number);
  number++;
  delay(250);  
}
