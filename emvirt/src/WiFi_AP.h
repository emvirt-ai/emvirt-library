#ifndef WiFi_AP_h
#define WiFi_AP_h
#include <Arduino.h>
#include "EEPROM.h"
#include "HTML.h"
#include <WebServer.h>
WebServer server(80);

String wifi_ssid, wifi_pass, wifi_user, wifi_fleet;

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

/*
 * Function for writing WiFi creds to EEPROM
 * Returns: true if save successful, false if unsuccessful
 */
bool writeToMemory(String ssid, String pass, String user, String fleetid){
  char buff1[30];
  char buff2[30];
  char buff3[30];
  char buff4[30];
  ssid.toCharArray(buff1,30);
  pass.toCharArray(buff2,30);
  user.toCharArray(buff3,30);
  fleetid.toCharArray(buff4,30);
   
  EEPROM.writeString(50,buff1);
  EEPROM.writeString(100,buff2);
  EEPROM.writeString(150,buff3);
  EEPROM.writeString(200,buff4);
  delay(100);
  String s = EEPROM.readString(50);
  String p = EEPROM.readString(100);
  String u = EEPROM.readString(150);
  String f = EEPROM.readString(200);
  //#if DEBUG
  Serial.print("Stored SSID, password, are: ");
  Serial.print(s);
  Serial.print(" / ");
  Serial.print(p);
  Serial.print(" / ");
  Serial.print(u);
  Serial.print(" / ");
  Serial.print(f);
  //#endif
  if(ssid == s && pass == p && user == u && fleetid == f){
    return true;  
  }else{
    return false;
  }
}


/*
 * Function for handling form
 */
void handleSubmit(){
  String response_success="<h1>Success</h1>";
  response_success +="<h2>Device will restart in 3 seconds</h2>";

  String response_error="<h1>Error</h1>";
  response_error +="<h2><a href='/'>Go back</a>to try again";
  
  if(writeToMemory(String(server.arg("ssid")),String(server.arg("password")),String(server.arg("username")),String(server.arg("fleetid")))){
     server.send(200, "text/html", response_success);
     EEPROM.commit();
     delay(3000);
     ESP.restart();
  }else{
     server.send(200, "text/html", response_error);
  }
}

/*
 * Function for home page
 */
void handleRoot() {
  if (server.hasArg("ssid")&& server.hasArg("password")&& server.hasArg("username")&& server.hasArg("fleetid")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
}

/*
 * Function for loading form
 * Returns: false if no WiFi creds in EEPROM
 */
bool loadWIFICredsForm(){
  String s = EEPROM.readString(50);
  String p = EEPROM.readString(100);
  String u = EEPROM.readString(150);
  String f = EEPROM.readString(200);
  
  const char* ssidd     = "ESP-Cam";
  const char* password = "emvirt123";

  Serial.println("Setting Access Point...");
  
  WiFi.softAP(ssidd, password);
  
  IPAddress IP = WiFi.softAPIP();
  
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.println("HTTP server started");
 
  while(s.length() <= 0 && p.length() <= 0 && u.length() <= 0 && f.length() <= 0){
    server.handleClient();
    delay(100);
  }
  
  return false;
}

/*
 * Function checking WiFi creds in memory 
 * Returns: true if not empty, false if empty
 */
bool CheckWIFICreds(){
  Serial.println("Checking WIFI credentials");
  String s = EEPROM.readString(50);
  wifi_ssid = s;
  String p = EEPROM.readString(100);
  wifi_pass = p;
  String u = EEPROM.readString(150);
  wifi_user = u;
  String f = EEPROM.readString(200);
  wifi_fleet = f;
  //#if DEBUG
  Serial.print("Found credentials: ");
  Serial.print(s);
  Serial.print("/");
  Serial.print(p);
  Serial.print("/");
  Serial.print(u);
  Serial.print("/");
  Serial.print(f);
  delay(5000);
  //#endif
  if(s.length() > 0 && p.length() > 0 && u.length() > 0 && f.length() > 0){
    return true;
  }else{
    return false;
  }
}

#endif
