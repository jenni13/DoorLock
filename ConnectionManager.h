// ConnectionManager.h

#ifndef _CONNECTIONMANAGER_h
#define _CONNECTIONMANAGER_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

//#include <ESP8266mDNS.h>
//#include <ArduinoOTA.h>

//#include <ArduinoOTA\ArduinoOTA.h>
//#include <ESP8266mDNS\ESP8266mDNS.h>

#include "Logger.h"


#define HOSTNAME "DOORLOCK001"


class ConnectionManagerClass
{
protected:


public:

	void modeAccessPoint();
	void modeAccessPointAndWifi();
	String checkStatus(int);
	//void modeOta();


};



#endif

