#ifndef XR_IMU_H
#define XR_IMU_H

//IMU stuff
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

#include "XRComponent.h"

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high


  // MPU control/status vars
  bool dmpReady = false;  // set true if DMP init was successful
  uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
  uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
  uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
  uint16_t fifoCount;     // count of all bytes currently in FIFO
  uint8_t fifoBuffer[64]; // FIFO storage buffer
  int IMUdataReady = 0;

  // orientation/motion vars
  Quaternion q;           // [w, x, y, z]         quaternion container
  VectorInt16 aa;         // [x, y, z]            accel sensor measurements
  VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
  VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
  VectorFloat gravity;    // [x, y, z]            gravity vector
  float euler[3];         // [psi, theta, phi]    Euler angle container
  float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
  
  float pitch;
  float roll;
  float rollFiltered;
  

// IMU interrupt service routine
void dmpDataReady() {
     IMUdataReady = 1;
}        

// function that actually read the angle when the flag is set by the ISR

void readAngles()  {

    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));
     } 
     
     else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        IMUdataReady = 0;
    }
}
     



class XRImu : public XRComponent
{

  int requested_state;   
  
  // class default I2C address is 0x68
  // specific I2C addresses may be passed as a parameter here
  // AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
  // AD0 high = 0x69
  MPU6050 mpu;
  //MPU6050 mpu(0x69); // <-- use for AD0 high
 
   public:

   // constructor
   XRImu() : XRComomponent()
   {    
   }
   
   void setup()
   {
         // join I2C bus (I2Cdev library doesn't do this automatically)
      #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
          Wire.begin();
          Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
      #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
          Fastwire::setup(400, true);
      #endif
    
      // initialize device
      mpu.initialize();
      devStatus = mpu.dmpInitialize();
    
      // supply your own gyro offsets here, scaled for min sensitivity
      mpu.setXGyroOffset(53);
      mpu.setYGyroOffset(-5);
      mpu.setZGyroOffset(51);
      mpu.setXAccelOffset(-2230);
      mpu.setYAccelOffset(-698);
      mpu.setZAccelOffset(2035);  
    
      // make sure it worked (returns 0 if so)
      if (devStatus == 0) {
          // turn on the DMP, now that it's ready
          mpu.setDMPEnabled(true);
    
          // enable Arduino interrupt detection
          attachInterrupt(26, dmpDataReady, RISING);
          mpuIntStatus = mpu.getIntStatus();
    
          // get expected DMP packet size for later comparison
          packetSize = mpu.dmpGetFIFOPacketSize();
      } else {
          // ERROR!
          // 1 = initial memory load failed
          // 2 = DMP configuration updates failed
          // (if it's going to break, usually the code will be 1)
          Serial.print(F("DMP Initialization failed (code "));
          Serial.print(devStatus);
          Serial.println(F(")"));
      }
   }

   void loop()
   {
        // check for IMU inpterrupt

        if (IMUdataReady == 1) {
          readAngles();
        }

        roll = (ypr[1] * 180/M_PI) - 1.5;
        pitch = (ypr[2] * 180/M_PI) + 0.7;
    
   }


  
};



#endif
