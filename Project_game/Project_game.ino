#include <IRremote.hpp>
#include <Servo.h>

Servo character1;
Servo character2;
Servo character3;

#define IRrev A1
IRrecv irrecv(IRrev);
decode_results res;

unsigned long duration;
unsigned long pre1_time = 0;
unsigned long pre2_time = 0;
unsigned long pre3_time = 0;

int state1 = 0;
int state2 = 0;
int state3 = 0;

void setup() {
 Serial.begin(9600);
 character1.attach(3);
 character2.attach(5);
 character3.attach(6);
 irrecv.enableIRIn();
 randomSeed(analogRead(0));
}



void loop() {

//  if (irrecv.decode(&res)){
//    Serial.println(res.value,HEX);
//    irrecv.resume();
//  }
// E1A2748B --  <==
//  E1A2847B -- 가운데
// E1A254AB -- ==>


  if (irrecv.decode(&res)){
    irrecv.resume();
    Serial.println(res.value,HEX);
    switch(res.value){
    // --------------------------------- 캐릭터 1번
    case 0xE1A2748B: // <== 눌렸다면
      if(state1==1){
        pre1_time = millis();
        character1.write(90); // 그럼 쓰러져
        state1 = 0;
        Serial.println("캐릭터 1 쓰러져");  
      }
      else{
        Serial.println("너 감점!");
      }
      break;
    // --------------------------------- 캐릭터 2번
    case 0xE1A2847B:
      if(state2==1){
        pre2_time = millis();
        character2.write(90); // 그럼 쓰러져
        state2 = 0;
        Serial.println("캐릭터 2 쓰러져");
      }
      else{
        Serial.println("너 감점!");
      }
      break;

    // --------------------------------- 캐릭터 3번
    case 0xE1A254AB:
      if(state3==1){
        pre3_time = millis();
        character3.write(90); // 그럼 쓰러져
        state3 = 0;
        Serial.println("캐릭터 3 쓰러져");
      }
      else{
        Serial.println("너 감점!");
      }
      break;
    }
  }

  duration = random(500,5000);

    
  if(state1 == 0 && millis()-pre1_time >= duration){
    character1.write(0); // 그럼 일어나
    state1 = 1;
    pre1_time = millis();
    Serial.println("캐릭터 1 일어나");
  }
    
  if(state2 == 0 && millis()-pre2_time >= duration){
    character2.write(0); // 그럼 일어나
    state2 = 1;
    pre2_time = millis();
    Serial.println("캐릭터 2 일어나");
  }
  
  if(state3 == 0 && millis()-pre3_time >= duration){
    character3.write(0); // 그럼 일어나
    state3 = 1;
    pre3_time = millis();
    Serial.println("캐릭터 3 일어나");
  }
    

 

}
