
const int SW_pin = 7; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output joystick
const int Y_pin = 1; // analog pin connected to Y output joystick


int buzz = 2; // buzzer pin
int incomingByte = 0; //incoming Byte infoamtion
char control_information;// information sent to python code snake game


int X_axis[2];
int Y_axis[2];

const int ideal_center = 511;

int compX;
int compY;

void setup() {
  Serial.begin(9600); 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz, LOW);
}

void center(){
  X_axis[1] = analogRead(X_pin); 
  Y_axis[1] = analogRead(Y_pin); 
  X_axis[0] = X_axis[1]; 
  Y_axis[0] = Y_axis[1];
  if(X_axis[0] == analogRead(X_pin) && Y_axis[0] == analogRead(Y_pin)){

    if(analogRead(X_pin) < ideal_center + 30 && analogRead(X_pin) > ideal_center - 30){
        if(analogRead(Y_pin) < ideal_center + 30 && analogRead(Y_pin) > ideal_center - 30){
          compX = ideal_center - analogRead(X_pin);
          compY = ideal_center - analogRead(Y_pin);
        }
    }
 }
 delay(75); 
}
  
void joystick() {
  
  if(analogRead(X_pin) < (ideal_center - compX) -100 && analogRead(X_pin) >= 0){
    control_information = 'd'; 
  }
   if(analogRead(X_pin) > (ideal_center - compX)+100 && analogRead(X_pin) <= 1023){
    control_information = 'a'; 
  }
   if(analogRead(Y_pin) > (ideal_center - compY)+ 100  && analogRead(Y_pin) <= 1023){
    control_information = 'w'; 
  }
  if(analogRead(Y_pin) < (ideal_center - compY) -100  && analogRead(Y_pin) >= 0){
    control_information = 's'; 
  }
 delay(75);

 //Serial.print("X Pin = ");
 //Serial.println(analogRead(X_pin));
 //Serial.print("Y Pin = ");
 //Serial.println(analogRead(Y_pin));
}


void loop() {
  if (Serial.available() > 0) {
  incomingByte = Serial.read();
  if (incomingByte == 'E') {
    tone(buzz, 1000); // Send 1KHz sound signal...
    delay(75);        // ...for 1 sec
    noTone(buzz);     // Stop sound...
  }
 }
 

   
   
  center();
  joystick();
  Serial.write(control_information);
  Serial.println();
  control_information = ' ';
}
