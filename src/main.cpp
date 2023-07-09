#include <Arduino.h>

#include <Wire.h>
#include <Debug.h>
#include <definition.h>
#include "imuread.h"
#include "sensorlab.h"
#include <Scan.h>
#include "SensorFusion.h" 
#include "simspirit_now.h"

#include <BTNS.h>
#include <LEDS.h>
#include <proximity.h>

bool drift = false; //enable to allow use of sparkfun library/ disable to use adafruit library

SF fusion;
/// @brief
float gx, gy, gz, ax, ay, az, mx, my, mz;
float deltat;
bool imuFound = false;

void setup(){  

  Serial.begin(115200);
  delay(1000);

  initPins();

  ledSeq();
    
  greenLed(on);
  delay(1000);
  blueLed(off);
  delay(1000);
  
  PRINTLINE("Led Flased Sequence done: ");
  PRINTLINE("____________________");

  PRINTLINE("Starting Tasks: ");

  imuFound = imusetup();
  if(imuFound){
    sensorsetup();
  }
  
  proximityFound = proximitySetup();

  proximityFound = false;

  delay(500);
  
  //app_main();
  deviceConnected = setupTXRX();

  PRINTLINE("Tasks running: ");  
}

void loop() {

  SetupBoardDriver();
  SetupConnections();
  
}

//Setup_Connections: Ble Connection Monitor 
void SetupConnections(){
  //Serial.print("Setup_Connections running on core ");    
  //
  if (deviceConnected) {
    //Set yaw pitch roll temp Characteristic value and notify connected SimSpirit
    //yawCharacteristic->setValue(String(yaw));
    /*
    yawCharacteristic->setValue<int>(yaw*100);
    pitchCharacteristic->setValue<int>(pitch*100);
    rollCharacteristic->setValue<int>(roll*100);
    */   
    if(nearToFar){
      //-1 signal tells the mainboard that user removed HT from ear
      //only re-disabled by pressing the calibrate button
      //on the mainboard; always perform calibration any time CMD transitions from -1 to any number; it shows that Pair was pressed
      //cmdCharacteristic->setValue<int>(-1);
      loopTXRX(yaw,pitch,roll,-1);
      PRINTLINE("HT removed from Ear: Sending -1 to SimSpirit");         
    }
    else{
      //cmdCharacteristic->setValue<int>(cmdBTN); 
      loopTXRX(yaw,pitch,roll,cmdBTN);
      PRINTLINE("HT not removed from Ear: Sending BTN cmd to SimSpirit");         
    }    
    //PRINTLINE("connection ble");
    if ((millis() - lastTime) > timerDelay) {
      randomLed();        
      //Notify YAW PITCH ROLL AND temperature reading from sensor 
      lastTime = millis();
    }
  }
  else{
    flashBlue();
  }  
}

void SetupBoardDriver(){
    //Serial.print("Setup_BoardDriver running on core ");
    processBtn();
    if(proximityFound){
      proximity = proximitySense(); 
      if(proximity == 0 || proximity == -1){
        if(proximity != proximity_old){
          if(proximity == -1){
            nearToFar = true;
          }
          else{
            //nearToFar = false;
          }
          proximity_old = proximity;
        }
      }      
    }
    if(!drift){
      if(imuFound){
        if(imuloop(ax, ay, az, gx, gy, gz)){
          /// @brief fusion
          deltat = fusion.deltatUpdate(); 
          fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, deltat); 
          pitch = fusion.getPitch();
          roll = fusion.getRoll(); 
          yaw = 360.00-fusion.getYaw();
          PRINTLINE("_____");
          PRINTF("Roll_1 %0.1f, Pitch_1 %0.1f, Yaw_1 %0.1f\n", roll, pitch, yaw); 
          PRINTLINE();
          PRINTLINE("_____");
        }
      }
    }
    else{
      if(imuFound){
        sensorloop(roll, pitch, yaw);
        PRINTLINE("_____");
        PRINTF("Roll_2 %0.1f, Pitch_2 %0.1f, Yaw_2 %0.1f\n", roll, pitch, yaw); 
        PRINTLINE();
        PRINTLINE("_____");
      }
    }
    Serial.println("HT-MB Pair Status: " + String(ht_paired));
}
