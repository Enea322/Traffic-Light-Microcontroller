int red_led = 2;
int yellow_led = 3;
int green_led = 4;

String masterSignal = ""; // Stores the received signal

void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  if (Serial.available() > 0) {
    masterSignal = Serial.readStringUntil('\n'); 
    masterSignal.trim(); // Remove any extra whitespace
  }

  if (masterSignal == "green") {
    setTrafficLight(red_led);
    delay(50); 
  } else if (masterSignal == "yellow") {
    setTrafficLight(yellow_led);
  } else if (masterSignal == "red") {
    delay(100); 
    setTrafficLight(green_led);
  } else if (masterSignal == "pedestrian") {
    setTrafficLight(green_led);
  }
  
  // Accelerate the green-to-yellow transition
  if (masterSignal == "yellow" && digitalRead(green_led) == HIGH) {
    delay(100); 
  }

  delay(1000); 

}
  
void setTrafficLight(int light) {
  digitalWrite(red_led, light == red_led ? HIGH : LOW);
  digitalWrite(yellow_led, light == yellow_led ? HIGH : LOW);
  digitalWrite(green_led, light == green_led ? HIGH : LOW);
}
