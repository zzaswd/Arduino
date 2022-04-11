#define RED 11
#define GREEN 10
#define BLUE 9

void setup() {
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);  
}

void loop() {
  
  if(Serial.available() > 0){
    int data = Serial.read();
    // 데이터가 제대로 수신됐는 지 ECHO 기능 설정
    Serial.println(data);
    if(data== '1'){
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
      
    }
    else if(data == '2'){
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,LOW);
    }
    else if(data == '3'){
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,HIGH);
    }
    else {
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
      
    }
  }
  

}
