#ifndef XRROBOTLEG_H
#define XRROBOTLEG_H

#include "XRComponent.h"

class XRRobotGait : public XRComponent
{
    // walk test positions
    
    int initStart;
    int state;
    float rate;
    
    int targetLeg1x;
    int targetLeg1z;
    int prevLeg1x;
    int prevLeg1z;
    float currentLeg1x;
    float currentLeg1z;
    float stepDiffLeg1x;
    float stepDiffLeg1z;
    
    int targetLeg2x;
    int targetLeg2z;
    int prevLeg2x;
    int prevLeg2z;
    float currentLeg2x;
    float currentLeg2z;
    float stepDiffLeg2x;
    float stepDiffLeg2z;
    
    int targetLeg3x;
    int targetLeg3z;
    int prevLeg3x;
    int prevLeg3z;
    float currentLeg3x;
    float currentLeg3z;
    float stepDiffLeg3x;
    float stepDiffLeg3z;
    
    int targetLeg4x;
    int targetLeg4z;
    int prevLeg4x;
    int prevLeg4z;
    float currentLeg4x;
    float currentLeg4z;
    float stepDiffLeg4x;
    float stepDiffLeg4z;
    
    int targetLeg1y;
    int prevLeg1y;
    float currentLeg1y;
    float stepDiffLeg1y;
    
    int walkXPos1;
    int walkXPos2;
    int walkXPos3; 
    int walkXPos4; 
    int walkXPos5;
    int walkXPos6; 
    int walkXPos7; 
    int walkXPos8; 
    
    int walkYPos1;
    int walkYPos2;
    int walkYPos3;
    int walkYPos4;
    int walkYPos5;
    int walkYPos6;
    int walkYPos7;
    int walkYPos8;
    
    int walkZPos1;
    int walkZPos2;
    int walkZPos3;
    int walkZPos4;
    int walkZPos5;
    int walkZPos6;
    int walkZPos7;
    int walkZPos8;

   public:
   
   void setup()
   {
    
   }

   void loop()
   {

    
   }


  
}



#endif
