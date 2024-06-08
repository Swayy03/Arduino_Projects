//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;
int firstStep = 1000;
int secondStep = 200;
int thirdStep = 270;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
	// Rotate CW slowly at 5 RPM
	myStepper.setSpeed(18);
	myStepper.step(firstStep);
	delay(1000);
	
	// Rotate CCW quickly at 10 RPM
	myStepper.setSpeed(18);
	myStepper.step(-secondStep);
	delay(1000);

  myStepper.setSpeed(18);
	myStepper.step(thirdStep);
	delay(1000);

  myStepper.setSpeed(18);
	myStepper.step(-stepsPerRevolution);
	delay(1000);
}