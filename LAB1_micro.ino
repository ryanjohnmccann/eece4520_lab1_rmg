int red=13;
int yellow=11;
int green=9;
int button=7;
int buttonPress=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(button,INPUT);

}
void loop() {
  while(int buttonPress=1){
  digitalWrite(red,HIGH);
  delay(200);
  digitalWrite(red,LOW);
  delay(200);  
  }
  
  if(digitalRead(button)==HIGH){
  digitalWrite(red,HIGH);
  delay(15000);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  delay(15000);
  digitalWrite(green,LOW);
  digitalWrite(yellow,HIGH);
  delay(3000);
  digitalWrite(yellow,HIGH);
  delay(3000);
  digitalWrite(yellow,LOW);
  }


}
