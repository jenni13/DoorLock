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

	SPIFFS.begin();
	if (configuration.itExist()) // mode access point only
	{
		connect.modeAccessPointAndWifi();

	}
	else // wifi appairage and access point
	{
		connect.modeAccessPoint();
		//CommandManager.WritePCF8574(0xFF);

	}
	server.on("/commande", handleRoot);
	server.begin();
	Serial.println("HTTP server started");



	/****SPIFFS***/

	if (clean)
	{
		configuration.formatConfigFile();
	}
	else
	{
		/*test*/
		/*configuration.writeConfigFile("SSID", "abcdef");
		configuration.writeConfigFile("SSID", "ghij");
		configuration.writeConfigFile("NOM", "Jean");
		configuration.writeConfigFile("NOM", "Bono");
		configuration.writeConfigFile("SSID", "klm");
		configuration.writeConfigFile("NOM", "Charly");
		configuration.writeConfigFile("NOM", "Charles");
		configuration.writeConfigFile("NUM", "04423");
		configuration.writeConfigFile("NUM", "044");


		Serial.println("lecture fin:");
		configuration.readConfigFile();

		Serial.println("del:");
		configuration.deleteValueConfigFile("SSID", "ghij");
		Serial.println("afficher del:");
		configuration.readConfigFile();
		Serial.println("Je cherche 2");
		String reponse = configuration.readValueConfigFile("NUM",2);
		Serial.println(reponse);
		configuration.deleteKeyConfigFile("SSID");
		Serial.println("lecture fichier ssid supprime:");
		configuration.readConfigFile();

		configuration.deleteKeyConfigFile("PWD");

		Serial.println("lecture fichier sans PWD:");
		configuration.readConfigFile();*/
		
	}
	SPIFFS.end();

	if (ota_ok)
		connect.modeOta();
}
void loop()
{
	ArduinoOTA.handle();
	server.handleClient();

		

}
