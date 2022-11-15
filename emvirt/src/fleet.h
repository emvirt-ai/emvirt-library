#ifndef fleet_h
#define fleet_h
#include <Arduino.h>
#include "register.h"

void fleet(const char* userName, const char* fleetID) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.emvirtcloud.com/device_registered/");
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<100> doc;
    doc["userid"] = userName;
    doc["fleetid"] = fleetID;
    doc["deviceID"] = id;

    String request;
    serializeJson(doc, request);
    Serial.println(request);

    int httpResponseCode = http.POST(request);
    String response = http.getString();
    Serial.println(response);
    StaticJsonDocument<50> doc1;
    deserializeJson(doc1, response);
    JsonObject obj = doc1.as<JsonObject>();
    int msg = obj[String("message")];

    if (msg == 0) {
      Serial.println("false");
      sendRegisterDevice(userName, fleetID);
    } else if (msg == 1) {
      Serial.println("true");
    }
  }
}

#endif
