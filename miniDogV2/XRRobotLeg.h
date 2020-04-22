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

   // This sets the target position of the foot relative to the base of the leg
   // for setting the overall attitude of the dog, see methods in XRRobotDog
   //
   // This is separated from the entire dog IK because it makes it much easier to create Gaits
   // and it makes the code much more re-usable and breaks it up into simpler parts
   //
   // It also moves all of the responsibility of filtering to the actuator
   // since different actuators may have different requirements for filtering.
   //
   bool SetTargetPosition(float x, float y, float z)
   {
      float hipPosition;
      float legPosition;
      float kneePosition;

      if (!CalculateInverseKinematics(x,y,z,hipPosition, legPosition, kneePosition))
      {
          // This is an invalid position - we cannot move to this position
          return false;
      }

      hip.SetTargetPosition(hipPosition);
      leg.SetTargetPosition(legPosition);
      knee.SetTargetPosition(kneePosition);

      return true;
   }

   bool CalculateInverseKinematics(float x, float y, float z, float& hipPosition, float& legPosition, float& kneePosition)
   {
      // TODO - Calculate joint positions -- return safe values for now

      // set to the mid points
      hipPosition = (hip.GetMinPosition() + hip.GetMaxPosition()) * 0.5;
      legPosition = (leg.GetMinPosition() + leg.GetMaxPosition()) * 0.5;
      kneePosition = (knee.GetMinPosition() + knee.GetMaxPosition()) * 0.5;

      return true;    
   }
  
};



#endif
