#ifndef XRACTUATOR_H
#define XRACTUATOR_H

#include "XRComponent.h"

class XRActuator : public XRComponent
{
  // an actuator allows movement through a range of positions
  // be those rotation (eg servo) where the position denotes a minimum or maximum angle
  // or linear (eg linear actuator)where it denotes a minimum or maximum extension
 
   float _minPosition;
   float _maxPosition;
   float _maxSpeedPerSecond;

   // actuator movement parameters
   bool _movingToPosition;
   float _targetPosition;
   unsigned long _timeTargetPositionRequested;
   float _currentPosition;

   // value from 0 to 1 for speed
   float _speed;
 
   public:

   enum ActuatorMode { 
    calibration,
    normal,
    compliant
   };

   protected: 
   ActuatorMode _mode;

   public:

   // set up a constrained actuator
   XRActuator(float minPosition, float maxPosition, float maxSpeedPerSecond)
   {

      _minPosition = minPosition;
      _maxPosition = maxPosition;
      _maxSpeedPerSecond = maxSpeedPerSecond;

      // set speed to slow for safety
      _speed = 0.1;
   }

   // Speed is a value from zero to one
   virtual void SetSpeed(float speed)
   {
      if (speed > 1.0) 
      {
         speed = 1.0;
      }

      if (speed < 0.0)
      {
         speed = 0.0;
      }
      _speed = speed;
   }

   virtual void SetTargetPosition(float position)
   {
      if (position < _minPosition)
      {
        position = _minPosition;
      }

      if (position > _maxPosition)
      {
        position = _maxPosition;
      }
      
      _targetPosition = position;
      _movingToPosition = true;
      _timeTargetPositionRequested = millis();
      
   }

   virtual void SetMode(ActuatorMode mode)
   {
      _mode = mode;
   }

   virtual void Calibrate() = 0;

   float GetSpeed()
   {
      return _speed;
   }

   ActuatorMode GetMode()
   {
      return _mode;
   }
   
 
};









#endif
