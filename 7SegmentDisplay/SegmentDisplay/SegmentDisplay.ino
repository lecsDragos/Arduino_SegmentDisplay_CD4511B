// This sketch uses CD4511B chip to drive the seven segment displays;

// Configuration

int *latchPins;
int displayPins[4];
int maxDigits; // zero based; 

// Public setup methods
void setupDisplayPins(int a, int b, int c, int d) {
  displayPins[0] = a;
  displayPins[1] = b;
  displayPins[2] = c;
  displayPins[3] = d;
}

void setupLatchPins(int pins, ...) {
  va_list valist;
  va_start(valist, pins);
  latchPins = (int *) malloc(pins * sizeof(int));
  maxDigits = pins - 1;
  for (int index = 0; index < pins; index++) {
    latchPins[index] = va_arg(valist, int);
    
  }
  va_end(valist);
}

// Internal setup
void setup() {
  Serial.begin(9600);
  setupDisplayPins(6, 8, 7, 5);
  setupLatchPins(2, 9, 10);
  enablePinsForPutput();
}

void enablePinsForPutput() {
  for (int index = 0; index < 4; index++) {
    pinMode(displayPins[index], OUTPUT);
  }

  for (int index = 0; index <= maxDigits; index++) {
    pinMode(latchPins[index], OUTPUT);
  }
}

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

// Display logic
void displayNumber(int number) {
  displayNumber(number, maxDigits, 0);
}

void displayNumber(int number, int digits, int currentDigit) {  
    int divider = pow(10, digits);
    int numberToDisplay = number / divider;
   
    displayNumberUsingLedDriverPins(numberToDisplay, displayPins, latchPins[currentDigit]);

    if (digits > 0) {
      int rest = number % divider;
      displayNumber(rest, digits - 1, currentDigit + 1);
    }
}

void displayNumberUsingLedDriverPins(int number, int pins[4], int latchingPin) {
  digitalWrite(latchingPin, LOW);

  Serial.println(latchingPin);
  
  for (int index = 0; index < 4; index++) { 
    int pin = pins[index];
    int value = ledDriverInputTable[number][index];
    digitalWrite(pin, value);
  }
  
  digitalWrite(latchingPin, HIGH);
}

// Run loop 
int number = 0;
void loop() {

  if (number > 12) { number = 0; }
  
  displayNumber(number);
  number++;
  delay(250);  
}
