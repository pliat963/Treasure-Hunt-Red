#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>  
#include "../SECRETS.h"

const char* ssid = SSID_1;
const char* password = PASSWORD_1;

ESP8266WebServer server(80);


void setup() {

  WiFi.softAP(ssid, password);
  Serial.begin(9600); // Starts the serial communication
  server.begin();
  Serial.println("start!");
}

void loop() {

  server.handleClient();

}