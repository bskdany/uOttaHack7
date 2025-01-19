#define NUM_PINS 10
#define NUM_SENSOR_PINS 8
#define NUM_MOVEMENT_PINS 2
const int LIGHT_SENSOR_PINS[NUM_SENSOR_PINS] = {2, 3, 12, 5, 6, 7, 8, 9};
const int MOVEMENT_PINS[NUM_MOVEMENT_PINS] = {10, 11};

void setup() {
  for(int i = 0; i < NUM_SENSOR_PINS; i++){
    pinMode(LIGHT_SENSOR_PINS[i], OUTPUT);
  }

  for(int i = 0; i < NUM_MOVEMENT_PINS; i++){
    pinMode(MOVEMENT_PINS[i], INPUT);
  }

  Serial.begin(9600);
}

int decode_number() {
  int number = 0;
  for(int i=0; i<NUM_PINS; i++){
    number |= digitalRead(LIGHT_SENSOR_PINS[i]) << i;
  }
  return number;
}

int encode_number(unsigned int number){
  for(int i=0; i<NUM_PINS; i++){
    digitalWrite(MOVEMENT_PINS[i], (number >> i) & 1);
  }
}

void loop() {
  for(int i = 0; i < 4; i++){
    if(i == 0){
      digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
      digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
    }
    else if(i == 1){
      digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
    }
    else if(i == 2){
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
    }
    else if(i == 3){
      digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
      digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
    }

    for(int j = 2; j < NUM_SENSOR_PINS; j++){
      digitalWrite(LIGHT_SENSOR_PINS[j], HIGH);
    }
    delay(1000);

  }
  // delay(1000);
  // for(int i = 0; i < 4; i++){
  //     if(i == 0){
  //       digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
  //       digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
  //     }
  //     else if(i == 1){
  //       digitalWrite(LIGHT_SENSOR_PINS[0], LOW);
  //       digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
  //     }
  //     else if(i == 2){
  //       digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
  //       digitalWrite(LIGHT_SENSOR_PINS[1], LOW);
  //     }
  //     else if(i == 3){
  //       digitalWrite(LIGHT_SENSOR_PINS[0], HIGH);
  //       digitalWrite(LIGHT_SENSOR_PINS[1], HIGH);
  //     }

  //     for(int j = 2; j < NUM_SENSOR_PINS; j++){
  //       digitalWrite(LIGHT_SENSOR_PINS[j], LOW);
  //     }

  //   }
 

  delay(1000);


  // for(int i=0; i<256; i++){
  //   encode_number(i);
  //   delay(100);
  //   int test_recieved = decode_number();
  //   Serial.print("Sent: ");
  //   Serial.print(i);
  //   Serial.print(", recieved: ");
  //   Serial.print(test_recieved);
  //   delay(1000);
  // }
  // delay(1000);
  // Serial.println(decode_number());
  if(digitalRead(MOVEMENT_PINS[0])==HIGH){
    Serial.println("LEFT");
  }
  else{
    Serial.println(digitalRead(MOVEMENT_PINS[0]));
  }
  if(digitalRead(MOVEMENT_PINS[1])==HIGH){
    Serial.println("RIGHT");
  }
}
