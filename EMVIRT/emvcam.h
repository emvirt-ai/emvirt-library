#ifndef emvcam_h
#define emvcam_h
#include "src/stream.h"
#include "src/WiFi_AP.h"
#include "src/register.h"

class EMVCAM {
  public:
    void wifiHost(){
      EEPROM.begin(400);
      if(!CheckWIFICreds()){
        Serial.println("No WIFI credentials stored in memory. Loading form...");
        while(loadWIFICredsForm());
      }
    }
    void reg(const char* userName, const char* fleetID){
      if(!alreadyRegistered()){
        sendRegisterDevice(userName, fleetID);
      }
      cam(userName, fleetID);
    }
};

EMVCAM emvcam;

#endif
