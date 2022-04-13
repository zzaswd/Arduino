#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int buttonPin = 6;

void setScreen();
void gameScreen();
void regameScreen();

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

int compare = 0;

void loop() {
  if(compare == 0){
     setScreen();
  }    
  if(digitalRead(buttonPin)==1){
    compare =1;
  }

  if(compare ==1){
     gameScreen();
  }
  if(compare ==2){
    regameScreen();
  }
}

void setScreen(){
    lcd.setCursor(0,0);
    lcd.print("WellCome Baby");
    lcd.setCursor(0,1);
    lcd.print("hurry up!");
    delay(500);
}

void gameScreen(){
    lcd.clear();
    lcd.print("Get Ready !!!");
    delay(1000);

    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("3");
    delay(1000);

    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("2");
    delay(1000);

    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("1");
    delay(1000);

    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Game Start");
    delay(1000);
    
    int i = 3;
    lcd.clear();
    lcd.setCursor(2,0); 
    lcd.print("your Time : ");
    while(i){
      lcd.setCursor(6,1);
      lcd.print(i);
      lcd.print(" ");
      i--;
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Congraturation!");
    lcd.setCursor(2,1);
    lcd.print("your score : ");
    delay(1000);
    compare = 2;
}

void regameScreen(){
    int j = 5;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("one more time ?");
    while(j) {
        if(digitalRead(buttonPin)==HIGH){
          compare=1;
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
    delay(1000);
    compare=0;
}
