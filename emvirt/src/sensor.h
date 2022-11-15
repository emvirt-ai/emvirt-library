#ifndef sensor_h
#define sensor_h
#include <Arduino.h>
#include "register.h"

//function for publishing sensor data
template <class type> 
void post(String sensorID, type value){
  StaticJsonDocument<128> st_doc;
  st_doc["user_id"] = userid;
  st_doc["deviceID"] = id;
  st_doc["sensorID"] = sensorID;
  st_doc["sensor_data"] = value;
  char sup[128];
  serializeJson(st_doc, sup);

  if (client.connected()) {
    boolean json = client.publish(userid, sup);
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    delay(5000);
  }
}

#endif
