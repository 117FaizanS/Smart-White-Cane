const int trigPin = 8;
const int echoPin = 9;
const int buzzer = 10;
const int switchPin = 2;

long duration;
float distanceCm;
unsigned long previousMillis = 0;
int responseInterval = 1000; // Default to medium distance

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    duration = getUltrasonicDistance();
    distanceCm = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.println(distanceCm);

    // Determine response interval based on distance
    if (distanceCm <= 15) { // Close
      responseInterval = 333;
    } else if (distanceCm > 15 && distanceCm <= 25) { // Medium
      responseInterval = 1000;
    } else if (distanceCm > 25 && distanceCm <= 30) { // Far
      responseInterval = 4000;
    } else {
      responseInterval = 10000; // No response if out of range
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= responseInterval) {
      previousMillis = currentMillis;
      tone(buzzer, 440, 100); // Activate the buzzer
    }
  } else {
    noTone(buzzer); // Turn off the buzzer
  }
}

long getUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH);
}
