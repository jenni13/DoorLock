// ConfigManager.h

#ifndef _CONFIGMANAGER_h
#define _CONFIGMANAGER_h

#include <FS.h>
#include <map>


#define FILENAME "/configuration.cfg"



class ConfigManagerClass
{
protected:
	const char* filename;
	std::map<String, int> index;

public:

	String readConfigFile();
	size_t getSize(File);
	
	//void writeConfigFile(char*);
	void writeConfigFile(String key, String value);
	bool itExist();
	bool keyExist(String);
	void eraseKeyValue(String);
	void formatConfigFile();
};

	//extern ConfigManagerClass ConfigManager;

#endif

