#include "Wire.h"
#include "XRRemoteReceiver.h"
//#include "XRImu.h"
#include "XRRobotDog.h"
#include "XRRobotLeg.h"
#include "XRServoActuator.h"

// robot receiver
XRRemoteReceiver receiver(27,10);

// imu
//XRImu imu();

// define parameters for robot---------------
#define hipOffset 76.5
#define thighLength 125
#define shinLength 125     

#define bodyWidth 126      // half the distance from the middle of the body to the hip pivot  
#define bodyLength 147.5      // distance from centre of body to shoulder pivot

// construct robot

// Front left leg - servo pin, servo offset, hall effect pint, min angle, max angle, speed degrees per second
XRServoActuator frontLeftHip(5,1500,A7,0,180,90);
XRServoActuator frontLeftThigh(5,1500,A7,0,180,90);
XRServoActuator frontLeftKnee(5,1500,A7,0,180,90);

XRRobotLeg frontLeftLeg(&frontLeftHip, hipOffset, &frontLeftThigh, thighLength, &frontLeftKnee, shinLength);

// Front right leg
XRServoActuator frontRightHip(5,1500,A7,0,180,90);
XRServoActuator frontRightThigh(5,1500,A7,0,180,90);
XRServoActuator frontRightKnee(5,1500,A7,0,180,90);

XRRobotLeg frontRightLeg(&frontRightHip, hipOffset, &frontRightThigh, thighLength, &frontRightKnee, shinLength);

// Rear left leg
XRServoActuator rearLeftHip(5,1500,A7,0,180,90);
XRServoActuator rearLeftThigh(5,1500,A7,0,180,90);
XRServoActuator rearLeftKnee(5,1500,A7,0,180,90);

XRRobotLeg rearLeftLeg(&rearLeftHip, hipOffset, &rearLeftThigh, thighLength, &rearLeftKnee, shinLength);

// Front left leg
XRServoActuator rearRightHip(5,1500,A7,0,180,90);
XRServoActuator rearRightThigh(5,1500,A7,0,180,90);
XRServoActuator rearRightKnee(5,1500,A7,0,180,90);

XRRobotLeg rearRightLeg(&rearRightHip, hipOffset, &rearRightThigh, thighLength, &rearRightKnee, shinLength);

// Robot
XRRobotDog miniDogv2(&frontLeftLeg, &frontRightLeg, &rearLeftLeg, &rearRightLeg, bodyWidth, bodyLength);

// timers

unsigned long currentMillis;
unsigned long previousMillis;

// modes
int mode = 0;


void setup() {

  Serial.begin(115200);

  receiver.setup();
//  imu.setup();
  miniDogv2.setup();
  
}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event
          
        previousMillis = currentMillis;


        // modes - use serial 
        if (Serial.available()) {       // check for serial data
            char c = Serial.read();
  
            if (c == 'a') {             // no compliance
              mode = 0;
            }
            else if (c == 'b') {        // compliance on
              mode = 1;
            }
            else if (c == 'z') {        // calibrate hall sensors
              mode = 99;
            }
        }

        // mode - use remote
        if (receiver.isConnected)
        {
            if (receiver.toggleTop == 0) {           // no compliance
              mode = 0;
            }
            else if (receiver.toggleTop == 1) {      // compliance on
              mode = 1;
            }
    
            if (receiver.Select == 1) {              // calibrate hall sensors
              mode = 99;
            }
        }        

   
  }   // end of timed loop

} //  end of main loop
