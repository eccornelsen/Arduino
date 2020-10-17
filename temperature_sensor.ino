//constants
const int AI_0 = A0; //TMP
const int DI_2 = 2; //PB
const int DO_3 = 3; //LED
const float tmp_ref = 20.0;

//variables
int tmp_value = 0;
int tmp_min = 1023;
int tmp_max = 0;
float tmp_volts = 0.0;
float tmp_deg = 0.0;

//void setup
void setup() {
  //IO mapping
  pinMode(DI_2, INPUT);
  pinMode(DO_3, OUTPUT);
  pinMode(AI_0, INPUT);
  analogReference(INTERNAL);
  //Enabling Serial port
  Serial.begin(9600);  
  
  
  //Calibration
  digitalWrite(DO_3, HIGH);
  while(millis() < 20000){
    tmp_value = analogRead(AI_0);
    if(tmp_value > tmp_max) {
      tmp_max = tmp_value;
    }
    if(tmp_value < tmp_min) {
      tmp_min = tmp_value;
    }
  }
  digitalWrite(DO_3, LOW);
}
//void loop
void loop() {
  tmp_value = analogRead(AI_0);
  tmp_value = map(tmp_value, tmp_min, tmp_max, 0, 255);
  tmp_value = constrain(tmp_value, 0, 255);  
  tmp_volts = (tmp_value/1024.0)*5.0;
  tmp_deg = (tmp_volts - 0.5)*100;

  unsigned int tot;
  tot = 0;
  for (int i = 0; i < 64; i++){
    tot += analogRead(AI_0);
    }
  
  //Serial.print(tmp_value);
  //Serial.print(tmp_volts);
  Serial.print(tmp_deg);
  Serial.print('-');
  Serial.print(tot*0.001632 - 50.0);
  Serial.print('\n');
  
  delay(1000);

}
