#include "Wire.h"
#include "XRRemoteReceiver.h"
#include "XRImu.h"
#include "XRRobotDog.h"
#include "XRRobotLeg.h"
#include "XRServoActuator.h"

// robot receiver - CE, CSN
XRRemoteReceiver receiver(27,10);

// imu - arduino interupt pin
XRImu imu(26);

// define parameters for robot---------------
#define hipOffset 76.5
#define thighLength 125
#define shinLength 125     

#define bodyWidth 126      // half the distance from the middle of the body to the hip pivot  
#define bodyLength 147.5      // distance from centre of body to shoulder pivot

// construct robot ---------------------------------------------------------


// define actuators for front left leg - servo pin, servo offset, hall effect pint, min angle, max angle, speed degrees per second
//
// min angle and max angle are mapped to 1000-2000 microseconds
// these could be -90 and 90 or -135 and 45. They can also be reversed - ie 90 down to -90. They should be set to represent a meaningful value in your 
//
// When dealing with an XRActuator one should only care about the desired "position" selected from between a minimum and maximum position
// The details of how that position are interpretted are left up to the implementation
//
// eg for a servo the position may be a target angle, for a linear actuator it may be a target length
//
XRServoActuator frontLeftHip(5,1500,A7,0,180,90);
XRServoActuator frontLeftThigh(5,1500,A7,0,180,90);
XRServoActuator frontLeftKnee(5,1500,A7,0,180,90);

// define front left leg - pass in actuators
// Kinematics is (will be) built into each leg
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

// Robot ------------------------------

// whole robot kinematics for actions, gaits and poses are managed in the Robot object
// however the robot sets targets for the legs which the legs are responsible for calculating
XRRobotDog miniDogv2(&frontLeftLeg, &frontRightLeg, &rearLeftLeg, &rearRightLeg, bodyWidth, bodyLength);

// timers

unsigned long currentMillis;
unsigned long previousMillis;

// modes
XRActuator::ActuatorMode mode = XRActuator::ActuatorMode::normal;

void setup() {

  Serial.begin(115200);

  receiver.setup();
  imu.setup();
  miniDogv2.setup();
  
}

void loop() {

  // update the IMU. values are available through Imu.pitch and Imu.Roll
  imu.loop();

  // update the receiver. this can be interogated for whether it's connected and for its values
  receiver.loop();

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event
        previousMillis = currentMillis;

        XRActuator::ActuatorMode newMode = mode;
        
        // modes - use serial 
        if (Serial.available()) {       // check for serial data
            char c = Serial.read();
  
            if (c == 'a') {             // no compliance
              newMode = XRActuator::ActuatorMode::normal;
            }
            else if (c == 'b') {        // compliance on
              newMode = XRActuator::ActuatorMode::compliant;
            }
            else if (c == 'z') {        // calibrate hall sensors
              newMode = XRActuator::ActuatorMode::calibration;
            }
        }

        // mode - use remote
        if (receiver.isConnected)
        {
            if (receiver.toggleTop == 0) {           // no compliance
              newMode = XRActuator::ActuatorMode::normal;
            }
            else if (receiver.toggleTop == 1) {      // compliance on
              newMode = XRActuator::ActuatorMode::compliant;
            }
    
            if (receiver.Select == 1) {              // calibrate hall sensors
              newMode = XRActuator::ActuatorMode::calibration;
            }
        }        

        if (newMode != mode)
        {
            miniDogv2.SetMode(newMode);
            mode = newMode;
        }
   
  }   // end of timed loop

  miniDogv2.loop();


  //
  // Motion for the dog will be handled with reusable objects I'm calling Actions, Poses and Gaits
  //
  // it will be possible to simply apply an action, pose or a gait to the dog, and in fact smoothly blend between them
  //
  // this uses techniques similar to those used for animation in the games industry
  //

} //  end of main loop
