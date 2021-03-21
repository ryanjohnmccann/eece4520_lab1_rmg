
** Gabriela Borges Lab2 Joystick code **

const int SW_pin = 7; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output joystick
const int Y_pin = 1; // analog pin connected to Y output joystick

int buzz = 2; // buzzer pin
int incomingByte =0; //incoming Byte infoamtion
char control_information;// information sent to phyton code snake game

void setup(){ 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz, LOW);
  Serial.begin(9600); 
}

** joystick code to determin directions d = left, a = right, w = up, s = down otherwise it is blanck **
void joystick(){

 if( analogRead(X_pin) == 0 ){
     control_information = 'd';    
  }
 else if( analogRead(X_pin) == 1023 ){
  control_information = 'a';    
  }
 else if( analogRead(Y_pin) == 1023 ){
    control_information = 'w';  
  }
 else if( analogRead(Y_pin) == 0 ){
    control_information = 's';
  }
 else{
   control_information =' ';
 }
  delay(100);
}
void loop(){
 // buzzer will buzz when apple is eaten
 if (Serial.available() > 0){
  incomingByte = Serial.read();

  if(incomingByte == 'E'){
    digitalWrite(buzz,HIGH);
    delay(300);
    digitalWrite(buzz,LOW);
  }
 }

  joystick();

  Serial.write(control_information);
  Serial.println();
  
  delay(100);
}
