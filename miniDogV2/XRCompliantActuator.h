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

   virtual void SetCompliance(float compliance)
   {
      if (compliance < 0)
      {
        compliance = 0;
      }

      if (compliance > 1)
      {
        compliance = 1;
      }

      _compliance = compliance;
   }

   float GetCompliance()
   {
      return _compliance;
   }

   void Calibrate()
   {
      // override with calibration routine
   }

};









#endif
