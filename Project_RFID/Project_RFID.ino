#include <SPI.h> // SPI 통신을 위한 라이브러리
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10 // 9,10번을 MFRC522 객체에 넣어야해서 define 해줌
MFRC522 mfrc(SS_PIN,RST_PIN);



// 카드 결제 관련 시간 체크.
unsigned long check_time = 0;
unsigned long tag_time = 0;
int compare;
int count =5;

// 회원 가입 및 금액 충전을 가정.
int id[3][4]={{195,71,234,17},{147,95,142,13}};
int cash[3] = {3000,3000,3000};  


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init(); // UID tag 값 확인할 것.
}

void loop() {
  if(count >=0){
    if(!mfrc.PICC_IsNewCardPresent()) // 예외처리 1
      return;
  
    if(!mfrc.PICC_ReadCardSerial())  // 예외처리 2
      return; 
    
    for(int i=0; i<3;i++){
      compare =0;
      for(int j=0; j<4;j++){
        if(mfrc.uid.uidByte[j]==id[i][j])
          compare++;
      }
      if(compare == 4){
           Serial.println(count);

           if(millis()-tag_time<=500){   // 0.5초 안에 연속으로 인식 되지 않으면 --> 즉, 카드를 뗀다면 다시 count =5으로.
             if(millis() - check_time >= 1000){ // 5초 동안 카드가 지속된다면 count--> 0으로 이동 --> 결제.
                 if(count ==0){
                   cash[i]-=500;
                   Serial.print("결제 되었습니다. 아이디 ");
                   Serial.print(i);
                   Serial.print("님의 잔액은 ");
                   Serial.print(cash[i]);
                   Serial.println("입니다");      
                   count = -1;
                   break;
                 }
                 Serial.print("count = ");
                 Serial.println(count);
                 count--;
                 check_time = millis();
             }
           }
           else count = 5;
           tag_time = millis();
           break; 
      }
    }
    
    if(compare < 4){
       Serial.println("Access denied");    
       count = 5;
       delay(500);
    }
  }

  else {
    Serial.println("게임 시작");
    int i = 30;
    while(i){
         i--;
         Serial.print("게임 시간 : ");
         Serial.println(i);
         delay(1000);
    }
    Serial.println("게임이 종료되었습니다.");
    count = 5;
  }

  
}
   
