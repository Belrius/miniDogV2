#ifndef XRROBOTLEG_H
#define XRROBOTLEG_H

#include "XRComponent.h"
#include "XRCompliantActuator.h"

class XRRobotLeg : public XRComponent
{

   public:

   XRRobotLeg(XRCompliantActuator* hipAct, float hipOffset,
              XRCompliantActuator* legAct, float thighLength,
              XRCompliantActuator* kneeAct, float shinLength):XRComponent(), hip(*hipAct), hipOffset(hipOffset), leg(*legAct),thighLength(thighLength), knee(*kneeAct), shinLength(shinLength)
   {
   }

   XRCompliantActuator& hip;
   float hipOffset;
   
   XRCompliantActuator& leg;
   float thighLength;
   
   XRCompliantActuator& knee;
   float shinLength;
   
   void setup()
   {
      hip.setup();
      leg.setup();
      knee.setup();
   }

   void loop()
   {
      hip.loop();
      leg.loop();
      knee.loop();
   }

   void SetMode(XRActuator::ActuatorMode mode)
   {
      hip.SetMode(mode);
      leg.SetMode(mode);
      knee.SetMode(mode);
   }

   void SetCompliance(float compliance)
   {
      hip.SetCompliance(compliance);
      leg.SetCompliance(compliance);
      knee.SetCompliance(compliance);
   }
  
};



#endif
