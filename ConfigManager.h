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
	String readValueConfigFile(String , String);
	size_t getSize(File);
	void writeConfigFile(String key, String value);
	bool itExist();
	bool keyExist(String);
	void eraseKeyValue(String);
	void formatConfigFile();
	std::map<String, int> getIndex();


};

	//extern ConfigManagerClass ConfigManager;

#endif

