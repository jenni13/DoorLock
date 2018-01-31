
#include "ConfigManager.h"

/*void ConfigManagerClass::init()
{

}*/

bool ConfigManagerClass::readConfigFile() // loading file if it exists
{
	File configFile = SPIFFS.open("/configuration.txt", "r");
	if (!configFile)
	{
		Serial.println("le chargement du fichier de configuration a échoué");
		return false;
	}
	String s = configFile.readString();
	Serial.println(s);

	configFile.close();
}

size_t ConfigManagerClass::getSize(File filename)
{
	size_t size = filename.size();

	return size;
}

bool ConfigManagerClass::isEmpty(File filename)
{
	if (filename.size() == 0)
		return true;
	else
		return false;
}

void ConfigManagerClass::writeConfigFile()
{
	File configFile = SPIFFS.open("/configuration.txt", "w");
	configFile.printf("ok ajoute");
	configFile.close();

}



//ConfigManagerClass ConfigManager;
