#include <ESP32Servo.h>

const int SERVO_PIN = 15;
Servo myServo;

String inputString = "";
bool inputComplete = false;

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
  Serial.println("Enter angle (0180) to move the servo:");
}

void loop() {
  // Read user input from Serial
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    if (inChar == '\n' || inChar == '\r') {
      inputComplete = true;
    } else {
      inputString += inChar;
    }
  }

  // When a full command is received
  if (inputComplete) {
    int angle = inputString.toInt();  // Convert input to integer
    if (angle >= 0 && angle <= 180) {
      myServo.write(angle);
      Serial.print("Moving servo to ");
      Serial.print(angle);
      Serial.println("°");
    } else {
      Serial.println("Invalid angle. Enter a value between 0 and 180.");
    }

    // Clear input
    inputString = "";
    inputComplete = false;
    delay(500);  // Delay to allow the servo to move
  }
}
