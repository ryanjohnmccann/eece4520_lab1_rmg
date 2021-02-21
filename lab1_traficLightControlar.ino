int yellowpin = 4;
int redpin = 6;
int greenpin =5;
int buzz =  12;
int button = 10;
bool  buttonpress = true;


void setup() {
  pinMode(yellowpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(redpin,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  
}

void toggle_led(int Pin, int delay1){
  for(delay1 ; delay1 >=0; delay1--){
    digitalWrite(Pin,HIGH);
    delay(1);
    if(delay1 == 3000){
      digitalWrite(buzz,HIGH);
      delay(100);
      digitalWrite(buzz,LOW);
    }
  }
  digitalWrite(Pin,LOW);
}

void loop() {
  while(buttonpress){
    if(digitalRead(button) == LOW){
      buttonpress = false;
      break;  
    }
    digitalWrite(redpin,HIGH);
    delay(100);
    digitalWrite(redpin,LOW);
    delay(100);
  }
 
  for(int Pin = 6 ; Pin >= 4 ; Pin--){
      if( Pin == 4){ 
       toggle_led(Pin, 3000);
      }
      else{
        toggle_led(Pin, 15000);        
      } 
  }
}
