
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <DS1307RTC.h>



//pins for motor
const int ENABLE = 5; // connected to enable pin 1 of the L293D
const int DIRA  = 6; // connected to In pin 1 (pin2) of the L293D
const int DIRB  = 4; // connected to In pin 2 (pin8) of the L293D
const int button = 2; // connected to the interupt for button press detection

bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
double speed1[4] = {0,127.5,191.25,255}; //indicated the speed/PMW for the enable pin
int curr_minute = -1; // Check for a change in minutes

//Pins for LCD displacy
const int rs = 12, en =11, d4 = 7, d5 = 8, d6 =9, d7 = 10;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
 

//set up pin output, input, ISR, and RCT 
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,state);
  
   while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");

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
    DisplayTime ();
    delay(2000); 
  }
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

// Will print time in an easy to read manner
void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

//slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
void slowdown(){
  for(int i = 3; i >= 0; i--){
    speed(speed1[i]); 
    direction();
    displayspeed(speed1[i]);
    displayrotation();
    DisplayTime ();
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
//displays speed
void DisplayTime (){
  lcd.setCursor(0,1);
  lcd.print(hour());
  lcd.print(":");
  lcd.print(minute());
  lcd.print(":");
  lcd.print(second());
}

//main loop toggles between slowing down and speeding up
void loop() { 
   int temp_minute = minute();
  // Minute not declared yet
  if (curr_minute == -1) {
    curr_minute = temp_minute;
  }
  speedup();
  slowdown();
   // === Use these if you'd like to see time ===
  if (timeStatus() == timeSet) {
    digitalClockDisplay();
  } 
  else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
  }
}
  
  

  










































//#include <Wire.h>
//// === Include necessary external libraries ===
//#include <TimeLib.h>
//#include <DS1307RTC.h>
//#include <LiquidCrystal.h>
//// need to have that file to get the lcd to work 
//
//const int ENABLE = 5; // connected to enable pin 1 of the L293D
//const int DIRA  = 6; // connected to In pin 1 of the L293D
//const int DIRB  = 4; // connected to In pin 2 of the L293D
//const int button = 2; // connected to the interupt for button press detection
//
//volatile bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
//const double maxspeed = 255; //max speed of the PMW at enable pin of the L293D form 0 - 255
//int speed1; //indicated the speed/PMW for the enable pin
//int curr_minute = -1; // Check for a change in minutes
//
//
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//// used for the LCD 
//// vss is grounded 
////vdd is postive 
////v0 is connected to the middle leg of potentiometer 
////rs to pins 7
////E pin 8
////d4 to 9 
////d5 to 10 
////d6 to 11
////d7 to 12
////a to positve terminal 
////k is negative 
////leg one of the potentiomer is positve 
////third leg of the potentiometer is negative 
//
//// set up pin output, input, and ISR
//void setup() {
//  lcd.begin(16, 2);
//  Serial.begin(9600);
//  pinMode(ENABLE,OUTPUT);
//  pinMode(DIRA,OUTPUT);
//  pinMode(DIRB,OUTPUT);
//  pinMode(button, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);
//  digitalWrite(DIRA,state); 
//  digitalWrite(DIRB,state);
//
//  while (!Serial) ; // wait until Arduino Serial Monitor opens
//  setSyncProvider(RTC.get);   // the function to get the time from the RTC
//  if(timeStatus()!= timeSet) {
//     Serial.println("Unable to sync with the RTC");
//  }
//  else{
//     Serial.println("RTC has set the system time");
//     Serial.println("Displaying the LCD");
//  }
//  lcd.clear();
//  
//}
//
//// controles speed and direction of the motor
//void speed(int sp) {
//  analogWrite(ENABLE,sp);
//  digitalWrite(DIRA,state); 
//  digitalWrite(DIRB,!state);
//  delay(2000);              
//}
//
////ISR to change rotation of motor
//void rotate() {
//  state = !state;
//}
//
//// speed up the motor at incriments of 2/4, 3/4, and full of max speed for motor
//void speedup() {
//     
//  for (double i = 63.75; i <= 255; i = i + (maxspeed*0.25)) {
////    
//     lcd.clear();
//     lcd.setCursor(0, 0); //sets the postiion for the time 
//     lcd.print(hour());
//     lcd.print(":");
//     lcd.print(minute());
//     lcd.print(":");
//     lcd.print(second());
//     lcd.setCursor(0, 1);
//     lcd.print("C:");
//     lcd.print(speed1);
//     Serial.println(speed1);
//
//
//
//    if (i == 63.75) {
//      i=i+maxspeed*0.25; 
//      speed1 = i;
//    }
//    else {
//      speed1 = i;
//    }
//    speed(speed1); 
//  
//     delay(5000);
//  }
//     
//}
//
//void digitalClockDisplay() {
//  // digital clock display of the time
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.print(" ");
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year()); 
//  Serial.println(); 
//  lcd.setCursor(0, 0);
//  lcd.print(month());
//}
//
//// Will print time in an easy to read manner
//void printDigits(int digits) {
//  // utility function for digital clock display: prints preceding colon and leading 0
//  Serial.print(":");
//  if(digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//}
//
//// slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
//void slowdown() {
//
//  for (double i = 191.25; i >= 0; i = i - (maxspeed*0.25)) {
//     //lcd.setCursor(0, 1);
//     
//     lcd.clear();     
//     lcd.setCursor(0, 0);
//     lcd.print(hour()); 
//     lcd.print(":");
//     lcd.print(minute());
//     lcd.print(":");
//     lcd.print(second());
//     lcd.setCursor(0, 1);
//     lcd.print("C:");
//     lcd.print(speed1);
//     Serial.println(speed1);
// 
//    if (i == 63.75) {
//      i=i-maxspeed*0.25; 
//      speed1 = i;
//    }
//    else {
//      speed1 = i;
//    }
//    speed(speed1);
//    
//  delay(5000);
//  }
//}
//
//// Run fan for 30 seconds, we have reached a new minute
//void beg_minute() {
//  Serial.print("Here");
//  Serial.println();
//  // Turn fan on with current speed
//  speed(maxspeed);
//  // Speed function seems to have a 2 second delay, delay here is only 28 seconds then
//  delay(28000);
//  // Turn fan off
//  speed(0);
//}
//
//// main loop toggles between slowing down and speeding up
//void loop() {
//  int temp_minute = minute();
//  // Minute not declared yet
//  if (curr_minute == -1 ) {
//    curr_minute = temp_minute;
//  }
//  else {
//    // We have reached a new minute, turn the fan on for 30 seconds
//    if (temp_minute != curr_minute) {
//      curr_minute = temp_minute;
//      beg_minute();
//    }
//  }
//  if (speed1 == 0) {
//    speedup(); 
//  }
//  else if (speed1 = 255) {
//    slowdown();     
//  }
//  // === Use these if you'd like to see time ===
//  if (timeStatus() == timeSet) {
//    digitalClockDisplay();
//  } 
//  else {
//    Serial.println("The time has not been set.  Please run the Time");
//    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
//    Serial.println();
//  }
//    
//}




























































//#include <Wire.h>
//// === Include necessary external libraries ===
//#include <TimeLib.h>
//#include <DS1307RTC.h>
//#include <LiquidCrystal.h>
//
//const int ENABLE = 5; // connected to enable pin 1 of the L293D
//const int DIRA  = 6; // connected to In pin 1 of the L293D
//const int DIRB  = 4; // connected to In pin 2 of the L293D
//const int button = 2; // connected to the interupt for button press detection
//
//volatile bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
//const double maxspeed = 255; //max speed of the PMW at enable pin of the L293D form 0 - 255
//int speed1; //indicated the speed/PMW for the enable pin
//int curr_minute = -1; // Check for a change in minutes
//
//
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//
//// set up pin output, input, and ISR
//void setup() {
//  lcd.begin(16, 2);
//
//
//  Serial.begin(9600);
//  pinMode(ENABLE,OUTPUT);
//  pinMode(DIRA,OUTPUT);
//  pinMode(DIRB,OUTPUT);
//  pinMode(button, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(button), rotate, FALLING);
//  digitalWrite(DIRA,state); 
//  digitalWrite(DIRB,state);
//
//  while (!Serial) ; // wait until Arduino Serial Monitor opens
//  setSyncProvider(RTC.get);   // the function to get the time from the RTC
//  if(timeStatus()!= timeSet) {
//     Serial.println("Unable to sync with the RTC");
//  }
//  else{
//     Serial.println("RTC has set the system time");
//     Serial.println("Displaying the LCD");
//  }
//  lcd.clear();
//  
//}
//
//// controles speed and direction of the motor
//void speed(int sp) {
//  analogWrite(ENABLE,sp);
//  digitalWrite(DIRA,state); 
//  digitalWrite(DIRB,!state);
//  delay(2000);              
//}
//
////ISR to change rotation of motor
//void rotate() {
//  state = !state;
//}
//
//// speed up the motor at incriments of 2/4, 3/4, and full of max speed for motor
//void speedup() {
//     
//  for (double i = 63.75; i <= 255; i = i + (maxspeed*0.25)) {
//    
//     lcd.clear();
//     lcd.setCursor(0, 1);
//     lcd.print("C:");
//     lcd.print(speed1);
//     Serial.println(speed1);
//     lcd.setCursor(0, 0);
//     lcd.clear();
//     lcd.print(hour());
//     lcd.print(":");
//     lcd.print(minute());
//     lcd.print(":");
//     lcd.print(second());
//
//
//
//    if (i == 63.75) {
//      i=i+maxspeed*0.25; 
//      speed1 = i;
//    }
//    else {
//      speed1 = i;
//    }
//    speed(speed1); 
//  
//     delay(5000);
//  }
//     
//}
//
//void digitalClockDisplay() {
//  // digital clock display of the time
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.print(" ");
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year()); 
//  Serial.println(); 
//  lcd.setCursor(0, 0);
//  lcd.print(month());
//  //lcd.print(temp_minute);
//}
//
//// Will print time in an easy to read manner
//void printDigits(int digits) {
//  // utility function for digital clock display: prints preceding colon and leading 0
//  Serial.print(":");
//  if(digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//}
//
//// slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
//void slowdown() {
//
//  for (double i = 191.25; i >= 0; i = i - (maxspeed*0.25)) {
//     //lcd.setCursor(0, 1);
//     
//     lcd.clear();
//     lcd.setCursor(0, 1);
//     lcd.print("C:");
//     lcd.print(speed1);
//     Serial.println(speed1);
//     
//     lcd.setCursor(0, 0);
//     lcd.print(hour()); 
//     lcd.print(":");
//     lcd.print(minute());
//    lcd.print(":");
//   lcd.print(second());
//
//// if (i == 63.75) {
////     lcd.clear();
////     lcd.print("C:");
////     lcd.print("2/4");
////      
////    }
////    if (i == 191.25 ) {
////     lcd.clear();
////     lcd.print("C:");
////     lcd.print("3/4");
////      
////    }
////    if (i == 255 ) {
////     lcd.clear();
////     lcd.print("C:");
////     lcd.print("Full speed ");
////      
////    }
//    if (i == 63.75) {
//      i=i-maxspeed*0.25; 
//      speed1 = i;
//    }
//    else {
//      speed1 = i;
//    }
//    speed(speed1);
//    
//  delay(5000);
//  }
//}
//
//// Run fan for 30 seconds, we have reached a new minute
//void beg_minute() {
//  Serial.print("Here");
//  Serial.println();
//  // Turn fan on with current speed
//  speed(maxspeed);
//  // Speed function seems to have a 2 second delay, delay here is only 28 seconds then
//  delay(28000);
//  // Turn fan off
//  speed(0);
//}
//
//// main loop toggles between slowing down and speeding up
//void loop() {
//  int temp_minute = minute();
//  // Minute not declared yet
//  if (curr_minute == -1 ) {
//    curr_minute = temp_minute;
//  }
//  else {
//    // We have reached a new minute, turn the fan on for 30 seconds
//    if (temp_minute != curr_minute) {
//      curr_minute = temp_minute;
//      beg_minute();
//    }
//  }
//  if (speed1 == 0) {
//    speedup(); 
//  }
//  else if (speed1 = 255) {
//    slowdown();     
//  }
//  // === Use these if you'd like to see time ===
//  if (timeStatus() == timeSet) {
//    digitalClockDisplay();
//  } 
//  else {
//    Serial.println("The time has not been set.  Please run the Time");
//    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
//    Serial.println();
//  }
//    
//}
