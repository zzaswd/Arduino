#include <LiquidCrystal_I2C.h>
#define LED 9
#define CDS A0

LiquidCrystal_I2C lcd(0x27,16,2); // (주소,열,행)

//wire 라이브러리를 통해서 LCD의 주소를 찾아낼 수 있음.
// 그것을 이용하면 주소값이 0x27이 나온다.
// 그 과정을 생략하고 0x27 넣은 것.

void setup() {
  lcd.init(); // 초기화 해주고
  lcd.backlight(); // 백라이트 켜주고
  lcd.print("hello, world");// 커서의 위치를 결정하지 않았으므로 0,0 에서 출력됌
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}

void loop() {


//  if(Serial.available()){
//    lcd.clear();
//    lcd.setCursor(0,1);
//    while(Serial.available()){
//      lcd.write(Serial.read());  
//    }
    
//  }
    int cds_val = analogRead(CDS);

    int led_status;
    if(cds_val >=400){
      digitalWrite(LED,LOW);
      led_status = 0;
    }
    else{
      digitalWrite(LED,HIGH);
      led_status = 1;
    }
    
    lcd.clear(); 
    lcd.setCursor(1,0); 
    lcd.print("ksh");
    lcd.setCursor(0,1);
    lcd.print("CDS:");
    lcd.setCursor(4,1);
    lcd.print(cds_val);
    lcd.setCursor(9,1);
    if(led_status){
      lcd.print("LED ON");
    }
    else{
      lcd.print("LED OFF");
    }
    
    delay(500);  // 적당한 시간을 줘야 clear로 인한 보이지 않는 것을 방지할 수 있음.
}
