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

// -------------------------------------------------
// Smooth Servo Movement Function
// -------------------------------------------------
void smoothMove(Servo &servo, int startAngle, int endAngle, int speedDelay)
{
  if (startAngle < endAngle)
  {
    for (int pos = startAngle; pos <= endAngle; pos++)
    {
      servo.write(pos);
      delay(speedDelay);
    }
  }
  else
  {
    for (int pos = startAngle; pos >= endAngle; pos--)
    {
      servo.write(pos);
      delay(speedDelay);
    }
  }
}

// -------------------------------------------------
// Test One Servo
// -------------------------------------------------
void testServo(Servo &servo, const char *name)
{
  Serial.print("Testing ");
  Serial.println(name);

  // Move from 0° to 90°
  smoothMove(servo, 0, 90, 20);
  delay(1000);

  // Move back from 90° to 0°
  smoothMove(servo, 90, 0, 20);
  delay(1000);
}

// -------------------------------------------------
// Test Stepper Motor
// -------------------------------------------------
void testStepper()
{
  Serial.println("Testing Stepper");

  digitalWrite(EN_PIN, LOW); // Enable stepper

  // Move forward
  stepper.moveTo(800);
  while (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }

  delay(1000);

  // Move back
  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }

  delay(1000);

  digitalWrite(EN_PIN, HIGH); // Disable stepper
}

// -------------------------------------------------
// Setup
// -------------------------------------------------
void setup()
{
  Serial.begin(115200);

  // Stepper setup
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH); // Disable stepper initially

  stepper.setMaxSpeed(600);
  stepper.setAcceleration(300);

  // Attach servos
  s1.attach(5);   // ELBOW
  s2.attach(6);   // WRIST
  s3.attach(7);   // GRIPPER
  s4.attach(10);  // BASE_1
  s5.attach(9);   // BASE_2
  s6.attach(8);   // SHOULDER
  
 

  // Initialize all servos to 0°
  s1.write(0);
  s2.write(0);
  s3.write(0);
  s4.write(0);
  s5.write(0);
  s6.write(0);

  delay(3000);
}

// -------------------------------------------------
// Main Loop
// -------------------------------------------------
void loop()
{
  testServo(s1, "ELBOW");
  testServo(s2, "WRIST");
  testServo(s3, "GRIPPER");
  testServo(s6, "SHOULDER");
  testServo(s5, "BASE_2");
  testServo(s4, "BASE_1");

  testStepper();

  delay(3000);
}