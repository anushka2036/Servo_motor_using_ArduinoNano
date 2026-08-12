#include <Servo.h>

// Create a servo object
Servo myServo;

// Define the pins
const int joyPin = A0;
const int potPin = A1;
const int servoPin = 3;

// --- Variables for Robust Priority Logic ---
// We use 'float' for more accurate smoothing
float lastSmoothedPotValue = 0; 

// A threshold to detect intentional movement
const int potThreshold = 4;

void setup() {
  myServo.attach(servoPin);
  
  // Take an initial reading to set the starting position
  lastSmoothedPotValue = analogRead(potPin);
  
  Serial.begin(9600);
}

void loop() {
  // 1. Read the raw potentiometer value
  int rawPotValue = analogRead(potPin);
  
  // 2. Apply a smoothing filter to stabilize the reading
  float currentSmoothedPotValue = (0.9 * lastSmoothedPotValue) + (0.1 * rawPotValue);

  // 3. Check if the SMOOTHED value has changed significantly
  if (abs(currentSmoothedPotValue - lastSmoothedPotValue) > potThreshold) {
    // --- POTENTIOMETER HAS PRIORITY ---
    int servoAngle = map(currentSmoothedPotValue, 0, 1023, 0, 180);
    myServo.write(servoAngle);
    
    Serial.print("Control: Potentiometer -- Angle: ");
    Serial.println(servoAngle);

  } else {
    // --- JOYSTICK HAS CONTROL ---
    int joyValue = analogRead(joyPin);
    int servoAngle = map(joyValue, 0, 1023, 0, 180);
    myServo.write(servoAngle);
    
    Serial.print("Control: Joystick -- Angle: ");
    Serial.println(servoAngle);
  }

  // 4. Update the last known value for the next loop
  lastSmoothedPotValue = currentSmoothedPotValue;
  
  delay(15);
}