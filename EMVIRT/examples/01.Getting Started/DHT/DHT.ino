/*************************************************************
emvirt is a platform to control your device over the Internet.
You can easily build graphic interfaces for all your projects.
*************************************************************/

//Include emv library for using emvirt features
#include <emv.h>
#include <DFRobot_DHT11.h> //DHT library you can take according to you

const char* ssid = "WIFI_SSID";         //Enter your Wifi SSID
const char* pass = "WIFI_PASSWORD";     //Enter your Wifi password
const char* userID = "Username";        //Enter your emvirt username
const char* fleetID = "Fleet_ID";       //Enter your fleet id

DFRobot_DHT11 DHT; //DHT library

int DHT11_PIN = 32; //Connect DHT11_PIN with GPIO pins. Here we use pin 32, you can change it

long previousMillis = 0;
long interval = 500; //Setup millisecond to send data (Recommended-500)

void setup() {
  Serial.begin(115200);
  
  emv.wifi(ssid, pass);  // Here your device connects to wifi

  emv.build(userID, fleetID);  // Here your device connects to emvirtcloud

  pinMode(DHT11_PIN, INPUT);  //Configure the GPIO pin to behave either as an input or an output.
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis; 
    DHT.read(DHT11_PIN);
    
    //Write your logic
    float temp = DHT.temperature; //Read Temperature
    float hum = DHT.humidity;     //Read Humidity

    /* post is use in sending data to emvirtcloud, post takes 2 input, which are-
    *Sensor id
    *Value
    post(Sensor_ID, Value) */
    post("S1", temp); 
    post("S2", hum);
  }
}
