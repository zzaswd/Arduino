//=============================
//   LCD Declare
//=============================
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setScreen();
void gameScreen();
void regameScreen();


char score;
int state = 0; // 현재 상태에 따라 무슨 함수를 진행할 지 선택.
int buttonPin = 6; // Regame 선택하기 위한 버튼.


//=============================
//   RFID Declare
//=============================
#include <SPI.h> // SPI 통신을 위한 라이브러리
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc(SS_PIN,RST_PIN);

void pay();


// 카드 결제 관련 시간 체크.
unsigned long check_time = 0;
unsigned long tag_time = 0;
int id_ok;
int count =5;

// 회원 가입 및 금액 충전을 가정.
int id[3][4]={{195,71,234,17},{147,95,142,13}};
int cash[3] = {500,3000,3000}; 
int idx = 0;


//=============================
//   Serial Declare
//=============================
#include <SoftwareSerial.h>
#define TX 7
#define RX 8
SoftwareSerial soft_Serial(TX,RX);
String game_stat ="gameend,";

//=============================
//   Interrupt Declare
//=============================
int pause = 0;
int pause_led = 4;
unsigned long pre_time = 0;
unsigned long cur_time = 0;


//=============================
//   Sound Declare
//=============================
#define sound 5
int Victoty[] ={784, 988, 1175, 1568} ;
int Gameover[] = {247, 233, 220, 208, 196};
int Pay[] = {330, 311, 294};

void setup() {
//=============================
//   LCD Setup
//=============================
  lcd.init();
  lcd.backlight();
  
//=============================
//   RFID Setup
//=============================
  SPI.begin();
  mfrc.PCD_Init(); 
  
//=============================
//   Serial Setup
//=============================
  soft_Serial.begin(9600);

//=============================
//   Interrupt Setup
//=============================
  pinMode(pause_led,OUTPUT);
  attachInterrupt(0, Pause, FALLING);  // Pull_UP 회로 이용.

//=============================
//   Sound Setup
//=============================
  pinMode(sound,OUTPUT);
}

void loop() {
    // state 0 : default screen.
    // state -1 : pay.
    // state 1 : game start.
    // state 2 : regame quest.

    // count 
    if(state ==  0)  {  setScreen();  state =-1;  }
    if(state == -1)     pay();
//    if(count == -1)     state =1;  
    
    if(state ==1)       gameScreen();  
    if(state ==2)       regameScreen();  
  
}

void setScreen(){
    lcd.setCursor(0,0);
    lcd.print("Welcome Baby    ");
    lcd.setCursor(0,1);
    lcd.print("hurry up!       ");
    delay(100);
}

void gameScreen(){
    lcd.clear();
    lcd.print("Get Ready !!!");
    delay(1000);

    int z = 3;
    while(z) {
    lcd.setCursor(6, 1);
    lcd.print(z);
    lcd.print(" ");
    z--;
    tone(sound,784);
    delay(500);
    noTone(sound);
    delay(500);
    }
    

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Game Start !!");
    lcd.setCursor(0, 1);
    lcd.print("    ( ^ _ ^ )   ");
    tone(sound,1175);
    delay(1000);
    game_stat = "gamestart,";
    soft_Serial.print(game_stat+idx+","+pause);
    noTone(sound);
    
    int i = 30;
    lcd.clear();
    
    while(i){
      if(pause == 1){
        lcd.setCursor(0,0);
        lcd.print("    pause !!   ");
        lcd.setCursor(0,1);
        lcd.print("    ( >_< )/    ");
        
      }
           
      else{
          lcd.setCursor(2,0);
          lcd.print("Your ID : ");
          lcd.print(idx);
          
          lcd.setCursor(0,1); 
          lcd.print("Your Time : ");
          lcd.print(i);
          lcd.print("  ");
          i--;
          delay(1000);
      }
    }
    game_stat = "gameend,";
    soft_Serial.print(game_stat+idx+","+pause);
    
    lcd.clear();
    
    lcd.setCursor(1,0);
    lcd.print("Congraturation!");
    lcd.setCursor(0,1);
    lcd.print("Your Score : ");
    

    

    while(soft_Serial.available()){
       score = soft_Serial.read();
       delay(1);
       lcd.print(score);
    }

    // 게임 축하 사운드
    int s = 0;
    while(s<4){
      tone(sound, Victoty[s]);
      delay(500);
      s++;
    }
      
    noTone(sound);
    delay(1000);
    state = 2;
}

void regameScreen(){
    int j = 5;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("One more time ?");
    while(j) {
        if(digitalRead(buttonPin)==HIGH){
          state=-1;
          lcd.clear();
          lcd.print("Restart !");
          delay(1000);
          return;  
        }
        lcd.setCursor(6,1);
        lcd.print(j);
        lcd.print(" ");
        j--;       
        delay(1000);
    }
    lcd.clear();
    lcd.print("Game Over..");
    lcd.setCursor(0,1);
    lcd.print("     ( =_=) //   ");
    // 게임 종료 사운드
    int s = 0;
      while(s<5){
      tone(sound, Gameover[s]);
      delay(200);
      s++;
    }
    delay(300);
    noTone(sound);
    game_stat = "gameend,";
    soft_Serial.print(game_stat+idx+","+pause);
    delay(1700);
    state=0;
}

void pay(){
    static int check = 0;
    if(!mfrc.PICC_IsNewCardPresent()){
      check++;
      if(check>=5)state=0;
      return; 
    }
    
    if(!mfrc.PICC_ReadCardSerial()) // 예외처리 2
      return; 
 

    if(millis()-tag_time<=500){   // 0.5초 안에 연속으로 인식 되지 않으면 --> 즉, 카드를 뗀다면 다시 count =5으로.
      check = 0;
      if(millis() - check_time >= 1000){ // 5초 동안 카드가 지속된다면 count--> 0으로 이동 --> 결제.
          for(int i=0; i<3;i++){
            id_ok =0;
            for(int j=0; j<4;j++){
              if(mfrc.uid.uidByte[j]==id[i][j])
                id_ok++;
            }
            if(id_ok == 4){
                 lcd.setCursor(0,0);
                 lcd.print("Paying....      ");
                 lcd.setCursor(0,1);
                 lcd.print("      ");
                 lcd.print(count);
                 lcd.print("       ");
                 if(count ==0){
                      if(cash[i]-500<0){
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("No.. money OTL  ");
                          delay(2000);
                          state=0;
                          break;
                      }
                       else{
                         cash[i]-=500;
                         lcd.clear();
                         lcd.setCursor(0,0);
                         lcd.print("ID : ");
                         lcd.print(i);
                         lcd.print(" Success.");
                         lcd.setCursor(0,1);
                         lcd.print("balance : "); 
                         lcd.print(cash[i]); 
                         idx = i;                 // 송신 위해 아이디 저장
                          
                         int s = 0;
                           while(s<3){
                             tone(sound, Pay[s]);
                             delay(100);
                             s++;
                           }
                         noTone(sound);
                         delay(1700);
                         state = 1;
                         break;
                       }
                 }
                 Serial.print("count = ");
                 Serial.println(count);
                 count--;
                 check_time = millis();  
                 
                break; 
              }

            }
             if(id_ok < 4){
             Serial.println("Access denied");    
             count = 5;
             delay(500);
             }
          }
    }
    else {count = 5; state =0;}
    tag_time = millis();

}

void Pause(){
  
  cur_time =millis();
  if(cur_time - pre_time >= 500){ 
      pre_time = cur_time;
      pause = !pause;
      soft_Serial.print(game_stat+idx+","+pause);
      digitalWrite(pause_led, pause);
  }
}
