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
		configuration.initIndex();
		String ssid_wifi = connect.selectSsid(configuration, 1);
		String pwd = connect.selectPwd(configuration, 1);
		connect.modeAccessPointAndWifi(ssid_wifi,pwd);

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
		/*configuration.writeConfigFile("SSID", "SFR_6CD0");
		configuration.writeConfigFile("PWD","4rseluckervolder"),
		configuration.writeConfigFile("NOM", "Jean");
		configuration.writeConfigFile("NUM", "04423");*/



		Serial.println("lecture fin:");
		configuration.readConfigFile();
		Serial.println("ssid");
		configuration.readValueConfigFile("SSID", 1);

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
