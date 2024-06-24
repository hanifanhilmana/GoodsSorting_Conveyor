#include <Servo.h>

const byte triggerPin1 = 8;
const byte echoPin1 = 9;
const byte triggerPin2 = 12;
const byte echoPin2 = 11;
const byte servoPin = 10;
const byte redLedPin = 7;
const byte yellowLedPin = 6;
const byte greenLedPin = 5;
const byte blueLedPin = 4;
const byte motor = 3;

const float distance = 25.0;
Servo servo;

void setup() {
  Serial.begin(9600);

  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  servo.attach(servoPin);
  pinMode(motor, OUTPUT);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  float distance1 = measureRange(triggerPin1, echoPin1);
  float distance2 = measureRange(triggerPin2, echoPin2);

  float gap = distance1 + distance2;
  float width = distance - gap;
  
  int category = determineCategory(width);
  
  Serial.print("category: ");
  Serial.println(category);
  Serial.print("distance from sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("distance from sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print("gap (distance 1 + distance 2): ");
  Serial.print(gap);
  Serial.println(" cm");
  Serial.print("width object: ");
  Serial.print(width);
  Serial.println(" cm");
  
  performAction(category);

  delay(5000);
}

float measureRange(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float range = (duration * 0.0343) / 2;
  return range;
}

int determineCategory(float width_) {
  if (width_ > 0.0 && width_ <= 5.0) {
    return 1; // small
  } else if (width_ > 5.0 && width_ <= 10.0) {
    return 2; // medium
  } else if (width_ > 10.0 && width_ <= 15.0) {
    return 3; // large
  } else {
    return 4; // another
  }
}

void performAction(int category) {
  switch (category) {
    case 1: // small
      digitalWrite(motor, LOW);
      
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, LOW);

      servo.write(45);
      break;
    case 2:// medium
      digitalWrite(motor, LOW);
    
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(blueLedPin, LOW);
      
      servo.write(90);
      break;
    case 3:// large
      digitalWrite(motor, LOW);
      
      digitalWrite(redLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, HIGH);
      
      servo.write(135);
      break;
    case 4: // another
      digitalWrite(motor, HIGH);
    
      digitalWrite(redLedPin, HIGH);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
      
      servo.write(90);
      break;
  }
}