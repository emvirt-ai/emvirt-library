/*************************************************************
emvirt is a platform to control your device over the Internet.
You can easily build graphic interfaces for all your projects.
*************************************************************/

//Include emv library for using emvirt features
#include <emv.h>

const char* ssid = "WIFI_SSID";         //Enter your Wifi SSID
const char* pass = "WIFI_PASSWORD";     //Enter your Wifi password
const char* userID = "Username";        //Enter your emvirt username
const char* fleetID = "Fleet_ID";       //Enter your fleet id

const int led = 33; //Connect led with GPIO pins. Here we use pin 33, you can change it

void setup() {
  Serial.begin(115200);
  
  emv.wifi(ssid, pass); // Here your device connects to wifi

  emv.build(userID, fleetID); // Here your device connects to emvirtcloud

  /* digitalAct is use to setup digital Actuator, digitalAct takes 3 input from you-
   *  1.Actuator id
   *  2.Actuator pin
   *  3.Actuator No.
  digitalAct(Actautor_id, Actuator_pin, Actuator_No.) */
  digitalAct("A1", led, 0); //Connect LED with emvirtcloud

  pinMode(led, OUTPUT); //Configure the GPIO pin to behave either as an input or an output.
}

void loop() {
  //Here, it will help to control the actuator
  client.loop();
}
