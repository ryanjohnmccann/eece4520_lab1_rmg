
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define button 2

int buttonpress = 0;
int s;
int maxspeed = 255;

void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void speed(int sp){
  analogWrite(ENABLE,sp);
}

void rotate(int side){
  
  if(side == 1){
    digitalWrite(DIRA,HIGH); //right
    digitalWrite(DIRB,LOW); 
  }
  if(side == 0){
    digitalWrite(DIRA,LOW); //left
    digitalWrite(DIRB,HIGH);   
  } 
    
}

void loop() {

  for(int i = 255; i > 0; i = i - (maxspeed*0.25)){
    if( i == 63){
      s = 0;
    }else{
      s = i;
    }
    if(digitalRead(button) == LOW){
      if(buttonpress == 1){
        buttonpress = 0;
      }else{
         buttonpress =1;
      }
      s = 255; 
    }
    speed(s);
    rotate(buttonpress);
    delay(1000);
    Serial.print("Button = ");
    Serial.print(digitalRead(button));
    Serial.println(); 
    Serial.print("Buttonpress = ");
    Serial.print(buttonpress);
    Serial.println(); 
    Serial.print("Speed = ");
    Serial.print(s);
    Serial.println(); 
    Serial.print("I = ");
    Serial.print(i);
    
    Serial.println();
    Serial.println();  
  }
  
  
    
  

    
}
   
