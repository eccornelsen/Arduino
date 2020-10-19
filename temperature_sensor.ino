//constants
const unsigned int AI_0 = A0; //TMP
const unsigned int DO_3 = 3; //LED
const unsigned int max_dig = 1023; //10bit resolution
const String mode = "INTERNAL";

//variables
float dig_value = 0.0;
float temp_volts = 0.0;
float temp_deg = 0.0;
float Vref = 0.0;

//void setup
void setup() {
  //IO mapping
  pinMode(DO_3, OUTPUT);
  pinMode(AI_0, INPUT);

  //setting INTERNAL reference voltage
  if(mode == "INTERNAL") {
    analogReference(INTERNAL);
    Vref = 1.1;
    }

  //Enabling Serial port
  Serial.begin(9600);  
  
  //Calibration
  digitalWrite(DO_3, HIGH);
  while(millis() < 5000){
    dig_value = analogRead(AI_0);
    Serial.println(dig_value);
    dig_value = constrain(dig_value, 0, max_dig);
  }
  digitalWrite(DO_3, LOW);
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
  temp_volts = (dig_value/(float)(max_dig+1))*Vref;
  Serial.println(temp_volts);

  //Temperature calculation
  temp_deg = (temp_volts - 0.5)*100; //750mV @ 25degC 
  Serial.println(temp_deg);
  delay(1000);
}
