
#include "ConfigManager.h"


String ConfigManagerClass::readConfigFile() // loading file if it exists
{
	
	File configFile = SPIFFS.open(FILENAME, "r");
	String s;
	if (!configFile)
	{
		Serial.println("le chargement du fichier de configuration a échoué");

	}
	while (configFile.available())
	{
		s = configFile.readString();
		
		Serial.println(s);
	}
	configFile.close();

	return s;
}

size_t ConfigManagerClass::getSize(File filename)
{
	size_t size = filename.size();

	return size;
}



/*void ConfigManagerClass::writeConfigFile(char* modification )
{
	
	File configFile = SPIFFS.open(this->filename, "w");
	configFile.printf(modification);
	configFile.close();
	
}*/
void ConfigManagerClass::writeConfigFile(String key, String value)
{
	String s,res;
	if (keyExist(key))
	{
		File configFile = SPIFFS.open(FILENAME, "r+");
		if (!configFile)
		{
			Serial.println("le chargement du fichier de configuration a echoue write");
		}

		while (configFile.available())
		{
			s = configFile.readStringUntil('\n');
			res = s.substring(0, s.indexOf(':'));
			int position = configFile.position();
				if (res == key)
				{
					
					res = configFile.readString();
					configFile.seek(position-1, SeekSet);
					configFile.print(value + '.' + index.at(key) + ':'+ '\n' + res);
					index[key] = index[key] + 1;
				
				}
		}
		configFile.close();
		
	}
	else
	{
		index[key] = 1;
		File configFile = SPIFFS.open(FILENAME, "a");
		if (!configFile)
		{
			Serial.println("le chargement du fichier de configuration a echoue write");

		}
		if (configFile.size() == 0)
		{
			configFile.println(key + ":"+ value + '.' + index.at(key) + ':');

			index[key] = index[key] + 1;
			configFile.close();

		}
		else
		{
			configFile.println();
			configFile.println(key + ":" + value + '.' + index.at(key) + ':');

			index[key] = index[key] + 1;
			configFile.close();
		}

	}
}

bool ConfigManagerClass::itExist()
{
	if (SPIFFS.exists(FILENAME)== true)
	{
		Serial.println("il existe");
		return true;
	}
	else
	{
		Serial.println("il n'existe pas");
		return false;
	}

}

bool  ConfigManagerClass::keyExist(String key)
{
	for (std::map<String, int>::iterator it = index.begin(); it != index.end(); ++it)
	{
		if (it->first == key)
		{
			Serial.println("trouve");
			return true;
		}
		
	}
	Serial.println("pas trouve");
	return false;
}

void ConfigManagerClass::eraseKeyValue(String key)
{
	String s;
	int position = this->keyExist(key);
	
	if (position == -1)
	{
		Serial.println("Clé ou fichier introuvable ");
	}
	else
	{
		File configFile = SPIFFS.open(FILENAME, "w");
		configFile.seek(position, SeekSet);
		s = configFile.readString();
		s.remove(position);
		configFile.close();

	}
}

void ConfigManagerClass::formatConfigFile() //erase all the file
{
	
	SPIFFS.format();
	Serial.println("le fichier a ete formate");
}

