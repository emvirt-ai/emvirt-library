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

const int led1 = 10; //Connect led1 with GPIO pins. Here we use pin 10, you can change it
const int led2 = 11; //Connect led2 with GPIO pins. Here we use pin 11, you can change it
const int led3 = 12; //Connect led3 with GPIO pins. Here we use pin 12, you can change it
const int led4 = 13; //Connect led4 with GPIO pins. Here we use pin 13, you can change it
const int led5 = 14; //Connect led5 with GPIO pins. Here we use pin 14, you can change it

void setup() {
  Serial.begin(115200);
  
  emv.wifi(ssid, pass); // Here your device connects to wifi

  emv.build(userID, fleetID); // Here your device connects to emvirtcloud

  /* digitalAct is use to setup digital Actuator, digitalAct takes 3 input, which are-
   *  1.Actuator id
   *  2.Actuator pin
   *  3.Actuator No. (Initialize by 0)
  digitalAct(Actautor_id, Actuator_pin, Actuator_No.) */
  digitalAct("A1", led1, 0); //Connect led1 with emvirtcloud
  digitalAct("A2", led2, 1); //Connect led2 with emvirtcloud
  digitalAct("A3", led3, 2); //Connect led3 with emvirtcloud
  digitalAct("A4", led4, 3); //Connect led4 with emvirtcloud
  digitalAct("A5", led5, 4); //Connect led5 with emvirtcloud

  //Configure the GPIO pin to behave either as an input or an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  //Here, it will help to control the actuator
  client.loop();
}
