/*####################################################################
 FILE: microbot_motor_shield.cpp
 VERSION: 1.0
 PURPOSE: Dual DC Motor Shield V2 library for Arduino

 HISTORY:
 Mirko Prosseda - Original version (10/06/2020)
#######################################################################*/


#include "microbot_motor_shield.h"
#include <Wire.h>

microbotMotorShield::microbotMotorShield(uint8_t shieldNum) {
  _shieldNum = shieldNum;
}

void microbotMotorShield::begin() {
  if (_shieldNum == 1) {
    pinMode(In1_1_1, OUTPUT);
    pinMode(In1_2_1, OUTPUT);
    pinMode(In2_1_1, OUTPUT);
    pinMode(In2_2_1, OUTPUT);
  } else if (_shieldNum == 2) {
    pinMode(In1_1_2, OUTPUT);
    pinMode(In1_2_2, OUTPUT);
    pinMode(In2_1_2, OUTPUT);
    pinMode(In2_2_2, OUTPUT);
  }
}

void microbotMotorShield::setMotor(uint8_t ch, uint8_t dir, uint8_t speed) {
  uint8_t In1, In2;

  if (_shieldNum == 1) {
    if (ch == 1) {
      In1 = In1_1_1;
      In2 = In1_2_1;
    } else if (ch == 2) {
      In1 = In2_1_1;
      In2 = In2_2_1;
    }
  } else if (_shieldNum == 2) {
    if (ch == 1) {
      In1 = In1_1_2;
      In2 = In1_2_2;
    } else if (ch == 2) {
      In1 = In2_1_2;
      In2 = In2_2_2;
    }
  }

  if (dir == 1) {
    analogWrite(In1, speed);
    analogWrite(In2, 0);
  } else if (dir == 0) {
    analogWrite(In1, 0);
    analogWrite(In2, speed);
  }
}

float microbotMotorShield::getCurrent(uint8_t ch) {
  if (_shieldNum == 1) {
    if (ch == 1) return analogRead(SenA_1) * (5.0 / 1023.0);
    if (ch == 2) return analogRead(SenB_1) * (5.0 / 1023.0);
  } else if (_shieldNum == 2) {
    if (ch == 1) return analogRead(SenA_2) * (5.0 / 1023.0);
    if (ch == 2) return analogRead(SenB_2) * (5.0 / 1023.0);
  }
  return 0;
}

float microbotMotorShield::getTemperature() {
  // Implémentation de la lecture de la température
  // Note: À implémenter si nécessaire
  return 0.0;
}

// Initialize the Motor Shield hardware
void microbotMotorShield::begin() {
   // set digital pins direction
   pinMode(In2_2, OUTPUT);
   pinMode(In1_1, OUTPUT);
   pinMode(In2_1, OUTPUT);
   pinMode(In1_2, OUTPUT);
   // reset digital pins and disables both channels
   digitalWrite(In1_1, LOW);
   digitalWrite(In1_2, LOW);
   digitalWrite(In2_1, LOW);
   digitalWrite(In2_2, LOW);

   Wire.begin();       // initialize I2C port
   // set temperature reading resolution
   Wire.beginTransmission(TCN75Addr); // address the sensor
   Wire.write(configReg);             // point at Configuration Register
   Wire.write(0x00);                  // set resolution at 0.5�C
   Wire.endTransmission();            // execute command
   // select Temperature Register for next readings
   Wire.beginTransmission(TCN75Addr); // address the sensor
   Wire.write(tempReg);               // point at Temperature Register
   Wire.endTransmission();            // execute command
}


// Set direction and speed for a specific motor channel
void microbotMotorShield::setMotor(uint8_t ch, uint8_t dir, uint8_t speed) {
   if(speed > 100) speed = 100;       // speed parameter must be from 0% to 100%
   if(dir == 0) {                     // dir parameter must be 0 or 1
      switch(ch) {                    // ch parameter must be 1 or 2
         case 1:
            analogWrite(In1_1, (float)speed * 2.55);
            digitalWrite(In1_2, LOW);
            break;
         case 2:
            analogWrite(In2_1, (float)speed * 2.55);
            digitalWrite(In2_2, LOW);
            break;
      }
   }
   else if (dir == 1) {               // dir parameter must be 0 or 1
      switch(ch) {                    // ch parameter must be 1 or 2
         case 1:
            analogWrite(In1_2, (float)speed * 2.55);
            digitalWrite(In1_1, LOW);
            break;
         case 2:
            analogWrite(In2_2, (float)speed * 2.55);
            digitalWrite(In2_1, LOW);
            break;
      }
   }
}


// Read current absorption on a specific channel
float microbotMotorShield::getCurrent(uint8_t ch) {
   // when you read motor current consider that it is powered in pwm mode, so also current readings
   // will be pulsed and you need to filter them via a digital low pass filter.
   if(ch == 1) return (((float)analogRead(SenA) * 0.002034505));      // = (1 / 1024 * 5) / 2.4;
   else if(ch == 2) return (((float)analogRead(SenB) * 0.002034505)); // = (1 / 1024 * 5) / 2.4;
   return -1; // error: ch value must be 1 or 2
}


// Read the board temperature
float microbotMotorShield::getTemperature() {
   signed int tReg;
   float temperature;

   // read data from Temperature Register
   Wire.requestFrom(TCN75Addr, 2);    // request 2 bytes from the sensor
   tReg = Wire.read();                // first byte of the Temperature Register
   tReg = tReg << 8;                  // 8-steps left shift
   tReg |= Wire.read();               // second byte of the Temperature Register
   tReg = tReg >> 4;                  // 4-steps right shift

   // evaluate ambient temperature
   temperature = (float)tReg / 16;    // Temperature Register value is divided by 16
   return temperature;
}
