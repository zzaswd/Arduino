#include <SoftwareSerial.h>
///송신부
#define TX 13
#define RX 12

SoftwareSerial soft_Serial(TX,RX); // 객체를 생성하는 코드

void setup() {
  soft_Serial.begin(9600); //TX 6, RX 7. Serial을 시작함.
  Serial.begin(9600);
}

void loop() {
  int i =0;
  int game_period = 30;
  String gamestart= "gamestart#" ;
  String gameend="gameend#";
  Serial.println(gamestart+i+"#"+game_period);
  soft_Serial.print(gamestart+i+"#"+game_period);
  delay(20000);
  soft_Serial.print(gameend+i+"#"+game_period);
  
}
