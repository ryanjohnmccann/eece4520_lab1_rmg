//Library for LCD
#include <LiquidCrystal.h>



//pins for motor
const int ENABLE = 5; // connected to enable pin 1 of the L293D
const int DIRA  = 6; // connected to In pin 1 (pin2) of the L293D
const int DIRB  = 4; // connected to In pin 2 (pin8) of the L293D
const int button = 2; // connected to the interupt for button press detection

bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
double speed1[4] = {0,127.5,191.25,255}; //indicated the speed/PMW for the enable pin

//Pins for LCD displacy
const int rs = 12, en =11, d4 = 7, d5 = 8, d6 =9, d7 = 10;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
 

//set up pin output, input, ISR, and RCT 
void setup() {
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,state);

  lcd.begin(16,2);

}

//controles speed and direction of the motor
void speed(int sp){
  analogWrite(ENABLE,sp);            
}

//ISR to change rotation of motor
void rotate(){
  state = !state;
  direction();
  displayrotation();
}
//indicated direction of motor
void direction(){
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,!state);
}
//speed up the motor at incriments of 2/4, 3/4, and full of max speed for motor
void speedup(){
  for(int i = 0; i <= 3 ; i++){
    speed(speed1[i]); 
    direction();
    displayspeed(speed1[i]);
    displayrotation();
    delay(2000); 
  }
}

//slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
void slowdown(){
  for(int i = 3; i >= 0; i--){
    speed(speed1[i]); 
    direction();
    displayspeed(speed1[i]);
    displayrotation();
    delay(2000); 
  }
}
//displays speed
void displayspeed(double dis){
  lcd.setCursor(0,0);
  lcd.print("Speed:");
  lcd.setCursor(7,0);
  lcd.print(dis);
  if(dis == 0.00){
    lcd.print("  ");
  }
}
//displays direction
void displayrotation(){
  lcd.setCursor(14,0);
  if(state == LOW){
    lcd.print("CC");
  }
  if(state == HIGH){
    lcd.print("C ");
  }
}

//main loop toggles between slowing down and speeding up
void loop() { 
  speedup();
  slowdown();
  
}
  
  
    
  

    

   
