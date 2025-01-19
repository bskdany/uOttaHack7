#define NUM_PINS 10
#define NUM_SENSOR_PINS 8
#define NUM_MOVEMENT_PINS 2

const int LIGHT_SENSOR_PINS[NUM_SENSOR_PINS] = { 2, 3, 12, 5, 6, 7, 8, 9 };
const int MOVEMENT_PINS[NUM_MOVEMENT_PINS] = { 10, 11 };

void setup() {
  for (int i = 0; i < NUM_SENSOR_PINS; i++) {
    pinMode(LIGHT_SENSOR_PINS[i], OUTPUT);
  }

  for (int i = 0; i < NUM_MOVEMENT_PINS; i++) {
    pinMode(MOVEMENT_PINS[i], INPUT);
  }

  Serial.begin(9600);
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
      Serial.print("FRONT: ");
      Serial.println(shiftedFront);
    } else if (i == 1) {
      digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
      splitIntegerToBinary(shiftedRight, split, sizeof(split)/sizeof(split[0]));
      Serial.print("RIGHT: ");
      Serial.println(shiftedRight);
    } else if (i == 2) {
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
      splitIntegerToBinary(shiftedBehind, split, sizeof(split)/sizeof(split[0]));
      Serial.print("BEHIND: ");
      Serial.println(shiftedBehind);
    } else if (i == 3) {
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
      splitIntegerToBinary(shiftedLeft, split, sizeof(split)/sizeof(split[0]));
      Serial.print("LEFT: ");
      Serial.println(left);
      Serial.println(shiftedLeft);
    }

    // Print the binary representation
    Serial.print("Binary Representation: ");
    for (int j = sizeof(split)/sizeof(split[0]) -1; j >=0 ; j--) {
        Serial.print(split[j]);
    }
    Serial.println();

    // Update light sensor pins based on split array
    for (int j =2; j < NUM_SENSOR_PINS; j++) {
      if(split[j-2] == HIGH){
        digitalWrite(LIGHT_SENSOR_PINS[j], HIGH);
      } else{
        digitalWrite(LIGHT_SENSOR_PINS[j], LOW);
      }
    }
    
    delay(1000); // Delay between iterations
   }

   // Check movement pins and print their status
   if (digitalRead(MOVEMENT_PINS[0]) == HIGH) {
     Serial.println("LEFT");
   } else {
     Serial.println(digitalRead(MOVEMENT_PINS[0]));
   }
   if (digitalRead(MOVEMENT_PINS[1]) == HIGH) {
     Serial.println("RIGHT");
   }
}
