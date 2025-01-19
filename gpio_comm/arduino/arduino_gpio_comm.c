#define NUM_PINS 10
const int INPUT_PINS[NUM_PINS] = {2, 3, 4, 5, 6};
const int OUTPUT_PINS[NUM_PINS] = {7, 8, 9, 10, 11};

void setup() {
  for(int i = 0; i < NUM_PINS; i++){
    pinMode(INPUT_PINS[i], INPUT);
    pinMode(OUTPUT_PINS[i], OUTPUT);
  }
  Serial.begin(9600);
}

int decode_number() {
  int number = 0;
  for(int i=0; i<NUM_PINS; i++){
    number |= digitalRead(INPUT_PINS[i]) << i;
  }
  return number
}

int encode_number(number){
  for(int i=0; i<NUM_PINS; i++){
    digitalWrite(OUTPUT_PINS[i], (number >> i) & 1);
  }
}

void loop() {
  int test = 15;
  encode_number(test);
  delay(1000);

  int test_recieved = decode_number();
  if(test_recieved > 0){
    Serial.print("Sent: ");
    Serial.print(test);
    Serial.print(", recieved: ");
    Serial.print(test_recieved);
    Serial.print(encode_number(0));
  }
  delay(1000);
}
