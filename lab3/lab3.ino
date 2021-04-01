
const int ENABLE = 5; // connected to enable pin 1 of the L293D
const int DIRA  = 6; // connected to In pin 1 of the L293D
const int DIRB  = 4; // connected to In pin 2 of the L293D
const int button = 2; // connected to the interupt for button press detection

volatile bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
const double maxspeed = 255; //max speed of the PMW at enable pin of the L293D form 0 - 255
int speed1; //indicated the speed/PMW for the enable pin

//set up pin output, input, and ISR
void setup() {
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);
  
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,state);
}

//controles speed and direction of the motor
void speed(int sp){
  analogWrite(ENABLE,sp);
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,!state);
  delay(2000);              
}

//ISR to change rotation of motor
void rotate(){
  state = !state;
}

//speed up the motor at incriments of 2/4, 3/4, and full of max speed for motor
void speedup(){
  for(double i = 63.75; i <= 255; i = i + (maxspeed*0.25)){
    if( i == 63.75){
      i=i+maxspeed*0.25; 
      speed1 = i;
    }else{
      speed1 = i;
    }
    speed(speed1); 
  }
}

//slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
void slowdown(){
  for(double i = 191.25; i >= 0; i = i - (maxspeed*0.25)){
    if( i == 63.75){
      i=i-maxspeed*0.25; 
      speed1 = i;
    }else{
      speed1 = i;
    }
    speed(speed1);  
  }
}

//main loop toggles between slowing down and speeding up
void loop() {

  if(speed1 == 0){
    speedup(); 
  }
  else if(speed1 = 255){
    slowdown();     
  }
  
}
  
  
    
  

    

   
