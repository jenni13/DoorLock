// ConnectionManager.h

#ifndef _CONNECTIONMANAGER_h
#define _CONNECTIONMANAGER_h

#include "ConfigManager.h"
#include "Logger.h"


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//#include <ESP8266mDNS>



#define HOSTNAME "DOORLOCK001"


class ConnectionManagerClass
{
protected:


public:

	String selectSsid(ConfigManagerClass config, int);
	String selectPwd(ConfigManagerClass config, int index);
	void modeAccessPoint();
	void modeAccessPointAndWifi(String ssid,String pwd);
	String checkStatus(int);
	void modeOta();



};



#endif

