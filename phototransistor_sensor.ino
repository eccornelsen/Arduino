//constants
const unsigned int AI_0 = A0; //PHT
const unsigned int AO_3 = 3; //LED w/ PWM 
const unsigned int max_dig = 1023; //10bit resolution
const unsigned int max_pwm = 255; //8bit resolution
const String mode = "INTERNAL";

//variables
float dig_value = 0.0;
float photo_volts = 0.0;
float Vref = 0.0;

//void setup
void setup() {
  //IO mapping
  pinMode(AO_3, OUTPUT);
  pinMode(AI_0, INPUT);

  //setting INTERNAL reference voltage
  if(mode == "INTERNAL") {
    analogReference(INTERNAL);
    Vref = 1.1;
    }

  //Enabling Serial port
  Serial.begin(9600);  
  
  //Calibration
  digitalWrite(AO_3, HIGH);
  while(millis() < 5000){
    dig_value = analogRead(AI_0);
    Serial.println(dig_value);
    dig_value = constrain(dig_value, 0, max_dig);
  }
  digitalWrite(AO_3, LOW);
}

//void loop
void loop() {
  //Analog value average read and limiting
  unsigned int avg=0;
  for (int i = 0; i < 64; i++){
    dig_value = analogRead(AI_0);
    dig_value = constrain(dig_value, 0, max_dig);
    avg += dig_value;
    }
  dig_value = avg/64.0;  
  Serial.println(dig_value);
  
  //ADC conversion
  photo_volts = (dig_value/(float)(max_dig+1))*Vref;
  Serial.println(photo_volts);

  //Light with PWM
  analogWrite(AO_3, map((int)dig_value, max_dig, 0, 0, max_pwm));

  delay(1000);
}
