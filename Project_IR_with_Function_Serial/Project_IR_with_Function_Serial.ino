#include <IRremote.hpp>
#include <Servo.h>
#include <SoftwareSerial.h>

#define TX 12
#define RX 13
SoftwareSerial soft_Serial(TX,RX);

Servo character1;
Servo character2;
Servo character3;

#define IRrev 2
IRrecv irrecv(IRrev);
decode_results res;

unsigned long duration;
unsigned long pre1_time = 0;
unsigned long pre2_time = 0;
unsigned long pre3_time = 0;

int state1 = 0;
int state2 = 0;
int state3 = 0;
unsigned long start_time = 0;

void setup() {
 Serial.begin(9600);
 character1.attach(3);
 character2.attach(5);
 character3.attach(6);
 irrecv.enableIRIn();
 randomSeed(analogRead(0));
 soft_Serial.begin(9600);
}

int score = 0;

void RecvMotor(int game_time,unsigned long start_time);

void loop() {
  if(soft_Serial.available()){
      String mystring = soft_Serial.readString();
      Serial.println(mystring);
  }
      
//      if(digitalRead(6)==HIGH){
//        RecvMotor(10,millis());
//        delay(1000);
//        
//        Serial.println("게임종료");
//        Serial.println(score);
//        score = 0;
//      }   
}

void RecvMotor(int game_time,unsigned long start_time){
  // 다 일어나!!
  character1.write(0);
  character2.write(0);
  character3.write(0);
  unsigned long pre_time = 0;
  int total_time = game_time;
  while(millis()-start_time<=total_time*1000 ){
    if(millis()-pre_time >999){
      Serial.println(game_time--);
      pre_time = millis();
    }
    
    //FF30CF -- 1번   FF18E7 -- 2번   FF7A85 -- 3번
  if (irrecv.decode(&res)){
    switch(res.value){
    // --------------------------------- 캐릭터 1번
    case 0xFF30CF: // <== 눌렸다면
      if(state1==1){
        pre1_time = millis();
        character1.write(90); // 그럼 쓰러져
        state1 = 0;
        score++;
        Serial.println("캐릭터 1 쓰러져");  
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;
    // --------------------------------- 캐릭터 2번
    case 0xFF18E7:
      if(state2==1){
        pre2_time = millis();
        character2.write(90); // 그럼 쓰러져
        state2 = 0;
        score++;
        Serial.println("캐릭터 2 쓰러져");
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;

    // --------------------------------- 캐릭터 3번
    case 0xFF7A85:
      if(state3==1){
        pre3_time = millis();
        character3.write(90); // 그럼 쓰러져
        state3 = 0;
        score++;
        Serial.println("캐릭터 3 쓰러져");
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;

    default: 
          irrecv.resume();
          continue;
          break;
    }
    irrecv.resume();
    Serial.println(res.value,HEX);
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

    Serial.println(score);
  }

  // 다쓰러져
  character1.write(90);
  character2.write(90);
  character3.write(90);
}
