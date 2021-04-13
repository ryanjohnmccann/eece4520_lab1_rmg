#include <Wire.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

//pins for motor
const int ENABLE = 3; // connected to enable pin 1 of the L293D
const int DIRA  = 6; // connected to In pin 1 (pin2) of the L293D
const int DIRB  = 4; // connected to In pin 2 (pin8) of the L293D
const int button = 2; //button pin

double speed1[4] = {0,127.5,191.25,255}; //indicated the speed/PMW for the enable pin
volatile bool state = LOW; // starts direction of CC
int i = 0; // used to move within speed1 to change speed

//Pins for LCD displacy
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 =11, d7 = 12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

//used with timer1 to update LCD
volatile bool update_lcd; 

//used with timer4 to count every timerperiod#
int TIMEPERIOD = 11;
volatile int counter = 0;

int curr_minute = -1; // Check for a change in minutes

//set up pin output, input, ISR, and RCT 
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,state);
  
  //Timer intrupte for LCD display every 1 sec
  noInterrupts();
  TCCR1A = 0;   //initialized timer1
  TCCR1B =0;
  TCCR1B |= 0b00000100; //256 prescaler
  TIMSK1 |= 0b00000001; //enable overflow interupt
  interrupts();

  //Timer interupte to update speed
  setupTimer4();

  //button intrupte
  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);

  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
}

//timer interupt to incriment speed 
//runs every 1 second, use count loop to increase/decrease time
void setupTimer4(){
  noInterrupts();
  // Clear registers
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4B |= 0b00000100;
  TIMSK4 |= 0b00000001; 
  interrupts();
}

//button interupte to set state to change direction
//runs on timer0
void rotate(){
  state = !state;
}

//interupt to update desplay every 1 sec
//runs on timer1
ISR(TIMER1_OVF_vect){
  update_lcd =true;
}

//interupt to update speed
//runns on timer 4
ISR(TIMER4_OVF_vect){
   counter = counter +1;
}

//displays speed
void display(double dis){
  lcd.setCursor(0,0);
  lcd.print("Speed:");
  lcd.setCursor(7,0);
  lcd.print(dis);
  if(dis == 0.00){
    lcd.print("  ");
  }
  lcd.setCursor(14,0);
  if(state == LOW){
    lcd.print("CC");
  }
  if(state == HIGH){
    lcd.print("C ");
  }
  lcd.setCursor(0,1);
  lcd.print(hour());
  lcd.print(":");
  lcd.print(minute());
  lcd.print(":");
  lcd.print(second());
}


// Run fan for 30 seconds, we have reached a new minute
void beg_minute(int sp) {
  analogWrite(ENABLE,speed1[sp]); //changes speed of motor uses timer3 since on pin3
  delay(30000);
}


//main loop toggles between slowing down and speeding up
void loop() {
   int temp_minute = minute();
   //updates LCD when it s true every 1sec
   if(update_lcd == true){
    update_lcd = false;
    display(speed1[i]);
   }
   //changes speed every time it reaches timeperiod value set
   //counter in incrimented every 1 sec with timer4
   if(counter >= TIMEPERIOD){
     i = i+1;
     if(i == 4){
       i = 0;
     }
     counter = 0;
   }
  // Minute not declared yet
  if (curr_minute == -1) {
    curr_minute = temp_minute;
  }
  else {
    // We have reached a new minute, turn the fan on for 30 seconds
    if (temp_minute != curr_minute) {
      curr_minute = temp_minute;
      beg_minute(i);
    }
   }
   
   analogWrite(ENABLE,speed1[i]); //changes speed of motor uses timer3 since on pin3
   //indicates direction of motor when state is low it is CC and high it is C
   digitalWrite(DIRA,state); 
   digitalWrite(DIRB,!state);
 
}
