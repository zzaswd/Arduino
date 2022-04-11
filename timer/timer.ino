#include <MsTimer2.h>

#define led 13

void isr(){
  static boolean state = HIGH; // 자료형이 Boolean이라 True or False
  // static을 선언하지 않으면 ISR이 실행될때마다 High
  digitalWrite(led,state);
  state = !state; 
}

void setup() {
  MsTimer2::set(1000,isr);
  MsTimer2::start();
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
