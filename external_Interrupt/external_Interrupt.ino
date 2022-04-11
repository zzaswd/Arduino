#define led 13

volatile byte state = HIGH;

const int duration = 1000; 

unsigned long pre_time = 0;
unsigned long cur_time = 0;


void isr(){
  cur_time =millis();
  if(cur_time - pre_time >= duration){
     Serial.println("인터럽트 발생");
     pre_time = cur_time;
     digitalWrite(led, state);
     state = !state;
     Serial.println(state);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
  attachInterrupt(0,isr,FALLING);
  
}

void loop() {
  
}
