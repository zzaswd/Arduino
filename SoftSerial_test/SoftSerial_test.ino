#include <SoftwareSerial.h>
///송신부
#define TX 6
#define RX 7

SoftwareSerial soft_Serial(TX,RX); // 객체를 생성하는 코드


void setup() {
  soft_Serial.begin(9600); //TX 6, RX 7. Serial을 시작함.
  pinMode(11,OUTPUT);
}

void loop() {

  soft_Serial.print(1);
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(500);
  
  soft_Serial.print(2);
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(500);

}
