#define CDS A0
void setup() {
  Serial.begin(9600);
}

void loop() {

  int val = analogRead(CDS);
  Serial.print(val);
  int lightness = map(val,19,800,0,255);
  Serial.print('\t');
  Serial.println(lightness);
  analogWrite(11,lightness);
  
}
