#ifndef XRCOMPLIANT_ACTUATOR_H
#define XRCOMPLIANT_ACTUATOR_H

#include "XRActuator.h"

class XRCompliantActuator : public XRActuator
{
   // value from 0 to 1 for compliance
   float _compliance;
   
   public:

   XRCompliantActuator(float minPosition, float maxPosition, float maxSpeedPerSecond) 
                      : XRActuator(minPosition, maxPosition, maxSpeedPerSecond)
   {
    
   }

   void setup()
   {
    
   }

   void loop()
   {
    
   }

   void Calibrate()
   {
      // override with calibration routine
   }

};









#endif
