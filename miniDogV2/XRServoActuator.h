#ifndef XRSERVO_ACTUATOR_H
#define XRSERVO_ACTUATOR_H

#include <Servo.h>
#include "XRCompliantActuator.h"

class XRServoActuator : public XRCompliantActuator
{
   Servo _servo;
    
   // values to write out to servos
   float _servoPos;    // initial value
   float _servoPosTrack;   // ongoing tracking value
   float _servoPosFiltered;  // filtered values
    
   // *******************************************************************************
   // servo offsets for default position - knees at 45', hips at 0', shoulders at 45'
   // *******************************************************************************
    
   int _servoOffset;      // these are really important to get as accurate as possible
    
    // *******************************************************************************
    
    // hall effect sensors - not used in miniDog V2 but the coe is still included

   int _hallEffectInPin;
    
   float _hall;
    
    // offset values for auto-calibration at startup
   int _hallOffset;
  
   public:

   ServoActuator(int servoOutPin, int servoOffset, int hallEffectInPin)
   {
      _servo.attach(servoOutPin);
      _servoOffset = servoOffset;
      _hallEffectInPin = hallEffectInPin;
   }

   void setup()
   {
      _servo.writeMicroseconds(_servoOffset);
      pinMode(_hallEffectInPin, INPUT);
      _hallOffset = analogRead(_hallEffectInPin);
   }

   void loop()
   {
       _hall = analogRead(_hallEffectInPin) - _hallOffset;
   }

   void Calibrate()
   {
      _hallOffset = analogRead(_hallEffectInPin);
   }
  
};









#endif
