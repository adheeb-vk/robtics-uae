// Smart Glasses for the Blind - Easy Version

int trigPin = 9;
int echoPin = 10;
int buzzer = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Send signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);

  // Convert to cm
  int distance = duration * 0.034 / 2;

  Serial.println(distance);

  // If object is closer than 30 cm → beep
  if (distance < 30) {
    digitalWrite(buzzer, HIGH);
    delay(100);              // Beeps
    digitalWrite(buzzer, LOW);
    delay(100);
  } 
  else {
    digitalWrite(buzzer, LOW);  // No beep
  }
}
