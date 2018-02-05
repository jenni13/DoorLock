
#include "ConfigManager.h"

/*void ConfigManagerClass::init()
{

}*/

String ConfigManagerClass::readConfigFile() // loading file if it exists
{
	File configFile = SPIFFS.open("/configuration.txt", "r");
	if (!configFile)
	{
		Serial.println("le chargement du fichier de configuration a échoué");
		//return false;
	}
	String s = configFile.readString();
	Serial.println(s);

	configFile.close();

	return s;
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

void ConfigManagerClass::writeConfigFile(char* modification )
{
	File configFile = SPIFFS.open("/configuration.txt", "w");
	configFile.printf(modification);
	configFile.close();

}


