//constants
const unsigned int AI_0 = A0; //TMP
const unsigned int DO_3 = 3; //LED
const unsigned int tmp_min = 0;
const unsigned int tmp_max = 1023;

//variables
unsigned int tmp_value = 0;
float tmp_volts = 0.0;
float tmp_deg = 0.0;

//void setup
void setup() {
  //IO mapping
  pinMode(DO_3, OUTPUT);
  pinMode(AI_0, INPUT);
  analogReference(INTERNAL);
  //Enabling Serial port
  Serial.begin(9600);  
  
  //Calibration
  digitalWrite(DO_3, HIGH);
  while(millis() < 5000){
    tmp_value = analogRead(AI_0);
    Serial.println(tmp_value);
    if(tmp_value > tmp_max) {
      tmp_value = tmp_max;
    }
    if(tmp_value < tmp_min) {
      tmp_value = tmp_min;
    }
  }
  digitalWrite(DO_3, LOW);
}
//void loop
void loop() {
  tmp_value = analogRead(AI_0);
  Serial.println(tmp_value);
  //Analog signal Normalization and Scaling
  tmp_value = map(tmp_value, tmp_min, tmp_max, tmp_min, tmp_max);
  tmp_value = constrain(tmp_value, tmp_min, tmp_max);  
  Serial.println(tmp_value);
  tmp_volts = (tmp_value/(float)(tmp_max+1-tmp_min))*1.1;
  Serial.println(tmp_volts);
  tmp_deg = (tmp_volts - 0.5)*100;
  Serial.println(tmp_deg);
  delay(1000);

  unsigned int avg=0;
  for (int i = 0; i < 64; i++){
    avg += analogRead(AI_0);
    }
  Serial.print("Average analog input ");
  Serial.println(avg/64.0);
  delay(500);
}
