#include <SoftwareSerial.h>
///수신부
#define TX 6
#define RX 7

SoftwareSerial soft_Serial(TX,RX); // 객체를 생성하는 코드


void setup() {
  soft_Serial.begin(9600); //TX 6, RX 7. Serial을 시작함.
  Serial.begin(9600);
  pinMode(11,OUTPUT);
}

void loop() {

  if(soft_Serial.available()){
    String mystring = soft_Serial.readString();
    Serial.println(mystring);
    if(mystring=="ledon"){
      digitalWrite(11,HIGH);      
    }
    else{
      digitalWrite(11,LOW);
    }
  }
  
  

}
