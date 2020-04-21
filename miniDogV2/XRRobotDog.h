#ifndef XRROBOTDOG_H
#define XRROBOTDOG_H

#include "XRComponent.h"
#include "XRRobotLeg.h"

class XRRobotDog : public XRComponent
{

   public:

   XRRobotDog() : XRComponent()
   {
    
   }

   XRRobotDog(XRRobotLeg& frontLeft, XRRobotLeg& frontRight, XRRobotLeg& rearLeft, XRRobotLeg& rearRight) 
             : XRComponent(), leg_fl(frontLeft), leg_fr(frontRight), leg_rl(rearLeft), leg_rr(rearRight)
   {
    
   }
   

   XRRobotLeg& leg_fl;
   XRRobotLeg& leg_fr;
   XRRobotLeg& leg_rl;
   XRRobotLeg& leg_rr;
   
   void setup()
   {
      leg_fl.setup();
      leg_fr.setup();
      leg_rl.setup();
      leg_rr.setup();
   }

   void loop()
   {
      leg_fl.loop();
      leg_fr.loop();
      leg_rl.loop();
      leg_rr.loop();
   }


  
};









#endif
