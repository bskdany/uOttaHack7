// Define the pin for device detection
#define DEVICE_DETECT_PIN 2

void driveLeftWheel(int16_t velocity, int time);
void driveRightWheel(int16_t velocity, int time);
void driveBothWheels(int16_t velocityLeft, int16_t velocityRight, int time);

void setup() {
  // Set up the device detect pin as output
  pinMode(DEVICE_DETECT_PIN, OUTPUT);

  // Initialize Serial1 (or appropriate serial port for your hardware) at 57600 baud
  Serial.begin(57600);

  // Toggle the device detect pin
  digitalWrite(DEVICE_DETECT_PIN, LOW);
  delay(100); // 0.1 second delay
  digitalWrite(DEVICE_DETECT_PIN, HIGH);

  // Wait for 2 seconds
  delay(2000);

  // Perform the toggling 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(DEVICE_DETECT_PIN, LOW);
    delay(100); // 0.1 second delay
    digitalWrite(DEVICE_DETECT_PIN, HIGH);
    delay(100); // 0.1 second delay
  }

  // Reinitialize Serial1 at 19200 baud
  Serial.begin(19200);

  // Send the byte values over serial
  Serial.write(128);
  delay(1000); // 1 second delay
  Serial.write(130);
  delay(200);
  Serial.write(132);
  delay(200);
  // delay(1000);
  Serial.write(133);

}

void loop() {
  // No operation in loop
  driveLeftWheel(200, 1000);
  // delay(1000);

  // Drive right wheel
  driveRightWheel(200, 1000);
  // delay(1000);

  // Drive both wheels
  driveBothWheels(200, 200, 1000);
  // delay(1000);
}


void driveLeftWheel(int16_t velocity, int time) {
  // Drive left wheel by setting the right wheel's velocity to 0
  Serial.write(145); // Drive Direct command opcode
  Serial.write((velocity >> 8) & 0xFF); // High byte for left wheel velocity
  Serial.write(velocity & 0xFF);        // Low byte for left wheel velocity
  Serial.write(0x00);                  // High byte for right wheel velocity (0 mm/s)
  Serial.write(0x00);                  // Low byte for right wheel velocity (0 mm/s)
  delay(time);
}

void driveRightWheel(int16_t velocit, int time) {
  // Drive right wheel by setting the left wheel's velocity to 0
  Serial.write(145); // Drive Direct command opcode
  Serial.write(0x00);                  // High byte for left wheel velocity (0 mm/s)
  Serial.write(0x00);                  // Low byte for left wheel velocity (0 mm/s)
  Serial.write((velocity >> 8) & 0xFF); // High byte for right wheel velocity
  Serial.write(velocity & 0xFF);        // Low byte for right wheel velocity
  delay(time);
}

void driveBothWheels(int16_t velocityLeft, int16_t velocityRight, int time) {
  // Drive both wheels with specified velocities
  Serial.write(145); // Drive Direct command opcode
  Serial.write((velocityLeft >> 8) & 0xFF);  // High byte for left wheel velocity
  Serial.write(velocityLeft & 0xFF);         // Low byte for left wheel velocity
  Serial.write((velocityRight >> 8) & 0xFF); // High byte for right wheel velocity
  Serial.write(velocityRight & 0xFF);        // Low byte for right wheel velocity
  delay(time);
}
