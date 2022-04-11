#define RED 11
#define BLUE 9
#define GREEN 10


void setup() {
  pinMode(13,OUTPUT); 
  pinMode(BLUE,OUTPUT); //B
  pinMode(GREEN,OUTPUT); //G
  pinMode(RED,OUTPUT); //R

}

void loop() {

  for(int i = 0; i<256;i=i+10){
    analogWrite(RED,i);
    delay(50);
  }

  for(int i = 255; i>=0;i=i-10){
    analogWrite(RED,i);
    delay(50);
  }
//----------------------

  for(int i = 0; i<256;i=i+10){
    analogWrite(BLUE,i);
    delay(50);
  }

  for(int i = 255; i>=0;i=i-10){
    analogWrite(BLUE,i);
    delay(50);
  }

  //----------------------
  for(int i = 0; i<256;i=i+10){
    analogWrite(GREEN,i);
    delay(50);
  }

  for(int i = 255; i>=0;i=i-10){
    analogWrite(GREEN,i);
    delay(50);
  }
  
}
