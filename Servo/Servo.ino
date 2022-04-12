#include <Servo.h>
#define changereg A0

Servo myServo;

void setup() {
  myServo.attach(11);

}

void loop() {
  int val = map(analogRead(changereg),0,1023,0,180);
    
  myServo.write(val);
  
}
