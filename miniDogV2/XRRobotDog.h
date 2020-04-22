#ifndef XRROBOTDOG_H
#define XRROBOTDOG_H

#include "XRComponent.h"
#include "XRRobotLeg.h"

class XRRobotDog : public XRComponent
{

   public:

   XRRobotDog(XRRobotLeg* frontLeft, 
              XRRobotLeg* frontRight, 
              XRRobotLeg* rearLeft, 
              XRRobotLeg* rearRight,
              float bodyWidth,   // half the distance from the middle of the body to the hip pivot  
              float bodyLength  // distance from centre of body to shoulder pivot
   ) 
             : XRComponent(), leg_fl(*frontLeft), leg_fr(*frontRight), leg_rl(*rearLeft), leg_rr(*rearRight), bodyWidth(bodyWidth), bodyLength(bodyLength)
   {
    
   }
   

      XRRobotLeg& leg_fl;
      XRRobotLeg& leg_fr;
      XRRobotLeg& leg_rl;
      XRRobotLeg& leg_rr;
      float bodyWidth;   // half the distance from the middle of the body to the hip pivot  
      float bodyLength;  // distance from centre of body to shoulder pivot


   
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


   void SetMode(XRActuator::ActuatorMode mode)
   {
      leg_fl.SetMode(mode);
      leg_fr.SetMode(mode);
      leg_rl.SetMode(mode);
      leg_rr.SetMode(mode);
   }

   void SetCompliance(float compliance)
   {
      leg_fl.SetCompliance(compliance);
      leg_fr.SetCompliance(compliance);
      leg_rl.SetCompliance(compliance);
      leg_rr.SetCompliance(compliance);
   }


  
};









#endif
