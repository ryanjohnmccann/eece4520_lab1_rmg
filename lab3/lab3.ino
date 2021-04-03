#include <Wire.h>
// === Include necessary external libraries ===
#include <TimeLib.h>
#include <DS1307RTC.h>

const int ENABLE = 5; // connected to enable pin 1 of the L293D
const int DIRA  = 6; // connected to In pin 1 of the L293D
const int DIRB  = 4; // connected to In pin 2 of the L293D
const int button = 2; // connected to the interupt for button press detection

volatile bool state = LOW; // if state is low it is rotation of motor CC if high it is rotation of motor is C
const double maxspeed = 255; //max speed of the PMW at enable pin of the L293D form 0 - 255
int speed1; //indicated the speed/PMW for the enable pin
int curr_minute = NULL; // Check for a change in minutes

// set up pin output, input, and ISR
void setup() {
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

// controles speed and direction of the motor
void speed(int sp) {
  analogWrite(ENABLE,sp);
  digitalWrite(DIRA,state); 
  digitalWrite(DIRB,!state);
  delay(2000);              
}

//ISR to change rotation of motor
void rotate() {
  state = !state;
}

// speed up the motor at incriments of 2/4, 3/4, and full of max speed for motor
void speedup() {
  for (double i = 63.75; i <= 255; i = i + (maxspeed*0.25)) {
    if (i == 63.75) {
      i=i+maxspeed*0.25; 
      speed1 = i;
    }
    else {
      speed1 = i;
    }
    speed(speed1); 
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

// slow down the motor at incriments of 3/4,1/2,0 of max speed of motor
void slowdown() {
  for (double i = 191.25; i >= 0; i = i - (maxspeed*0.25)) {
    if (i == 63.75) {
      i=i-maxspeed*0.25; 
      speed1 = i;
    }
    else {
      speed1 = i;
    }
    speed(speed1);  
  }
}

// Run fan for 30 seconds, we have reached a new minute
void beg_minute() {
  Serial.print("Here");
  Serial.println();
  // Turn fan on with current speed
  speed(speed1);
  // Speed function seems to have a 2 second delay, delay here is only 28 seconds then
  delay(28000);
  // Turn fan off
  speed(0);
}

// main loop toggles between slowing down and speeding up
void loop() {
  int temp_minute = minute();
  // Minute not declared yet
  if (curr_minute == NULL) {
    curr_minute = temp_minute;
  }
  else {
    // We have reached a new minute, turn the fan on for 30 seconds
    if (temp_minute != curr_minute) {
      curr_minute = temp_minute;
      beg_minute();
    }
  }
  if (speed1 == 0) {
    speedup(); 
  }
  else if (speed1 = 255) {
    slowdown();     
  }
  // === Use these if you'd like to see time ===
//  if (timeStatus() == timeSet) {
//    digitalClockDisplay();
//  } 
//  else {
//    Serial.println("The time has not been set.  Please run the Time");
//    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
//    Serial.println();
//  }
}
   
