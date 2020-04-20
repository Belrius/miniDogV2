#ifndef XRACTUATOR_H
#define XRACTUATOR_H

#include "XRComponent.h"

class XRActuator : public XRComponent
{
   public:

   enum ActuatorMode { 
    calibration,
    normal,
    compliant
   };

   protected: 
   ActuatorMode _mode;

   public:

   virtual void SetMode(ActuatorMode mode)
   {
      _mode = mode;
   }

   virtual void Calibrate() = 0;

   ActuatorMode GetMode()
   {
      return _mode;
   }
   
 
};









#endif
