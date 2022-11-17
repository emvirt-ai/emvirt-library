#ifndef emv_h
#define emv_h

#include <WiFi.h>
#include <PubSubClient.h>
#include <nvs_flash.h>
#include "src/sensor.h"
#include "src/actuator.h"
#include "src/fleet.h"

//const char* mqtt_server = "192.168.1.10";
const char* mqtt_server = "emvirtcloud.com";  //MQTT server
int mqtt_port = 31883;                        //MQTT port

//function to check that device is already registered or not
bool alreadyRegistered() {
      preferences.begin("emvAgentPrefs", false);
      id = preferences.getString("devid", "");
      preferences.end();
      if(id.length()!= 8)
        return false;
      return true;
}

class EMV {
  private:
    char ssid;
    char password;
    char userName;
    char fleetID;
  public:
  //function for wifi to connect
  void wifi(const char* ssid, const char* pass){
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address of this device: ");
    Serial.println(WiFi.localIP());
  }

  //function to setup server & port
  void build(const char* userName, const char* fleetID){
    //If device is not registered, then it will register
    if(!alreadyRegistered()){
      sendRegisterDevice(userName, fleetID);
    }
    fleet(userName, fleetID);
    postid(userName); //send userName
    
    client.setServer(mqtt_server, mqtt_port);
    while (!client.connected()) {
      Serial.println("Connecting to emvirtcloud...");
      
      char Buf[50];
      id.toCharArray(Buf, 64);
      if (client.connect(Buf)) {
        Serial.println("connected");
        client.setCallback(Callback);
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
      }
    }
  }

  //function to erase all partition
  void reboot() {
    nvs_flash_erase(); // erase the NVS partition and...
    nvs_flash_init(); // initialize the NVS partition.
    while(true);
  }
};

EMV emv;  //creation of object of class EMV

#endif
