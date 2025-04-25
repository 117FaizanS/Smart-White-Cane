// Define constants for ultrasonic sensor, buzzer, and switch pins
const int trigPin = 8;
const int echoPin = 9;
const int buzzer = 10;
const int switchPin = 2;

// Variables to store ultrasonic sensor measurements and control buzzer
response
long duration;
float distanceCm;
unsigned long previousMillis = 0;
int responseInterval = 1000; // Default response interval for medium distance

// Setup function to run once when the Arduino starts
void setup() {
  // Set pin modes for ultrasonic sensor, buzzer, and switch
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP); // Use internal pull-up resistor for the switch
  Serial.begin(9600); // Initialize serial communication for debugging
}

// Loop function
void loop() {
  // Check if the switch is pressed (LOW state)
  if (digitalRead(switchPin) == LOW) {
    // Get distance from the ultrasonic sensor
    duration = getUltrasonicDistance();
    distanceCm = duration * 0.034 / 2; // Calculate distance in centimeters
    
    // Print distance to the serial monitor for debugging
    Serial.print("Distance: ");
    Serial.println(distanceCm);
    
    // Determine response interval based on distance
    if (distanceCm <= 10) { // Close distance
      responseInterval = 333;
    } else if (distanceCm > 10 && distanceCm <= 20) { // Medium distance
      responseInterval = 1000;
    } else if (distanceCm > 20 && distanceCm <= 30) { // Far distance
      responseInterval = 4000;
    } else {
      responseInterval = 10000; // No response if out of range
    }
    
    // Check if the specified response interval has passed
    unsigned long currentMillis = millis();
    if (currentMillis- previousMillis >= responseInterval) {
      previousMillis = currentMillis;
      tone(buzzer, 440, 100); // Activate the buzzer with a tone for 100 milliseconds
    }
  } else {
    noTone(buzzer); // Turn off the buzzer if the switch is not pressed
  }
}

// Function to measure distance using the ultrasonic sensor
long getUltrasonicDistance() {
  // Trigger ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the pulse and return it
  return pulseIn(echoPin, HIGH);
}
