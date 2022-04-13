#include <IRremote.hpp>
int RECV_PIN = 2;
IRrecv ir(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  ir.enableIRIn();
}

void loop() {
  if(ir.decode(&results)){
    int recvString = results.value;
      if(recvString!=0xFFFFFFFF){
        Serial.println(recvString,HEX); // 수신받은 값을 HEX로 표현
      }
      ir.resume(); // 다음 값 수신
  }
}
//FF30CF -- 1번
//FF18E7 -- 2번
//FF7A85 -- 3번
