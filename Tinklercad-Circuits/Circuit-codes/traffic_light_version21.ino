// C++ code
int red_led = 0;
int yellow_led = 1;
int green_led = 2;
int button = 3;
int pedestrian_red_led = 4;
int pedestrian_green_led = 5;

enum State { 
  TRAFFIC_GREEN, 
  TRAFFIC_YELLOW, 
  TRAFFIC_RED, 
  TRAFFIC_YELLOW_AFTER_RED, 
  PEDESTRIAN_GREEN 
};

State currentState = TRAFFIC_GREEN;

bool pedestrianRequest = false;
int timer = 0;

void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(pedestrian_red_led, OUTPUT);
  pinMode(pedestrian_green_led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(button) == LOW) {
    pedestrianRequest = true;
  }

  switch (currentState) {
    case TRAFFIC_GREEN:
      setTrafficLight(green_led);
      setPedestrianLight(pedestrian_red_led);
      timer++;

      if (timer >= 7) { // Green for 7 seconds
        currentState = TRAFFIC_YELLOW;
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW:
      setTrafficLight(yellow_led);
      setPedestrianLight(pedestrian_red_led);
      timer++;

      if (timer >= 3) { // Yellow for 3 seconds
        currentState = TRAFFIC_RED; // Switch to red
        timer = 0;
      }
      break;

    case TRAFFIC_RED:
      setTrafficLight(red_led);
      setPedestrianLight(pedestrian_red_led);
      timer++;

      if (timer >= 5) { // Red for 5 seconds
        if (pedestrianRequest) {
          currentState = PEDESTRIAN_GREEN; // If there's a request, go to pedestrian green
        } else {
          currentState = TRAFFIC_YELLOW_AFTER_RED; // Otherwise, switch to yellow after red
        }
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW_AFTER_RED:
      setTrafficLight(yellow_led);
      setPedestrianLight(pedestrian_red_led);
      timer++;

      if (timer >= 3) { // Yellow for 3 seconds after red
        currentState = TRAFFIC_GREEN; // Switch back to green
        timer = 0;
      }
      break;

    case PEDESTRIAN_GREEN:
      setTrafficLight(red_led);
      setPedestrianLight(pedestrian_green_led);
      timer++;

      if (timer >= 10) { // Pedestrian green for 10 seconds
        currentState = TRAFFIC_RED; // Return to red for cars
        pedestrianRequest = false; 
        timer = 0;
      }
      break;
  }

  // Delay for 1 second to simulate timer
  delay(1000); 
}

void setTrafficLight(int light) {
  digitalWrite(red_led, light == red_led ? HIGH : LOW);
  digitalWrite(yellow_led, light == yellow_led ? HIGH : LOW);
  digitalWrite(green_led, light == green_led ? HIGH : LOW);
}

void setPedestrianLight(int light) {
  digitalWrite(pedestrian_red_led, light == pedestrian_red_led ? HIGH : LOW);
  digitalWrite(pedestrian_green_led, light == pedestrian_green_led ? HIGH : LOW);
}
