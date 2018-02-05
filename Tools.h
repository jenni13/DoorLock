#ifndef _TOOLS_h
#define _TOOLS_h

//libraries used

#include <FS.h> //SPIFFS

#include "Logger.h"
#include "CommandManager.h"
#include "ConfigManager.h"
#include "ConnectionManager.h"

bool config_is_defined = true;
bool ota_ok = true;


ConfigManagerClass configuration;
ConnectionManagerClass connect;
//CommandManagerClass CommandManager;
#endif
