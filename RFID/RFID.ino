#include <SPI.h> // SPI 통신을 위한 라이브러리
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10 // 9,10번을 MFRC522 객체에 넣어야해서 define 해줌

int id[3][4]={{195,71,234,17},{147,95,142,13}};

MFRC522 mfrc(SS_PIN,RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init(); // UID tag 값 확인할 것.
}

void loop() {

  if(!mfrc.PICC_IsNewCardPresent()) // 예외처리 1
    return;

  if(!mfrc.PICC_ReadCardSerial())  // 예외처리 2
    return; 
  int compare;
  for(int i=0; i<3;i++){
    compare =0;
    for(int j=0; j<4;j++){
      if(mfrc.uid.uidByte[j]==id[i][j])
        compare++;    
    }
    if(compare == 4){
       Serial.println("Authorized access");      
       delay(500);
       break;
    }
  }

  if(compare < 4){
     Serial.println("Access denied");      
     delay(500);
  }

}
   
