#ifndef XRROBOTLEG_H
#define XRROBOTLEG_H

#include "XRComponent.h"
#include "XRCompliantActuator.h"

class XRRobotLeg : public XRComponent
{

   public:

   XRRobotLeg()
   {
    
   }

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


  
};



#endif
