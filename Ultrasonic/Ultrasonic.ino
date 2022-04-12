
#define trig 2
#define echo 3
#define sound 7

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT); 
  pinMode(echo,INPUT);
  pinMode(sound,OUTPUT);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  double fly_time = pulseIn(echo,HIGH); // echo에 들어온 HIGH 구간의 기간(ms)를 측정해줌.
  double cm_dis = fly_time * 340 / 2 / 10000;
  if(cm_dis <500){
  Serial.println(cm_dis);

    if(cm_dis <20){
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      
      tone(sound,440);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,440);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,330);
      delay(350);
      noTone(sound);
      delay(100);
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,392);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,330);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,330);
      delay(250);
      noTone(sound);
      delay(100);
      tone(sound,294);
      delay(350);
      noTone(sound);
      delay(100);
       
    }
    else if(cm_dis<80)
      tone(sound,1000);
      delay(cm_dis);
      noTone(sound);
      delay(cm_dis);
    }
    else {
      noTone(sound);
  }
  delay(100); // 아두이노가 계산을 하기 위해 일정 시간을 줘야 한다.
  
  


}
