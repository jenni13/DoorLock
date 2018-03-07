#include <ArduinoOTA.h>
#include <dummy.h>
#include "DisplayManager.h"
#include "Tools.h"

ESP8266WebServer server(80);

/******/

void handleRoot()
{
	server.send(200, "text/html", "<h1>Bienvenue sur DoorLock </h1>");
	
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


	if (!configuration.itExist()) // mode access point only
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
	if (clean)
	{
		configuration.formatConfigFile();
	}
	else
	{
		
		configuration.writeConfigFile("SSID", "abcdef");
		configuration.writeConfigFile("SSID", "ghij");
		configuration.writeConfigFile("NOM", "Jean");
		configuration.writeConfigFile("NOM", "Bono");
		configuration.writeConfigFile("SSID", "klm");
		configuration.writeConfigFile("NOM", "Charly");
		configuration.writeConfigFile("PWD", "pass");


		Serial.println("lecture fin:");
		configuration.readConfigFile();

		Serial.println("Je cherche charly");
		configuration.readValueConfigFile("NOM",3);

		configuration.deleteKeyConfigFile("SSID");
		Serial.println("lecture fichier ssid supprime:");
		configuration.readConfigFile();

		configuration.deleteKeyConfigFile("PWD");

		Serial.println("lecture fichier sans PWD:");
		configuration.readConfigFile();

	}
	SPIFFS.end();
}
void loop()
{
	
	server.handleClient();
	
	//configuration.readConfigFile();
	//ArduinoOTA.handle();
		

}
