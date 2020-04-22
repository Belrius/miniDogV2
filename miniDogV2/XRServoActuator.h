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

   XRServoActuator(int servoOutPin, int servoOffset, int hallEffectInPin, float minPosition, float maxPosition, float maxSpeedPerSecond) 
                  : XRCompliantActuator(minPosition, maxPosition, maxSpeedPerSecond)
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

       // TODO - use the loop to attempt to move the servo to the target position 
       // in small increments rather than just set the servo directly to the target

       // this allows us to also use the speed and compliance settings correctly

       // requires consultation with James as to how this would work best.
   }

   void Calibrate()
   {
      _hallOffset = analogRead(_hallEffectInPin);
   }

   // Set Target positon
   // Ideally this shouldn't change from the base class implementation
   //
   // We should use the loop to manage the update of the actuator's position
   // to allow us to take account of compliance and desired speed. See notes in the loop function
   //
   void SetTargetPosition(float position)
   {
      // call the base class to set the target position
      XRCompliantActuator::SetTargetPosition(position);

      // the requested position may have been out of range
      // and may have been adjusted
      
      // get the actual position that's been set
      float targetPos = GetTargetPosition();
      float minPos = GetMinPosition();
      float maxPos = GetMaxPosition();

      // map the target position to a number of microseconds from 1000-2000 on the servo
      // normally done with a map function but the positions are floats
      int microsecs = (int)  ( (targetPos - minPos) / ( maxPos - minPos) * 1000 ) + 1000;

      _servo.writeMicroseconds(microsecs);
      
   }
  
};









#endif
