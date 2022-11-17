#ifndef actuator_h
#define actuator_h
#include <Arduino.h>
//#include <Servo.h>
#include "register.h"
#define SIZE 10

//struct for sensorID & sensorPin
struct actuator {
  char actuatorID[64];
  int actuatorPin;
  int isAnalog;
};

struct actuator allActuator[SIZE]; //Array of struct
//Servo servo;

//callback function for actuator
void Callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < SIZE; i++) {
    if (strcmp(topic, allActuator[i].actuatorID) == 0) {
      if (allActuator[i].isAnalog == 1) {
        char value[3];
        for (int i = 0; i < length; i++) {
          //Serial.print((char)payload[i]);
          value[i] = (char)payload[i];
        }
        int n;
        n = atoi(value);
        analogWrite(allActuator[i].actuatorPin, n);
        //Serial.println(allActuator[i].actuatorPin);
        //Serial.println(n);
        //servo.write(n);
      } else {
        char topic2[32];
        int l = strlen(topic);
        memset(topic2, '_', 14);
        topic2[11] = '/';
        topic2[12] = 'f';
        topic2[13] = '\0';
        memcpy(topic2, topic, l);
        int value = (char)payload[0];
        if (value == '1') {
          digitalWrite(allActuator[i].actuatorPin, HIGH);
          boolean pub = client.publish(topic2, "1");
        } else if (value == '0') {
          digitalWrite(allActuator[i].actuatorPin, LOW);
          boolean pub = client.publish(topic2, "0");
        }
      }
      break;
    }
  } 
}

//function for digital actuator
void digitalAct(String actuatorID, int actuatorPin, int count) {
  if (client.connected()) {
    String topic = id + "/" + actuatorID;
    topic.toCharArray(allActuator[count].actuatorID, 64);
    //Serial.println(topic);
    boolean sub = client.subscribe(allActuator[count].actuatorID);
//    Serial.print("subscribed .. ");
//    Serial.println(sub);
    allActuator[count].actuatorPin = actuatorPin;
  } else {
//    Serial.print("failed, rc=");
//    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    delay(5000);
  }
}

//function for analog actuator
void analogAct(String actuatorID, int actuatorPin, int count) {
  //servo.attach(actuatorPin);
  if (client.connected()) {
    String topic = id + "/" + actuatorID;
    topic.toCharArray(allActuator[count].actuatorID, 64);
    //Serial.println(topic);
    boolean sub = client.subscribe(allActuator[count].actuatorID);
    allActuator[count].actuatorPin = actuatorPin;
    allActuator[count].isAnalog = 1;
  } else {
//    Serial.print("failed, rc=");
//    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    delay(5000);
  }
}

#endif
