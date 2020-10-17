//Variables
int DI_pb = 2;
int DO_led = 3;
int DI_pb_state = 0;

//void setup
void setup() {
  pinMode(DI_pb, INPUT);
  pinMode(DO_led, OUTPUT);
  Serial.begin(9600);
}


//void loop
void loop() {
  DI_pb_state = digitalRead(DI_pb);
  if(DI_pb_state == HIGH){
    digitalWrite(DO_led, HIGH);
    delay(1000);
    digitalWrite(DO_led, LOW);
    delay(1000);  
  }
  else {
    digitalWrite(DO_led, LOW);
  }
  Serial.print(DI_pb);
  Serial.print(DO_led);
  Serial.print(DI_pb_state);
  Serial.print('\n');  
}
