#include "ConfigManager.h"
#include "Tools.h"


const char *ssid_wifi = "SFR_6CD0";
const char *password_wifi = "fa4rselutockervolder";

ESP8266WebServer server(80);

/******/

void handleRoot()
{
	server.send(200, "text/html", "<h1>Bienvenue sur DoorLock </h1>");
}

void modeAccessPoint()
{
	WiFi.mode(WIFI_AP); //only Access point. to do both -> (WiFi.mode(WIFI_AP_STA));
	WiFi.softAP(ssid, password);
	Serial.println();

	Serial.print("Server IP address: ");
	Serial.println(WiFi.softAPIP());

	Serial.print("Server MAC address: ");
	Serial.println(WiFi.softAPmacAddress());

	
}

void modeAccessPointAndWifi()
{
	WiFi.mode(WIFI_AP_STA);
	
	WiFi.softAP(ssid, password);
	Serial.println();

	Serial.print("Server IP address: ");
	Serial.println(WiFi.softAPIP());

	Serial.print("Server MAC address: ");
	Serial.println(WiFi.softAPmacAddress());


	WiFi.begin(ssid_wifi, password_wifi);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(".");
	}

	//If connection successful show IP address in serial monitor
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid_wifi);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}


/****/

void setup()
{
	Serial.begin(115200);

	if (!config_is_defined) // mode access point only
	{
		modeAccessPoint();
	}
	else // wifi appairage and access point
	{
		modeAccessPointAndWifi();
	}
	server.on("/commande", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
	
	/****SPIFFS***/
	
	SPIFFS.begin();
	configuration.writeConfigFile();



}

void loop()
{
	
	server.handleClient();
	//configuration.readConfigFile(); //Test configuration.txt

}
