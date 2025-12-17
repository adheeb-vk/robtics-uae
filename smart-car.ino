// ===== Pin Definitions =====
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define TRIG_PIN 6
#define ECHO_PIN 7

// ===== Parameters =====
#define OBSTACLE_DISTANCE 20   // cm
#define TURN_DELAY 500         // ms
#define STOP_DELAY 300         // ms

// ===== Setup =====
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopCar();
}

// ===== Main Loop =====
void loop() {
  long distance = getDistance();

  if (distance > 0 && distance <= OBSTACLE_DISTANCE) {
    stopCar();
    delay(STOP_DELAY);

    moveBackward();
    delay(400);

    stopCar();
    delay(200);

    turnRight();     // you can change to turnLeft()
    delay(TURN_DELAY);

    stopCar();
  } else {
    moveForward();
  }
}

// ===== Ultrasonic Function =====
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout ~5m
  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ===== Motor Control =====
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
