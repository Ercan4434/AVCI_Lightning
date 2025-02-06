const int led1 = 6; 
const int led3 = 8; 
const int led4 = 9; 
const int button = 3; 

unsigned long previousMillis1 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
const long interval1On = 75;
const long interval1Off = 900;
const long interval3Off = 750;
const long delayBetween3and4 = 50;
bool led1State = false;
bool led3State = false;
bool led4State = false;
bool led4DelayActive = false;
bool syncMode = false;

void setup() {
  pinMode(led1, OUTPUT);

  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(button, INPUT_PULLUP);

}

void loop() {
  unsigned long currentMillis = millis();
  
  if (digitalRead(button) == LOW) {
    syncMode = !syncMode;
    
  }

  if ((led1State && currentMillis - previousMillis1 >= interval1On) || (!led1State && currentMillis - previousMillis1 >= interval1Off)) {
    led1State = !led1State;
    digitalWrite(led1, led1State);
    previousMillis1 = currentMillis;
  }

  if ((led3State && currentMillis - previousMillis3 >= interval1On) || (!led3State && currentMillis - previousMillis3 >= interval3Off)) {
    led3State = !led3State;
    digitalWrite(led3, led3State);
    previousMillis3 = currentMillis;
    if (led3State) {
      if (syncMode) {
        digitalWrite(led4, HIGH);
        led4State = true;
        previousMillis4 = currentMillis;
      } else {
        led4DelayActive = true;
        previousMillis4 = currentMillis;
      }
    }
  }

  if (!syncMode && led4DelayActive && currentMillis - previousMillis4 >= delayBetween3and4) {
    led4DelayActive = false;
    led4State = true;
    digitalWrite(led4, HIGH);
    previousMillis4 = currentMillis;
  }

  if (led4State && currentMillis - previousMillis4 >= interval1On) {
    led4State = false;
    digitalWrite(led4, LOW);
    previousMillis4 = currentMillis;
  }
}
