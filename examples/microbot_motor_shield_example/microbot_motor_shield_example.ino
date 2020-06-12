/*####################################################################
 FILE: microbot_motor_shield_example.ino
 VERSION: 1.0
 PURPOSE: Dual DC Motor Shield V2 test sketch

 Description:
 * Shield temperature and current absorption are monitored on Serial Monitor
 * Motor speed and direction are controlled by a potentiometer.

 Connections:
 * this sketch needs two potentiometers attached on 3-pin strips labeled
 * "Analog Input"; they are used to change motor speed and direction.
 * Jumpers on SenA and SenB strips must be inserted.

 HISTORY:
 Mirko Prosseda - Original version (10/06/2020)
#######################################################################*/


#include <microbot_motor_shield.h>

microbotMotorShield MotorShield;

   const int analogPin1 = A2;
   const int analogPin2 = A3;

   int analogValue1, analogValue2;
   uint8_t pwmValue1, pwmValue2;

   float temperature;
   float currentA, currentB;


void setup() {
   MotorShield.begin();       // initialize the Motor Shield hardware
   Serial.begin(9600);        // initialize Serial Port
   Serial.println("Dual DC Motor Shield V2 test sketch");
}


void loop() {
   // read both potentiometers values
   analogValue1 = analogRead(analogPin1);
   analogValue2 = analogRead(analogPin2);

   // apply direction and speed adjustment for channel 1
   if(analogValue1 > 512) {
      pwmValue1 = ((float)analogValue1 - 512) * 0.1953; // evaluate new pwm value
      MotorShield.setMotor(1, 1, pwmValue1);
   }
   else {
      pwmValue1 = ((float)511 - analogValue1) * 0.1953; // evaluate new pwm value
      MotorShield.setMotor(1, 0, pwmValue1);
   }

   // apply direction and speed adjustment for channel 2
   if(analogValue2 > 512) {
      pwmValue2 = ((float)analogValue2 - 512) * 0.1953; // evaluate new pwm value
      MotorShield.setMotor(2, 1, pwmValue2);
   }
   else {
      pwmValue2 = ((float)511 - analogValue2) * 0.1953; // evaluate new pwm value
      MotorShield.setMotor(2, 0, pwmValue2);
   }

   // read current and temperature values
   temperature = MotorShield.getTemperature();
   currentA = MotorShield.getCurrent(1);
   currentB = MotorShield.getCurrent(2);
   Serial.println("Current: " + String(currentA) + "(A) / " + String(currentB) + "(B) - Temperature: " + String(temperature));
   delay(100);
}
