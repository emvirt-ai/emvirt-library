#ifndef stream_ws_h
#define stream_ws_h

#include <ArduinoWebsockets.h>
#include <Arduino.h>
#include "esp_camera.h"
#include "register.h"

using namespace websockets;
WebsocketsClient client1;
char host[100];
#include "camera_pins.h"

String un, fi;

void cam(const char* userName, const char* fleetID){
  un = userName;
  fi = fleetID;
}

void regCam(String userName, String fleetID){
  String serverName = "https://api.emvirtcloud.com/stream_started/";
  
  if(WiFi.status()== WL_CONNECTED){
  HTTPClient http;
  String serverPath = serverName + "?userid=" + userName + "&cam_id=" + id + "&fleet_id=" + fleetID;
  Serial.println(serverPath);

  http.begin(serverPath.c_str());
  http.addHeader("Content-Type", "application/json");
  //http.addHeader("Accept", "application/json");
  
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  } 
  else {
    Serial.println("WiFi Disconnected");
  }
}

void setupCam(){
  const char* websocket_server_host = "ws://iotcam.emvirtcloud.com:38888/writeStream?userid=";
  regCam(un, fi);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 5;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
    esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  strcpy(host, websocket_server_host);
  strcat(host, un.c_str());
  strcat(host, "&camid=");
  strcat(host, id.c_str());
  Serial.println(host);
  
  while(!client1.connect(host)){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Camera Connected with emvirt :)");
}

void stream(){
   camera_fb_t *fb = esp_camera_fb_get();
  if(!fb){
    Serial.println("Camera capture failed");
    esp_camera_fb_return(fb);
    return;
  }

  if(fb->format != PIXFORMAT_JPEG){
    Serial.println("Non-JPEG data not implemented");
    return;
  }

  client1.sendBinary((const char*) fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

#endif
