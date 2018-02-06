// ConfigManager.h

#ifndef _CONFIGMANAGER_h
#define _CONFIGMANAGER_h

#include <FS.h>

#define FILENAME "/configuration.cfg"

class ConfigManagerClass
{
protected:
	const char* filename;
	
public:

	String readConfigFile();
	size_t getSize(File);
	bool isEmpty(File);
	void writeConfigFile(char*);
	bool itExist(const char*);
};

	//extern ConfigManagerClass ConfigManager;

#endif

