#ifndef _TOOLS_h
#define _TOOLS_h

//libraries used

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <FS.h> //SPIFFS

#include "ConfigManager.h"


const char *ssid = "DOORLOCK001";
const char *password = "password"; //at least 8 character long

bool config_is_defined = true;

ConfigManagerClass configuration;
#endif
