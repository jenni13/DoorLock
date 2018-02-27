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
		Serial.println("lecture ssid 1:");
		configuration.readConfigFile();
		configuration.writeConfigFile("SSID", "ghij");
		Serial.println("lecture ssid 2:");
		configuration.readConfigFile();
		configuration.writeConfigFile("NOM", "Jean");
		/*if (configuration.itExist())
			Serial.println("creation ok");*/
		
		configuration.writeConfigFile("NOM", "Bono");
		Serial.println("lecture nom:");
		configuration.readConfigFile();

		configuration.writeConfigFile("SSID", "klm");
		Serial.println("lecture klm:");
		configuration.readConfigFile();
		configuration.writeConfigFile("NOM", "Jagger");
		configuration.writeConfigFile("SSID", "opqr");
		configuration.writeConfigFile("PWD", "passowr");
		configuration.writeConfigFile("NOM", "dfgdfg");

		Serial.println("lecture fin:");
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
