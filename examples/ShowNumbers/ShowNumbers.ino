#include <SegmentDisplay_CD4511B.h>

// the number that will get displayed
int number = 0;

/*
 * The parameters of the SegmentDisplay_CD4511B constructor:
 *    First 4 numbers are the Arduino pins connected to the  A, B, C, D pins of the CD4511B chip(s)
 *      in this example 6,8,7,5 are the pins used
 *    5-th number is the number of chips used 
 *      in this example 2 chips are used to drive 2 displays
 *    the remaining pins are the Arduino pins connected to the latching pins of the CD4511B chip(s) 
 *      in this example 9 and 10 are the numbers of the latching pins
*/
SegmentDisplay_CD4511B displayDriver(6,8,7,5,2,9,10);

void setup() {}

void loop() {
  if (number > 20) { number = 0; }
  
  displayDriver.showNumber(number);
  
  number++;
  
  delay(250);  
}
