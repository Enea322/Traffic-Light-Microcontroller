int red_led = 2;
int yellow_led = 3;
int green_led = 4;
int button = 5;
int pedestrian_red_led = 6;
int pedestrian_green_led = 7;

int signal_traffic = 0;  
int signal_pedestrian = 1;  

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

  Serial.begin(9600); 
}

void loop() {
  if (digitalRead(button) == LOW) {
    pedestrianRequest = true;
  }

  switch (currentState) {
    case TRAFFIC_GREEN:
      setTrafficLight(green_led);
      setPedestrianLight(pedestrian_red_led);
      digitalWrite(signal_traffic, HIGH);      // Signal green light
      digitalWrite(signal_pedestrian, LOW);   // Pedestrian light is red
      timer++;

      if (timer >= 7) { // Green for 7 seconds
        currentState = TRAFFIC_YELLOW;
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW:
      setTrafficLight(yellow_led);
      setPedestrianLight(pedestrian_red_led);
      digitalWrite(signal_traffic, LOW); 
      digitalWrite(signal_pedestrian, LOW);
      timer++;

      if (timer >= 2) { // Yellow for 3 seconds
        currentState = TRAFFIC_RED;
        timer = 0;
      }
      break;

    case TRAFFIC_RED:
      setTrafficLight(red_led);
      setPedestrianLight(pedestrian_red_led);
      digitalWrite(signal_traffic, LOW);   
      digitalWrite(signal_pedestrian, LOW);
      timer++;

      if (timer >= 7) { // Red for 7 seconds
        if (pedestrianRequest) {
          currentState = PEDESTRIAN_GREEN;
        } else {
          currentState = TRAFFIC_YELLOW_AFTER_RED;
        }
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW_AFTER_RED:
      setTrafficLight(yellow_led);
      setPedestrianLight(pedestrian_red_led);
      digitalWrite(signal_traffic, LOW);  
      digitalWrite(signal_pedestrian, LOW);
      timer++;

      if (timer >= 3) { // Yellow for 3 seconds after red
        currentState = TRAFFIC_GREEN;
        timer = 0;
      }
      break;

    case PEDESTRIAN_GREEN:
      setTrafficLight(red_led);
      setPedestrianLight(pedestrian_green_led);
      digitalWrite(signal_traffic, LOW);    
      digitalWrite(signal_pedestrian, HIGH); 
      timer++;

      if (timer >= 10) { // Pedestrian green for 10 seconds
        currentState = TRAFFIC_RED;
        pedestrianRequest = false;
        timer = 0;
      }
      break;
  }
  if (currentState == TRAFFIC_GREEN) {
    Serial.println("green");
  } else if (currentState == TRAFFIC_YELLOW || currentState == TRAFFIC_YELLOW_AFTER_RED) {
    Serial.println("yellow");
  } else if (currentState == TRAFFIC_RED) {
    Serial.println("red");
  } else if (currentState == PEDESTRIAN_GREEN) {
    Serial.println("pedestrian");
  }

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
