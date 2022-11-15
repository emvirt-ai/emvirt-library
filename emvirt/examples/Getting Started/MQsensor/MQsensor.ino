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

int mq135 = 35; //Connect mq135 with GPIO pins. Here we use pin 35, you can change it

long previousMillis = 0;
long interval = 500; //Setup millisecond to send data (Recommended-500)

void setup() {
  // See the connection status in Serial Monitor
  Serial.begin(115200);
  
  // Here your device connects to wifi
  emv.wifi(ssid, pass);

  // Here your device connects to emvirtcloud
  emv.build(userID, fleetID);

  //Configure the GPIO pin to behave either as an input or an output.
  pinMode(mq135, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    //Write your logic
    int sensorValue = analogRead(mq135);
    float volts = sensorValue * 5;
    volts = volts / 1023;

    /* post is use in sending data to emvirtcloud, post takes 2 input, which are-
    *Sensor id
    *Value
    post(Sensor_ID, Value) */
    post("S1", volts);
  }
}
