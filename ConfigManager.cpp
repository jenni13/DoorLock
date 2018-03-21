
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
	bool ok = false;
	/*conversion*/
	
	int precedent = numero-1;
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
		s = s.substring(s.indexOf(':') + 1, s.length());
		if (res == key)
		{
			if (numero != 1)
			{
				while (ok != true)
				{

					res = s.substring(s.indexOf('.') + 1, s.indexOf(':'));

					if (res == m)
					{
						s = s.substring(s.indexOf(':')+1, s.length());
						reponse = s.substring(0, s.indexOf('.'));
						ok = true;
					}
					else
					{
						s = s.substring(s.indexOf(':')+1, s.length());
					}
				}
			}
			else
			{
				res = s.substring(0, s.indexOf('.'));
				reponse = res.substring(res.indexOf(':') + 1, res.indexOf('.'));
			}
		}
	}

	configFile.close();
	return reponse;

}

void ConfigManagerClass::writeConfigFile(String key, String value) // insert un new key:value or a new value
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
				configFile.print(":"+value + "." + index.at(key) + "\n" + res);

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
			configFile.print(key + ":"+ value + "." + index.at(key) + ":");
			index[key] = index[key] + 1;
			configFile.close();

		}
		else
		{
			configFile.println();
			configFile.print(key + ":" + value + "." + index.at(key) + ":");
			index[key] = index[key] + 1;
			configFile.close();

		}


	}
}


void ConfigManagerClass::deleteKeyConfigFile(String key) // erase key and all values of this key 
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
			if (res != key)
			{
				newFile += s+ '\n';
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

void ConfigManagerClass::deleteValueConfigFile(String key, String value) // erase a value  
{
	String s,res,newFile,val;
	std::vector <String> split;
	int indice = 1;
	bool erase_ok = false;

	File configFile = SPIFFS.open(FILENAME, "r+");
	if (!configFile)
	{
		Serial.println("le chargement du fichier de configuration a echoue write");
	}

	while (configFile.available())
	{
		s = configFile.readStringUntil('\n');
	
		Serial.println(s);
		res = s.substring(0, s.indexOf(":"));
		if (res == key)
		{
			newFile += res;
			s = s.substring(s.indexOf(":")+1, s.length());

			while (split.size() != index.at(key)-1)
			{
				val = s.substring(0, s.indexOf("."));
				split.push_back(val);
				s = s.substring(s.indexOf(":")+1, s.length());

			}
			for (std::vector<String>::iterator it = split.begin(); it != split.end(); ++it)
			{
				if (*it != value)
				{
					newFile += ":" + *it + "." + indice;
					indice++;
				}
				else
					erase_ok = true;
			}
			newFile += "\n";
		}
		else
		{
			newFile += s + "\n";
		}

	}
	configFile.close();
	if (!erase_ok)
		Serial.println("la cle en entrée n existe pas, rien n a donc ete supprime");

	index[key] = indice;
	configFile = SPIFFS.open(FILENAME, "w");
	configFile.println(newFile);

	configFile.close();

}

size_t ConfigManagerClass::getSize(File filename)
{
	size_t size = filename.size();

	return size;
}


bool ConfigManagerClass::itExist() // test if the file exist in spiffs
{
	if (SPIFFS.exists(FILENAME))
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

