#define Down 7
#define Up 6

void setup() {
  pinMode(Down,INPUT);
  pinMode(Up,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(" Down : ");
  Serial.print(digitalRead(Down));
  
  Serial.print("     Up : ");
  Serial.println(digitalRead(Up));


}
