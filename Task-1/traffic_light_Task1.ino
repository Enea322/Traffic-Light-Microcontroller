int red_led = 0;       
int yellow_led = 1;    
int green_led = 2;    

void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

void loop() {
  
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  delay(3000);  // Red light stays on for 3 seconds

  
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, HIGH);
  delay(1500);  // Yellow light stays on for 1.5 seconds 

  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, HIGH);
  delay(3000);  // Green light stays on for 3 seconds

  digitalWrite(green_led, LOW);
  digitalWrite(yellow_led, HIGH);
  delay(1500);  // Yellow light stays on for 1.5 seconds

  digitalWrite(yellow_led, LOW);
  digitalWrite(red_led, HIGH);
  delay(3000);  // Red light stays on for 3 seconds

  // Repeat the cycle
}
