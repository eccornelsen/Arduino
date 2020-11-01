//libraries
#include <Servo.h>

//object instantiation
Servo motor_1;

//constants
const unsigned int DO_3 = 3; //SERVO MTR w/ PWM 

//variables
int motor_angle = 0;
int scan_time = 15;
int delay_time = 15000;

//void setup
void setup() {
  //IO mapping
  motor_1.attach(DO_3);

  //Enabling Serial port
  Serial.begin(9600);

  //Move axis to specific positions, both limits 0, 180 and mid 90
  motor_1.write(0);
  Serial.println("MOVE TO POS_0");              
  delay(delay_time);           
  
  motor_1.write(90);
  Serial.println("MOVE TO POS_90");              
  delay(delay_time);   
  
  motor_1.write(180);
  Serial.println("MOVE TO POS_180");              
  delay(delay_time);   

}

//void loop
void loop() {
  Serial.println("FROM 0 to 180");  
  for (motor_angle = 0; motor_angle <= 180; motor_angle ++) { 
    motor_1.write(motor_angle);
    Serial.println(motor_angle);           
    delay(scan_time);                       
  }
  delay(delay_time);

  Serial.println("FROM 180 to 0"); 
  for (motor_angle = 180; motor_angle >= 0; motor_angle --) { 
    motor_1.write(motor_angle); 
    Serial.println(motor_angle);                
    delay(scan_time);                       
  }
  delay(delay_time);
}
