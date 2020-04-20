#ifndef XRREMOTERECEIVER_H
#define XRREMOTERECEIVER_H

#include <nRF24L01.h>
#include <RF24.h>
#include "XRComponent.h"


//**************remote control****************
struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO 

    int16_t menuDown;      
    int16_t Select; 
    int16_t menuUp;  
    int16_t toggleBottom;  
    int16_t toggleTop; 
    int16_t toggle1; 
    int16_t toggle2; 
    int16_t mode;  
    int16_t RLR;
    int16_t RFB;
    int16_t RT;
    int16_t LLR;
    int16_t LFB;
    int16_t LT;
    int16_t checkit;
    int16_t checkit2;
};


const byte addresses[][6] = {"00001", "00002"};

class XRRemoteReceiver : public XRComponent
{
  RF24 radio;
  RECEIVE_DATA_STRUCTURE mydata_remote;
  
  public:

    bool isConnected;
    int RLR;
    int RFB;
    int RT;
    int LLR;
    int LFB;
    int LT;
    int toggleTop;
    int toggleBottom;
    int toggle1;
    int toggle2;
    int Select;

    unsigned long previousSafetyMillis;
    
  public:
  
  XRRemoteReceiver(int ce,int csn) : radio(ce,csn)
  {
    isConnected = false;
  }

  void setup()
  {
      radio.begin();
      radio.openWritingPipe(addresses[0]); // 00002
      radio.openReadingPipe(1, addresses[1]); // 00001
      radio.setPALevel(RF24_PA_MIN);
    
      radio.startListening();
      isConnected = true;
  }

  void loop()
  {
        // receive radio data

        unsigned long currentMillis = millis();
        
        if (radio.available()) {
                    radio.read(&mydata_remote, sizeof(RECEIVE_DATA_STRUCTURE));
                    previousSafetyMillis = currentMillis;
        }

        // check if remote has become disconnected

        if ( currentMillis - previousSafetyMillis > 500) {         
            Serial.println("*no remote data* ");
            ZeroValues();
            isConnected = false;
        } 

        // use values if the remote is connected ok
        
        else {
          isConnected = true;
          
          RLR = mydata_remote.RLR;
          RFB = mydata_remote.RFB;
          RT = mydata_remote.RT;
          LLR = mydata_remote.LLR;
          LFB = mydata_remote.LFB;
          LT = mydata_remote.LT;
          toggleTop = mydata_remote.toggleTop;
          toggleBottom = mydata_remote.toggleBottom;
          toggle1 = mydata_remote.toggle1;
          toggle2 = mydata_remote.toggle2;
          Select = mydata_remote.Select;
        }

              // Zero values to swing around +/- 0

        RLR = RLR - 512;      // get to +/- zero value
        RFB = RFB - 512;
        RT = RT - 512;
        LLR = LLR - 512;
        LFB = LFB - 512;
        LT = LT - 512;

        // Threshold remote data for slop in sticks

        if (RLR > 50) {
          RLR = RLR -50;
        }
        else if (RLR < -50) {
          RLR = RLR +50;
        }
        else {
          RLR = 0;
        }
        //*******
        if (RFB > 50) {
          RFB = RFB -50;
        }
        else if (RFB < -50) {
          RFB = RFB +50;
        }
        else {
          RFB = 0;
        }
        //******
        if (RT > 50) {
          RT = RT -50;
        }
        else if (RT < -50) {
          RT = RT +50;
        }
        else {
          RT = 0;
        }
        //******
        if (LLR > 50) {
          LLR = LLR -50;
        }
        else if (LLR < -50) {
          LLR = LLR +50;
        }
        else {
          LLR = 0;
        }
        //*******
        if (LFB > 50) {
          LFB = LFB -50;
        }
        else if (LFB < -50) {
          LFB = LFB +50;
        }
        else {
          LFB = 0;
        }
        //******
        if (LT > 50) {
          LT = LT -50;
        }
        else if (LT < -50) {
          LT = LT +50;
        }
        else {
          LT = 0;
        }      

  }

  void ZeroValues()
  {
      RLR = 512;
      RFB = 512;
      RT = 512;
      LLR = 512;
      LFB = 512;
      LT = 512;
      toggleTop = 0;
      toggleBottom = 0;
      toggle1 = 0;
      toggle2 = 0;
      Select = 0;
  }

};
#endif
