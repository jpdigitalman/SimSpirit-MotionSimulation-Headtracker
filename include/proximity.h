#include "RPR-0521RS.h"

RPR0521RS rpr0521rs;

bool proximitySetup() {
  
  //Wire.begin(19, 18);
    
  if(rpr0521rs.init() == 0){
    return true;
  }
  else{
    Serial.println("Proximity Sensor Not detected");
    return false;
  }
  
}

int proximitySense() {

  bool rc;
  unsigned short ps_val;
  float als_val;
  bool near_far;
  int res = -3;

  rc = rpr0521rs.get_psalsval(&ps_val, &als_val);
  if (rc == 0) {
    PRINT("RPR-0521RS (Proximity)     = ");
    PRINT(ps_val);
    PRINT(" [count]");
    near_far = rpr0521rs.check_near_far(ps_val);
        
    if (near_far == RPR0521RS_NEAR_VAL) {
      PRINTLINE(" Near");
      res = 0;
    } else {
      PRINTLINE(" Far");
      res = -1;
    }

    if (als_val != RPR0521RS_ERROR) {
      PRINT("RPR-0521RS (Ambient Light) = ");
      PRINT(als_val);
      PRINTLINE(" [lx]");
      PRINTLINE();
    }

    return res;
  }

  return res;
 
}
