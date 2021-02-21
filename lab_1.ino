/*
 * Ryan McCann
 * EECE.4520 Lab 1
 * Last modified on 02/20/21
 * No bugs identified at this point in time
*/

// GLOBAL VARIABLES
int yellow_pin = 3;
int green_pin = 5;
int red_pin = 6;
int button_pin = 10;
int buzzer_pin = 12;
int button_state;

void setup() {
  // Initialize LEDs
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);
  digitalWrite(yellow_pin, LOW);
  // Initialize digital input
  pinMode(button_pin, INPUT_PULLUP);  
  // Initialize buzzer
  pinMode(buzzer_pin, OUTPUT);
  Serial.begin(9600);
}

// Toggle an led given the pin and a duration
void toggle_led(char led_pin, int duration, bool default_state=false) {
  digitalWrite(led_pin, HIGH);
  delay(duration);
  digitalWrite(led_pin, LOW);
  if (default_state) {
    delay(duration);
  }
  else {
    delay(1);
  }
};

// Activates the buzzer for 3 seconds
void toggle_buzz() {
  digitalWrite(buzzer_pin, HIGH);
  delay(3000);
  digitalWrite(buzzer_pin,LOW);
  delay(1);
};

void loop() {
  // Default state, red light flashed until a button is pressed
  while (true) {
    button_state = digitalRead(button_pin);
    if (button_state == LOW) {
      break;
    }
    toggle_led(red_pin, 100, true);
    Serial.println(button_state);
  }
  while (true) {
    // Red light on for 15 seconds
    toggle_led(red_pin, 15000);
    toggle_buzz();
    // Green light on for 15 seconds
    toggle_led(green_pin, 15000);
    toggle_buzz();
    // Yellow light on for 3 seconds
    toggle_led(yellow_pin, 3000);
    toggle_buzz();
  }
}
