#include <IRremote.hpp>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <MsTimer2.h>

#define TX 7
#define RX 8
SoftwareSerial soft_Serial(TX,RX);

Servo character1;
Servo character2;
Servo character3;

#define IRrev A2
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

String game_stat;
char ID;
char pause;

void isr();

void setup() {
 Serial.begin(9600);
 character1.attach(3);
 character2.attach(5);
 character3.attach(6);
 irrecv.enableIRIn();
 randomSeed(analogRead(0));
 soft_Serial.begin(9600);
 MsTimer2::set(200,isr);
 MsTimer2::start();
 
}


int score = 0;

void RecvMotor(int game_time,unsigned long start_time);




void loop() {
      

//     if (game_stat == "gameend"){
//        Serial.println("end");

      if(game_stat == "gamestart"){
        RecvMotor(30,millis());
        delay(1000);
        game_stat = "gameend";
        Serial.println("게임종료");
      }
      
}

void RecvMotor(int game_time,unsigned long start_time){
  // 다 일어나!!

  character1.write(0);
  character2.write(0);
  character3.write(0);
  unsigned long pre_time = 0;
  int total_time = game_time;
  while(millis()-start_time<=total_time*1000 ){
      
    if(pause=='1'){
      Serial.println("갇혔다");
      delay(500);
      start_time += 500;
      continue;
    }
      
    if(millis()-pre_time >999){
      Serial.println(game_time--);
      pre_time = millis();
    }
    
    //FF30CF -- 1번   FF18E7 -- 2번   FF7A85 -- 3번
  if (irrecv.decode(&res)){
    Serial.println(res.value,HEX);
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
    Serial.print(" score = ");
    Serial.println(score);
    
    irrecv.resume();
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

  // 다쓰러져
  character1.write(90);
  character2.write(90);
  character3.write(90);
  soft_Serial.print(score);
  score = 0;
}


void isr(){
      char mystring[20];
      int i= 0;
      while(soft_Serial.available()){
        mystring[i++] = soft_Serial.read();
        delay(1);
      }
      mystring[i] = '\0';
      
      char* ptr = strtok(mystring, ",");
      if(ptr!=NULL){
      game_stat = ptr;
      Serial.print("game_stat = ");
      Serial.println(game_stat);   
      }
      ptr = strtok(NULL,",");
      if(ptr!=NULL){
      ID = *ptr;
      Serial.print("ID = ");
      Serial.println(ID);   
      }
      ptr = strtok(NULL,",");
      
      if(ptr!=NULL){
      pause = *ptr;
      Serial.print("pause = ");
      Serial.println(pause);   
      }  
      
}
