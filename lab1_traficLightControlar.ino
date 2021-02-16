int yellowpin = 25;
int redpin = 23;
int greenpin =24;
int buzz =  45;
int button = 35;
int buttonpress = 0;


void setup() {
  pinMode(yellowpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(redpin,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(button,INPUT);
  
}

void loop() {
  while(buttonpress ==0){
    if(digitalRead(button) == HIGH){
      buttonpress = 1;
    }
    digitalWrite(redpin,HIGH);
    delay(1000);
    digitalWrite(redpin,LOW);
    delay(1000);
  }  
 
  for(int Pin = 23; Pin <= 25 ; Pin++){
      if( Pin == 25){
        digitalWrite(Pin, HIGH);
        digitalWrite(buzz,HIGH);
        delay(1000);
        digitalWrite(buzz,LOW);
      
        delay(2000);
        digitalWrite(Pin,LOW);
       
       
      }
      else{
        digitalWrite(Pin, HIGH);
        delay(12000);
     
        digitalWrite(buzz,HIGH);
        delay(1000);
        digitalWrite(buzz,LOW);

        delay(2000);
        digitalWrite(Pin,LOW);
     
        
      } 
  }
}
