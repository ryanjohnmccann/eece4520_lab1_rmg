#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;

const int SW_pin = 7; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output joystick
const int Y_pin = 1; // analog pin connected to Y output joystick

int buzz = 2; // buzzer pin
int incomingByte = 0; //incoming Byte infoamtion
char control_information;// information sent to python code snake game

void setup() { 
  Serial.begin(9600); 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
//  Serial.println("Initialize MPU6050");
  // Make sure MPU is initialized
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  checkSettings();
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz, LOW);
}


void checkSettings() {
  Serial.println();
  
//  Serial.print(" * Sleep Mode:        ");
//  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
//  
//  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
//  Serial.print(" * Gyroscope offsets: ");
//  Serial.print(mpu.getGyroOffsetX());
//  Serial.print(" / ");
//  Serial.print(mpu.getGyroOffsetY());
//  Serial.print(" / ");
//  Serial.println(mpu.getGyroOffsetZ());
//  
//  Serial.println();
}

void joystick() {
//  Serial.print("X Pin = ");
//  Serial.println(analogRead(X_pin));
//  Serial.print("Y Pin = ");
//  Serial.println(analogRead(Y_pin));
 if ( analogRead(X_pin) >= 0 && analogRead(X_pin) <= 100 ) {
     control_information = 'd';    
 }
 else if ( analogRead(X_pin) <= 1100 && analogRead(X_pin) >= 900 ) {
  control_information = 'a';    
 }
 else if ( analogRead(Y_pin) <= 1100 && analogRead(Y_pin) >= 900 ) {
    control_information = 'w';  
 }
 else if ( analogRead(Y_pin) >= 0 && analogRead(Y_pin) <= 100 ) {
    control_information = 's';
 }
 delay(75);
}

void gyro(int xAxis, int yAxis) {
  // No change
  if (xAxis == 0 && yAxis == 0) {
  }
  // Change xAxis
  else if (abs(xAxis) > abs(yAxis)) {
    if (xAxis < -100) {
      control_information = 'a';
    }
    else if (xAxis > 100) {
      control_information = 'd';
    }
  }
  // Change yAxis
  else {
    if (yAxis > 100) {
      control_information = 'w';
    }
    else if (yAxis < -100) {
      control_information = 's';
    }
  }
  delay (75);
}

void loop(){
 // buzzer will buzz when apple is eaten
 if (Serial.available() > 0) {
  incomingByte = Serial.read();
  if (incomingByte == 'E') {
    tone(buzz, 1000); // Send 1KHz sound signal...
    delay(75);        // ...for 1 sec
    noTone(buzz);     // Stop sound...
  }
 }
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
//  Serial.print(" Xraw = ");
//  Serial.print(rawGyro.XAxis);
//  Serial.print(" Yraw = ");
//  Serial.print(rawGyro.YAxis);
//  Serial.print(" Xnorm = ");
//  Serial.print(normGyro.XAxis);
//  Serial.print(" Ynorm = ");
//  Serial.print(normGyro.YAxis);
  gyro(normGyro.XAxis, normGyro.YAxis);
  joystick();

  Serial.write(control_information);
  Serial.println();
  control_information = ' ';
}
