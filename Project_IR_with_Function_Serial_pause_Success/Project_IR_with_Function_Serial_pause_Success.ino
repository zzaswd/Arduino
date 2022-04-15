//=============================
//   IR Receive Declare
//=============================

#include <IRremote.hpp>
#define IRrev 2
IRrecv irrecv(IRrev);
decode_results res;

//=============================
//   Serial Declare
//=============================

#include <SoftwareSerial.h>
#define TX 7
#define RX 8
SoftwareSerial soft_Serial(TX,RX);

void check_serial();               // Serial 통신으로 값이 넘어 오는 지 체크

String game_stat;                  //Serial 통신으로 받아오는 데이터 값 저장.
char ID;
char pause;

//=============================
//   Servo Motor Declare
//=============================
#include <Servo.h>

Servo character1;
Servo character2;
Servo character3;

unsigned long duration;
unsigned long pre1_time = 0;      // 이전에 누웠던 시간 체크
unsigned long pre2_time = 0;
unsigned long pre3_time = 0;

int state1 = 0;                   // 모터의 상태 체크
int state2 = 0;
int state3 = 0;

//unsigned long start_time = 0;     // 게임이 시작하는 시간 체크

void RecvMotor(int game_time,unsigned long start_time); // 시간 체크하면서 모터 동작

int score = 0;                    // 점수


void setup() {
  
//=============================
//   Servo Motor Setup
//=============================
 character1.attach(3);
 character2.attach(5);
 character3.attach(6);
 randomSeed(analogRead(0));
//=============================
//   IR Receive Setup
//=============================
 irrecv.enableIRIn();

//=============================
//   Serial Setup
//=============================
 soft_Serial.begin(9600);
}

void loop() {
      check_serial();                   // 시리얼 통신 체크하고, 값 들어오면 전역변수에 저장.
      
      if(game_stat == "gamestart"){     // game_stat이 시작하라고 했다면,
        RecvMotor(30,millis());         // 30초 게임을 시작, 그리고 실행한 시간 저장.
        delay(1000);
        game_stat = "gameend";          // 다시 게임이 시작되지 않도록 game_stat 초기화.
      }    
}

void RecvMotor(int game_time,unsigned long start_time){   // 모터 동작.

  // 전체 모터 기상.
  character1.write(90);
  character2.write(90);
  character3.write(90);
                    
  int total_time = game_time;         // while문에 들어가기 전 전체 게임 시간 설정.
  while(millis()-start_time<=total_time*1000 ){   // 시작 시간으로부터 게임시간이 지날때까지 반복

    check_serial();                               //  while이 매번 돌때마다 시리얼 값 수신. Pause를 감지하기 위함.
    if(pause=='1'){                               //  일시 정지 버튼이 눌렸다면 continue. 단 멈춰있는 시간을 더하기.
      Serial.println("갇혔다");
      delay(500);
      start_time += 500;
      continue;
    }
     
  //FF30CF -- 1번   FF18E7 -- 2번   FF7A85 -- 3번
    
  if (irrecv.decode(&res)){                         //  IR 값 수신.
    switch(res.value){
    // --------------------------------
    // 캐릭터 1번 
    // 눌렸을 때 서있었다면 쓰러지고 득점. 그리고 이전 눌린시간 초기화.
    // 넘어져있었다면 감점.
    // --------------------------------
    case 0xFF30CF: 
      if(state1==1){
        pre1_time = millis();
        character1.write(170); // 그럼 쓰러져
        state1 = 0;
        score++;
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;
      
    // --------------------------------
    // 캐릭터 2번 이하 동일.
    // -------------------------------- 
    case 0xFF18E7:
      if(state2==1){
        pre2_time = millis();
        character2.write(170); 
        state2 = 0;
        score++;
        Serial.println("캐릭터 2 쓰러져");
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;
      
    // --------------------------------
    // 캐릭터 3번 이하 동일.
    // -------------------------------- 
    case 0xFF7A85:
      if(state3==1){
        pre3_time = millis();
        character3.write(170); 
        state3 = 0;
        score++;
        Serial.println("캐릭터 3 쓰러져");
      }
      else{
        score--;
        Serial.println("너 감점!");
      }
      break;

    // --------------------------------
    // 쓰레기 값 필터링.
    // 모터 전류량 때문에 쓰레기 값이 많이 들어와서 필수.
    // --------------------------------
    default: 
          irrecv.resume();
          continue;
          break;
    }
    irrecv.resume();    // 정상적일 때 역시 값 다시 받기.
  }
    duration = random(500,5000);  // 일어나는 속도를 랜덤으로 하기 위해 선언

    // --------------------------------
    // 캐릭터 1번 
    // 넘어져있고 특정 시간이 지나면 기상.
    // state와 pre_time 초기화
    // --------------------------------
    
    if(state1 == 0 && millis()-pre1_time >= duration){
      character1.write(90); 
      state1 = 1;
      pre1_time = millis();
      Serial.println("캐릭터 1 일어나");
    }

    // --------------------------------
    // 캐릭터 2번 이하 동일.
    // -------------------------------- 
    if(state2 == 0 && millis()-pre2_time >= duration){
      character2.write(90); 
      state2 = 1;
      pre2_time = millis();
      Serial.println("캐릭터 2 일어나");
    }
    
    // --------------------------------
    // 캐릭터 3번 이하 동일.
    // -------------------------------- 
    if(state3 == 0 && millis()-pre3_time >= duration){
      character3.write(90); // 그럼 일어나
      state3 = 1;
      pre3_time = millis();
      Serial.println("캐릭터 3 일어나");
    }
      
  }

  // 게임이 종료되면 전부 눕기. 그리고 점수를 보내고 초기화 
  character1.write(170);
  character2.write(170);
  character3.write(170);
  soft_Serial.print(score);
  score = 0;
}



// Serial 통신으로 값이 넘어 오는 지 체크하는 함수
void check_serial(){
      char mystring[20];
      int i= 0;    
      
      while(soft_Serial.available()){       // 버퍼에 있는 값을 모두 읽어와서 mystring이라는 배열에 저장.
        mystring[i++] = soft_Serial.read();
        delay(1);                           // delay 1이 없다면 버퍼 값 읽을 시간이 부족해서 값이 튄다.
      }
      mystring[i] = '\0';

      // 총 세 개의 값을 합쳐서 보내기 때문에 ,을 기준으로 세번의 파싱 진행.
      // 파싱된 값은 각각 전역변수에 저장.
      char* ptr = strtok(mystring, ",");
      if(ptr!=NULL) game_stat = ptr;
  
      ptr = strtok(NULL,",");
      if(ptr!=NULL) ID = *ptr;
           
      ptr = strtok(NULL,",");
      if(ptr!=NULL) pause = *ptr; 
      
}
