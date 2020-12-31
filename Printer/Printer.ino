/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
   http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo vertical; 
Servo horizontal;
Servo pen;

int maxBluePen = 10;

void setup() {
  vertical.attach(8);
  vertical.write(38); 
  pen.attach(9);
  pen.write(90);
  horizontal.attach(7);
  horizontal.write(20);
}
string[] a = [[1,1,1,1,1,1],
              [1,1,0,0,1,1],
              [1,1,0,0,1,1],
              [1,1,1,1,1,1],
              [1,1,0,0,1,1],
              [1,1,0,0,1,1],
              [1,1,0,0,1,1]]
void loop() {
 for (int horizonalPos = 20; horizonalPos <= 100; horizonalPos += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      horizontal.attach(7);
      horizontal.write(horizonalPos);              // tell servo to go to position in variable 'pos'
      delay(250);
      horizontal.detach();
      
      pen.attach(9);
      pen.write(90);
      for (int penPos = 90; penPos >= maxBluePen; penPos -= 2) { 
        pen.write(penPos);              
        delay(2);                       
      }
      delay(30);
      for (int penPos = maxBluePen; penPos <= 90; penPos += 2) { // goes from 180 degrees to 0 degrees
        pen.write(penPos);              
        delay(2);                      
      }
      
      pen.detach();
      delay(2);
 }

  horizontal.attach(7);
  for (int horizonalPos = 100; horizonalPos >= 20; horizonalPos -= 2) { // goes from 180 degrees to 0 degrees
    horizontal.write(horizonalPos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  horizontal.detach();
  

    // Move down
    vertical.attach(8);
    vertical.write(90);
    delay(250);
    vertical.write(38);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
    vertical.detach();
    delay(210);
}
