// #include <Servo.h>
// #include <AccelStepper.h>

// Servo s1, s2, s3, s4, s5, s6;

// // Stepper motor pins
// #define STEP_PIN 3
// #define DIR_PIN 2
// #define EN_PIN 4

// AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// void setup() {

//   // Stepper setup
//   pinMode(EN_PIN, OUTPUT);
//   digitalWrite(EN_PIN, HIGH); // disable stepper

//   stepper.setMaxSpeed(1000);

//   // Attach servos
//   s1.attach(5);   // ELBOW
//   s2.attach(6);   // GRIPPER
//   s3.attach(7);   // WRIST
//   s4.attach(8);   // BASE_1
//   s5.attach(9);   // BASE_2
//   s6.attach(10);  // SHOULDER

//   // Initial position
//   s1.write(0);
//   s2.write(0);
//   s3.write(0);
//   s4.write(0);
//   s5.write(0);
//   s6.write(0);

//   delay(2000);
// }

// void loop() {

//   // =========================
//   // SMALL TEST MOVEMENTS
//   // =========================

//   // ELBOW
//   s1.write(20);
//   delay(800);
//   s1.write(0);
//   delay(800);

//   // GRIPPER
//   s2.write(20);
//   delay(800);
//   s2.write(0);
//   delay(800);

//   // WRIST
//   s3.write(20);
//   delay(800);
//   s3.write(0);
//   delay(800);

//   // BASE_1
//   s4.write(20);
//   delay(800);
//   s4.write(0);
//   delay(800);

//   // BASE_2
//   s5.write(20);
//   delay(800);
//   s5.write(0);
//   delay(800);

//   // SHOULDER
//   s6.write(20);
//   delay(800);
//   s6.write(0);
//   delay(800);

//   // Pause before repeating
//   delay(2000);
// }

#include <Servo.h>
#include <AccelStepper.h>

Servo s1, s2, s3, s4, s5, s6;

// Stepper motor pins
#define STEP_PIN 3
#define DIR_PIN 2
#define EN_PIN 4

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {

  // Stepper setup
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);   // Disable stepper

  stepper.setMaxSpeed(1000);

  // Attach servos
  s1.attach(5);   // ELBOW
  s2.attach(6);   // wrist
  s3.attach(7);   // gripper
  s4.attach(8);   // BASE_1
  s5.attach(9);   // BASE_2
  s6.attach(10);  // SHOULDER

  // Initialize all servos to 0°
  s1.write(0);
  s2.write(0);
  s3.write(0);
  s4.write(0);
  s5.write(0);
  s6.write(0);

  delay(2000);    // Give the servos time to move to 0°
}

void loop() {

}