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

// Définitions pour le premier shield
#define In1_1_1 3
#define In1_2_1 5
#define In2_1_1 6
#define In2_2_1 9
#define SenA_1 A0
#define SenB_1 A1

// Définitions pour le deuxième shield
#define In1_1_2 4
#define In1_2_2 7
#define In2_1_2 8
#define In2_2_2 12
#define SenA_2 A2
#define SenB_2 A3

class microbotMotorShield {
   public:
      // Constructor pour chaque shield
      microbotMotorShield(uint8_t shieldNum);

      // PUBLIC METHODS
      void begin();                                          // initialize the Motor Shield hardware
      void setMotor(uint8_t ch, uint8_t dir, uint8_t speed); // set speed percentage for a specific motor channel
      float getCurrent(uint8_t ch);                          // read current absorption on a specific channel
      float getTemperature();                                // read board temperature

   private:
      uint8_t _shieldNum;  // Numéro du shield (1 ou 2)
};

#endif

