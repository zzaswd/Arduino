#include <SoftwareSerial.h>

// TX 8 RX 9
// BLE 센서
// Serial 통신
#define TX 8
#define RX 9

SoftwareSerial ble(TX,RX);

String myStr = "";
void setup() {
    Serial.begin(9600); // ble값을 보기 위해 추가.
    ble.begin(9600);
    pinMode(13,OUTPUT);
}

void loop() {

     while(ble.available())
    {
      char mychar = (char)ble.read();
      myStr +=mychar;
      delay(5);
      Serial.println(myStr);  
    }
    if(!myStr.equals("")){

      if(myStr == "ledon\r\n")
        digitalWrite(13,HIGH);
      else if(myStr =="ledoff\r\n")
        digitalWrite(13,LOW);
      myStr="";
    }
}
