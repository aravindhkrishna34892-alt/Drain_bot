#include "arduino_secrets.h"

#define TRIG_PIN 9     // Trigger pin of ultrasonic sensor
#define ECHO_PIN 10    // Echo pin of ultrasonic sensor
#define BUZZER_PIN 8   // Pin connected to the buzzer
#define IN1_PIN 4      // Motor driver IN1
#define IN2_PIN 5      // Motor driver IN2

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the sensor pins as outputs and inputs
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Set motor control pins as outputs
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Initially turn off the motor
  stopMotor();
}

void loop() {
  // Measure the distance using the ultrasonic sensor
  long distance = getDistance();

  // Print the distance in the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If the distance is less than 10 cm, turn on the buzzer and move motor
  if (distance < 10) {
    digitalWrite(BUZZER_PIN, HIGH);  // Turn buzzer ON
    moveMotorForward();  // Move the motor forward
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Turn buzzer OFF
    stopMotor();  // Stop the motor
  }

  // Wait for a while before the next measurement
  delay(500);
}

// Function to get the distance from the ultrasonic sensor
long getDistance() {
  // Send a pulse to the trigger pin to start the measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration on the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters (speed of sound = 343 m/s)
  long distance = (duration / 2) / 29.1;  // Distance in cm
  return distance;
}

// Function to move the motor forward
void moveMotorForward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
}

// Function to stop the motor
void stopMotor() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}