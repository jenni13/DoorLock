
#include "ConfigManager.h"


String ConfigManagerClass::readConfigFile() // reading all the file if it exists
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

String ConfigManagerClass::readValueConfigFile(String key, int numero ) // read value from key and index
{
	std::map<String, int> map = getIndex();
	File configFile = SPIFFS.open(FILENAME, "r+");
	if (!configFile)
	{
		Serial.println("le chargement du fichier de configuration a échoué");

	}
	String s,res,reponse;

	/*conversion*/
	
	int precedent = numero - 1;
	String m = String(precedent,DEC);

	
	if (numero == 0 || numero > map.at(key) )
	{
		reponse = "Mauvais index";
		Serial.println(reponse);
		return reponse;
	}

	while (configFile.available())
	{
		s = configFile.readStringUntil('\n');
		res = s.substring(0, s.indexOf(':'));
		
		if (res == key)
		{
			if (numero != 1)
			{
				res = s.substring(s.indexOf(m), s.indexOf(numero));
				reponse = res.substring(res.indexOf(':') + 1, res.indexOf('.'));
				Serial.println(reponse);			
			}
			else
			{
				res = s.substring(0, s.indexOf('.'));
				reponse = res.substring(res.indexOf(':') + 1, res.indexOf('.'));
				Serial.println(reponse);
			}
		}
	}

	configFile.close();
	return reponse;

}

void ConfigManagerClass::writeConfigFile(String key, String value) // isert un new key:value or a new value
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

void ConfigManagerClass::deleteKeyConfigFile(String key) // erase key 
{
	String s="", res,newFile="";
	std::map<String, int>::iterator it;
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
			if (res != key)
			{
				newFile += s+ "\n";
			}
			else
				newFile = newFile;
		}
		
		configFile.close();
		for(it = index.begin(); it != index.end(); ++it)
			if(it->first == key)
				index.erase(it);

		configFile = SPIFFS.open(FILENAME, "w");
		configFile.println(newFile);
		
		configFile.close();

		
	}
	else
	{
		Serial.println("la cle que vous voulez supprime n existe pas ");
	}
}

size_t ConfigManagerClass::getSize(File filename)
{
	size_t size = filename.size();

	return size;
}


bool ConfigManagerClass::itExist() // test if the file exist in spiffs
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

bool  ConfigManagerClass::keyExist(String key) // test if a key is in the index map
{
	for (std::map<String, int>::iterator it = index.begin(); it != index.end(); ++it)
	{
		if (it->first == key)
		{
			return true;
		}
	}
	return false;
}



void ConfigManagerClass::formatConfigFile() //delete the file
{
	SPIFFS.format();
	Serial.println("le fichier a ete formate");
}

std::map<String, int> ConfigManagerClass::getIndex()
{
	return index;
}

