#define changereg A0
#define LED 11

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  int val = analogRead(changereg);

  int lightness = val/4; // 10bit를 8bit로 바꿔야하니깐 4로 나누기
  // map을 사용해도 됌
  //lightness = map(val,0,1023,0,255);

  Serial.println(lightness);
  analogWrite(LED,lightness);
  
  
}
