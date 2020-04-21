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

   XRRobotLeg(XRCompliantActuator* hipAct, XRCompliantActuator* legAct, XRCompliantActuator* kneeAct)
   {
    hip = *hipAct;
    leg = *legAct;
    knee = *kneeAct;
   }

   XRCompliantActuator& hip;
   XRCompliantActuator& leg;
   XRCompliantActuator& knee;
   
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
