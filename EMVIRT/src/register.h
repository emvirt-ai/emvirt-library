#ifndef RegisterDevice_h
#define RegisterDevice_h
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>

WiFiClient espClient;
PubSubClient client(espClient);
Preferences preferences;
String devid; //deviceid for emv
String id;

// function to take userid
const char* userid;
String user_id;
void postid(const char* userName){
  userid = userName;
  user_id = userName;
}

//function to register device with emvirtcloud
void sendRegisterDevice(const char* userName,const char* fleetID) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.emvirtcloud.com/register_device/");
    http.addHeader("Content-Type", "application/json");
    
    StaticJsonDocument<100> doc;
    doc["user_id"] = userName;
    doc["fleetid"] = fleetID;
    doc["device_type"] = "mcu";
    JsonObject mac_addresses  = doc.createNestedObject("mac_addresses");
    mac_addresses["wlan0"] = WiFi.macAddress();
    String requestBody;
    serializeJson(doc, requestBody);
    
    int httpResponseCode = http.POST(requestBody);
    String response = http.getString();
//    Serial.println(response);
    StaticJsonDocument<50> doc1;
    deserializeJson(doc1, response);
    JsonObject obj = doc1.as<JsonObject>();
    String d=obj[String("device_id")];
//    Serial.println(d);
    devid = d;
    
    preferences.begin("emvAgentPrefs", false);
    preferences.putString("devid", devid); 
    preferences.end();
    Serial.println("Yeah! Your device is registered successfully with emvirt :)");
    Serial.print("Your Device Id: ");
    Serial.println(devid);
    id =d ;
    http.end();
  }
}

#endif
