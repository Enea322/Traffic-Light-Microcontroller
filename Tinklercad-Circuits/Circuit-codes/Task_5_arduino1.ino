// C++ code
//

int red_led = 2;
int yellow_led = 3;
int green_led = 4;

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
  Serial.begin(9600); //For communication with the pedestrian Arduino
}

void loop() {
  if (Serial.available() > 0) {
    char request = Serial.read();
    if (request == 'P') {
      pedestrianRequest = true;
    }
  }

  switch (currentState) {
    case TRAFFIC_GREEN:
      setTrafficLight(green_led);
      timer++;

      if (timer >= 7) { // Green for 7 seconds
        currentState = TRAFFIC_YELLOW;
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW:
      setTrafficLight(yellow_led);
      timer++;

      if (timer >= 3) { // Yellow for 3 seconds
        currentState = TRAFFIC_RED; 
        timer = 0;
      }
      break;

    case TRAFFIC_RED:
      setTrafficLight(red_led);
      timer++;

      if (timer >= 5) { // Red for 5 seconds
        if (pedestrianRequest) {
          currentState = PEDESTRIAN_GREEN; 
          Serial.write('G'); 
        } else {
          currentState = TRAFFIC_YELLOW_AFTER_RED; 
        }
        timer = 0;
      }
      break;

    case TRAFFIC_YELLOW_AFTER_RED:
      setTrafficLight(yellow_led);
      timer++;

      if (timer >= 3) { // Yellow for 3 seconds after red
        currentState = TRAFFIC_GREEN; 
        timer = 0;
      }
      break;

    case PEDESTRIAN_GREEN:
      setTrafficLight(red_led);
      timer++;

      if (timer >= 10) { // Pedestrian green for 10 seconds
        currentState = TRAFFIC_RED; 
        pedestrianRequest = false;
        timer = 0;
      }
      break;
  }

  delay(1000); 
}

void setTrafficLight(int light) {
  digitalWrite(red_led, light == red_led ? HIGH : LOW);
  digitalWrite(yellow_led, light == yellow_led ? HIGH : LOW);
  digitalWrite(green_led, light == green_led ? HIGH : LOW);
}