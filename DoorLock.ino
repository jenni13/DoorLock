#include "DisplayManager.h"
#include "Tools.h"

ESP8266WebServer server(80);

/******/

void handleRoot()
{
	server.send(200, "text/html", "<h1>Bienvenue sur DoorLock </h1>");
	String s = configuration.readConfigFile();
	server.sendContent(s);
}

/****/

void setup()
{
	Serial.begin(115200);

	/* a decommenter quand il y aura l'ecran
	display.init();
	display.setContrast(255);
	display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
	display.setFont(ArialMT_Plain_16);
	display.drawString(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, "Initialisation\n");
	display.display();
	delay(10);*/

	
	if (!configuration.itExist(FILENAME)) // mode access point only
	{
		connect.modeAccessPoint();
		//CommandManager.WritePCF8574(0xFF);
		/*if (ota_ok)
			connect.modeOta();*/
		
	}
	else // wifi appairage and access point
	{
		connect.modeAccessPointAndWifi();		
	}
	server.on("/commande", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
	
	/****SPIFFS***/
	
	SPIFFS.begin();
	configuration.writeConfigFile("j'ai ecrits");
	if (configuration.itExist(FILENAME))
		Serial.println("creation ok");


}

void loop()
{
	
	server.handleClient();
	//ArduinoOTA.handle();
		

}
