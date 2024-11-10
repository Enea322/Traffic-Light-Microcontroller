// C++ code

int button = 7;
int pedestrian_red_led = 5;
int pedestrian_green_led = 6;

void setup() {
  pinMode(pedestrian_red_led, OUTPUT);
  pinMode(pedestrian_green_led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600); // For communication with the traffic light Arduino
}

void loop() {
  if (digitalRead(button) == LOW) {
    delay(50); /
    if (digitalRead(button) == LOW) { 
      Serial.write('P');
    }
  }

  // Default pedestrian light is red
  setPedestrianLight(pedestrian_red_led);

  if (Serial.available() > 0) {
    char response = Serial.read();
    if (response == 'G') {
      setPedestrianLight(pedestrian_green_led);
      delay(10000); // Pedestrian green for 10 seconds
      setPedestrianLight(pedestrian_red_led); 
    }
  }

  delay(100); // Small delay for stability
}

void setPedestrianLight(int light) {
  digitalWrite(pedestrian_red_led, light == pedestrian_red_led ? HIGH : LOW);
  digitalWrite(pedestrian_green_led, light == pedestrian_green_led ? HIGH : LOW);
}