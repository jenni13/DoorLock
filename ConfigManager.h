// ConfigManager.h

#ifndef _CONFIGMANAGER_h
#define _CONFIGMANAGER_h

#include <FS.h>

class ConfigManagerClass
{
protected:
	File filename;

public:
	//void init();
	String readConfigFile();
	size_t getSize(File);
	bool isEmpty(File);
	void writeConfigFile(char*);
};

	//extern ConfigManagerClass ConfigManager;

#endif

