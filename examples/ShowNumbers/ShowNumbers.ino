#include <SegmentDisplay_CD4511B.h>

int numberToDisplay = 0;

SegmentDisplay_CD4511B sg(6,8,7,5,2,9,10);

void setup() {
}

void loop() {
  if (numberToDisplay > 12) { numberToDisplay = 0; }
  
  sg.displayNumber(numberToDisplay);
  
  numberToDisplay++;
  
  delay(250);  
}
