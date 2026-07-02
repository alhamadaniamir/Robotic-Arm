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
// Test Individual Servo
// -------------------------------------------------
void testServo(Servo &servo, const char *name)
{
  Serial.print("Testing ");
  Serial.println(name);

  smoothMove(servo, 0, 90, 20);
  delay(1000);

  smoothMove(servo, 90, 0, 20);
  delay(1000);
}

// -------------------------------------------------
// Test BASE_1 and BASE_2 Together
// BASE_1 : 0° -> 90°
// BASE_2 : 90° -> 0°
// -------------------------------------------------
void testBase()
{
  Serial.println("Testing BASE");

  // Forward
  for (int pos = 0; pos <= 90; pos++)
  {
    s4.write(pos);         // BASE_1
    s5.write(90 - pos);    // BASE_2 (opposite direction)
    delay(20);
  }

  delay(1000);

  // Return
  for (int pos = 90; pos >= 0; pos--)
  {
    s4.write(pos);         // BASE_1
    s5.write(90 - pos);    // BASE_2 (opposite direction)
    delay(20);
  }

  delay(1000);
}

// -------------------------------------------------
// Test Stepper
// -------------------------------------------------
void testStepper()
{
  Serial.println("Testing Stepper");

  digitalWrite(EN_PIN, LOW); // Enable driver

  stepper.moveTo(800);

  while (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }

  delay(1000);

  stepper.moveTo(0);

  while (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }

  delay(1000);

  digitalWrite(EN_PIN, HIGH); // Disable driver
}

// -------------------------------------------------
// Setup
// -------------------------------------------------
void setup()
{
  Serial.begin(115200);

  // Stepper setup
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH); // Disabled initially

  stepper.setMaxSpeed(600);
  stepper.setAcceleration(300);

  // Attach servos
  s1.attach(5);    // ELBOW
  s2.attach(6);    // WRIST
  s3.attach(7);    // GRIPPER
  s6.attach(8);    // SHOULDER
  s5.attach(9);    // BASE_2
  s4.attach(10);   // BASE_1

  // Initial positions
  s1.write(0);
  s2.write(0);
  s3.write(0);
  s6.write(0);

  // Base servos start opposite each other
  s4.write(20);     // BASE_1
  s5.write(70);    // BASE_2

  delay(3000);
}

// -------------------------------------------------\
// Main Loop
// -------------------------------------------------
void loop()
{
  testServo(s1, "ELBOW");

  testServo(s2, "WRIST");

  testServo(s3, "GRIPPER");

  testServo(s6, "SHOULDER");

  testBase();

  testStepper();

  delay(3000);
}