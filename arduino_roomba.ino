#define DEVICE_DETECT_PIN 13 // pin to turn rooomba on
#define NUM_PINS 10
#define NUM_SENSOR_PINS 8
#define NUM_MOVEMENT_PINS 2

const int LIGHT_SENSOR_PINS[NUM_SENSOR_PINS] = { 2, 3, 12, 5, 6, 7, 8, 9 };
const int MOVEMENT_PINS[NUM_MOVEMENT_PINS] = { 10, 11 };

void driveLeftWheel(int16_t velocity);
void driveRightWheel(int16_t velocity);
void driveBothWheels(int16_t velocityLeft, int16_t velocityRight);


void roomba_setup(){
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
  // driveBothWheels(50, 50);
    // delay(200);
    // driveBothWheels(0,0);
  // Serial.write(133);
}


void setup() {
  roomba_setup();


  for (int i = 0; i < NUM_SENSOR_PINS; i++) {
    pinMode(LIGHT_SENSOR_PINS[i], OUTPUT);
  }

  for (int i = 0; i < NUM_MOVEMENT_PINS; i++) {
    pinMode(MOVEMENT_PINS[i], INPUT);
  }

  
  // Serial.begin(9600); I have to disable this beause i'm using the roomba one

}

// void loop() {
  // No operation in loop
  // driveLeftWheel(200, 1000);
  // delay(1000);

  // Drive right wheel
  // driveRightWheel(200, 1000);
  // delay(1000);

  // Drive both wheels
  // driveBothWheels(200, 200, 1000);
  // delay(1000);
// }


void driveLeftWheel(int16_t velocity) {
  // Drive left wheel by setting the right wheel's velocity to 0
  Serial.write(145); // Drive Direct command opcode
  Serial.write((velocity >> 8) & 0xFF); // High byte for left wheel velocity
  Serial.write(velocity & 0xFF);        // Low byte for left wheel velocity
  Serial.write(0x00);                  // High byte for right wheel velocity (0 mm/s)
  Serial.write(0x00);                  // Low byte for right wheel velocity (0 mm/s)
}

void driveRightWheel(int16_t velocity) {
  // Drive right wheel by setting the left wheel's velocity to 0
  Serial.write(145); // Drive Direct command opcode
  Serial.write(0x00);                  // High byte for left wheel velocity (0 mm/s)
  Serial.write(0x00);                  // Low byte for left wheel velocity (0 mm/s)
  Serial.write((velocity >> 8) & 0xFF); // High byte for right wheel velocity
  Serial.write(velocity & 0xFF);        // Low byte for right wheel velocity
}

void driveBothWheels(int16_t velocityLeft, int16_t velocityRight) {
  // Drive both wheels with specified velocities
  Serial.write(145); // Drive Direct command opcode
  Serial.write((velocityLeft >> 8) & 0xFF);  // High byte for left wheel velocity
  Serial.write(velocityLeft & 0xFF);         // Low byte for left wheel velocity
  Serial.write((velocityRight >> 8) & 0xFF); // High byte for right wheel velocity
  Serial.write(velocityRight & 0xFF);        // Low byte for right wheel velocity
}

int decode_number() {
  int number = 0;
  for (int i = 0; i < NUM_PINS; i++) {
    number |= digitalRead(LIGHT_SENSOR_PINS[i]) << i;
  }
  return number;
}

void encode_number(unsigned int number) {
  for (int i = 0; i < NUM_MOVEMENT_PINS; i++) {
    digitalWrite(MOVEMENT_PINS[i], (number >> i) & 1);
  }
}

void intToBinaryArray(int number, byte* binaryArray, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    binaryArray[arraySize - 1 - i] = (number >> i) & 1;
  }
}

void splitIntegerToBinary(int number, int* binaryArray, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    binaryArray[arraySize - 1 - i] = (number >> i) & 1; // Store each bit in the array
  }
}

void loop() {
  // Simulated sensor values
  // int right = 400;
  // int behind = 400;
  // int left = 400;
  // int front = 400;
    int right = analogRead(A3);
  int behind = analogRead(A2);
  int left = analogRead(A1);
  int front = analogRead(A0);


  // Shift values
  int shiftedRight = right >> 3;
  int shiftedBehind = behind >> 3;
  int shiftedLeft = left >> 3;
  int shiftedFront = front >> 3;

  int split[6]; // Array to hold binary representation

   // Loop through directions
   for (int i = 0; i < 4; i++) {
    if (i == 0) {
      digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
      digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
      splitIntegerToBinary(shiftedFront, split, sizeof(split)/sizeof(split[0]));
      // Serial.print("FRONT: ");
      // Serial.println(shiftedFront);
    } else if (i == 1) {
      digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
      splitIntegerToBinary(shiftedRight, split, sizeof(split)/sizeof(split[0]));
      // Serial.print("RIGHT: ");
      // Serial.println(shiftedRight);
    } else if (i == 2) {
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
      splitIntegerToBinary(shiftedBehind, split, sizeof(split)/sizeof(split[0]));
      // Serial.print("BEHIND: ");
      // Serial.println(shiftedBehind);
    } else if (i == 3) {
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
      splitIntegerToBinary(shiftedLeft, split, sizeof(split)/sizeof(split[0]));
      // Serial.print("LEFT: ");
      // Serial.println(left);
      // Serial.println(shiftedLeft);
    }

    // Print the binary representation
    // Serial.print("Binary Representation: ");
    // for (int j = sizeof(split)/sizeof(split[0]) -1; j >=0 ; j--) {
        // Serial.print(split[j]);
    // }
    // Serial.println();

    // Update light sensor pins based on split array
    for (int j =2; j < NUM_SENSOR_PINS; j++) {
      if(split[j-2] == HIGH){
        digitalWrite(LIGHT_SENSOR_PINS[j], HIGH);
      } else{
        digitalWrite(LIGHT_SENSOR_PINS[j], LOW);
      }
    }
    
    delay(100); // Delay between iterations
   }


   int left_wheel = digitalRead(MOVEMENT_PINS[0]);
   int right_wheel = digitalRead(MOVEMENT_PINS[1]);

   if(left_wheel && right_wheel){
    driveBothWheels(50, 50);
    delay(200);
   }
   else if(left_wheel){
    driveRightWheel(0);
    driveLeftWheel(50);
    delay(200);
   }
   else if(right_wheel){
    driveLeftWheel(0);
    driveRightWheel(50);
    delay(200);
   }
   else{
    driveBothWheels(0,0);
   }


  //  // Check movement pins and print their status
  //  if (digitalRead(MOVEMENT_PINS[0]) == HIGH) {

  //    Serial.println("LEFT");
  //  } else {
  //    Serial.println(digitalRead(MOVEMENT_PINS[0]));
  //  }
  //  if (digitalRead(MOVEMENT_PINS[1]) == HIGH) {
  //    Serial.println("RIGHT");
  //  }
}

