#include <SPI.h>
#include "XRRemoteReceiver.h"
#include "XRImu.h"
#include "XRRobotDog.h"
#include "XRRobotLeg.h"
#include "XRServoActuator.h"

int x;
int y;
int z;

int yaw;
int r;
int p;

XRRemoteReceiver receiver(27,10);


// timers

unsigned long currentMillis;
unsigned long previousMillis;
unsigned long previousWalkMillis;
unsigned long previousSafetyMillis;

// There is a first order filter running on all motions, allbeit turned down a lot. It's also used for the reactivity of the compliance

float multiplierKneesRight = 2;
float multiplierShouldersRight = 2;
float multiplierHipsRight = 0;

float multiplierKneesLeft = 2;
float multiplierShouldersLeft = 2;
float multiplierHipsLeft = 0;

// filters values

int filterKneesRight = 15;
int filterShouldersRight = 15;
int filterHipsRight = 25;

int filterKneesLeft = 15;
int filterShouldersLeft = 15;
int filterHipsLeft = 25;

// global joint threshold value for hall effects
int threshholdGlobal =  5;



// modes

int mode = 0;



void setup() {


  receiver.setup();

 

  Serial.begin(115200);

 
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
        if (receiver.toggleTop == 0) {           // no compliance
          mode = 0;
        }
        else if (receiver.toggleTop == 1) {      // compliance on
          mode = 1;
        }

        if (receiver.Select == 1) {              // calibrate hall sensors
          mode = 99;
        }        

   
  }   // end of timed loop

} //  end of main loop
