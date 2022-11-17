/*************************************************************
emvirt is a platform to control your device over the Internet.
You can easily build graphic interfaces for all your projects.
*************************************************************/

// *****Select camera model***** //
//#define CAMERA_MODEL_WROVER_KIT
#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
//#define CAMERA_MODEL_AI_THINKER

//Include emv library for using emvirt features
#include <emv.h>
#include <emvcam.h>

const char* ssid = wifi_ssid;         //Enter your Wifi SSID
const char* pass = wifi_pass;         //Enter your Wifi password
const char* userName = wifi_user;     //Enter your emvirt username
const char* fleetID = wifi_fleet;     //Enter your emvirt fleet

void setup() {
  Serial.begin(115200);
  
  emvcam.wifiHost(); //Here your device become WiFi Hotspot

  emv.wifi(ssid, pass); // Here your device connects to WiFi
  
  emvcam.reg(userName, fleetID); // Here your device register itself with emvirt
  
  setupCam(); // Here device completes the setup for your camera
}

void loop() {
  stream(); // Start Streaming
}
