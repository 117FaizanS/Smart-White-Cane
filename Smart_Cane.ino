const int trigPin = 8;
const int echoPin = 9;
const int buzzer = 10;

long duration;
float distanceInch;
int timer;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceInch = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distanceInch);

  tone(buzzer, 440, 100);

  timer = distanceInch * 10;
  delay(timer);
}
