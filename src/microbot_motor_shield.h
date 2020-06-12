/*####################################################################
 FILE: microbot_motor_shield.h
 VERSION: 1.0
 PURPOSE: Dual DC Motor Shield V2 library for Arduino

 HISTORY:
 Mirko Prosseda - Original version (10/06/2020)
#######################################################################*/


#ifndef MICROBOT_MOTOR_SHIELD_H
#define MICROBOT_MOTOR_SHIELD_H

#include <Arduino.h>

#define In1_1 3
#define In1_2 5
#define In2_1 6
#define In2_2 9
#define SenA A0
#define SenB A1

#define TCN75Addr B1001000 // temperature sensor address
#define configReg 0x01     // Configuration Register
#define tempReg 0x00       // Temperature Register


class microbotMotorShield {
   public:
      // PUBLIC METHODS
      void begin();                                          // initialize the Motor Shield hardware
      void setMotor(uint8_t ch, uint8_t dir, uint8_t speed); // set speed percentage for a specific motor channel
      float getCurrent(uint8_t ch);                          // read current absorption on a specific channel
      float getTemperature();                                // read board temperature
};

#endif
