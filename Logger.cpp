// Logging class redirecting to serial port with log level

#include "Logger.h"

// Verbose log with char* input
void LoggerClass::Log(char * logMessage)
{
	Log(*logMessage, true);
}

void LoggerClass::Log(char * logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG == 2
	Output(logMessage);
	if (cr)
		linefeed();
#elif defined(ARDUINO) && ACTIVELOG == 3
	
	toFile(logMessage);
	if (cr)
		linefeed();
#endif
}

// Verbose log with char input
void LoggerClass::Log(char logMessage)
{
	Log(logMessage, true);
}

void LoggerClass::Log(char logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG == 2
	Output(&logMessage);
	if (cr)
		linefeed();
#elif defined(ARDUINO) && ACTIVELOG == 3
	Output(F("toFile"));
	toFile(logMessage);
	if (cr)
		linefeed();
#endif
}

// Verbose log with String input
void LoggerClass::Log(String logMessage)
{
	Log(logMessage, true);

}

void LoggerClass::Log(String logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG == 2
	Output(logMessage);
	if (cr)
		linefeed();
#elif defined(ARDUINO) && ACTIVELOG == 3
	toFile(logMessage);
	if (cr)
		linefeed();
#endif
}


// Error log with char* input
void LoggerClass::Error(char * logMessage)
{
	Error(*logMessage, true);
}

void LoggerClass::Error(char * logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG >= 1 
	Output(F("!!"));
	Output(logMessage);
	if (cr)
		linefeed();
#endif
}

// Error log with char input
void LoggerClass::Error(char logMessage)
{
	Error(logMessage, true);
	
}

void LoggerClass::Error(char logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG >= 1 
	Output(F("!!"));
	Output(&logMessage);
	if (cr)
		linefeed();
#endif
}

// Error log with String input
void LoggerClass::Error(String logMessage)
{
	Error(logMessage, true);
}

void LoggerClass::Error(String logMessage, bool cr)
{
#if defined(ARDUINO) && ACTIVELOG >= 1
	Output(F("!!"));
	Output(logMessage);
	if (cr)
		linefeed();
#endif
}

// Generic log output method
void LoggerClass::Output(char *  logMessage)
{
	Serial.print(logMessage);
	delay(10);
}

// Generic log output method
void LoggerClass::Output(String logMessage)
{
	Serial.print(logMessage);
	delay(10);
}

// Carriage return
void LoggerClass::linefeed()
{
	Serial.println();
	delay(10);
}

bool LoggerClass::IsLogging()
{
#if defined(ARDUINO) && ACTIVELOG >= 1
	return true;
#else
	return false;
#endif
}

void LoggerClass::toFile(String message)
{
	String s;
	int i = 0;
	File ferror = SPIFFS.open(FILEERROR, "a+");
	if (!ferror)
	{
		Serial.println("le chargement du fichier d erreur a echoue");
	}
	ferror.println(i+ '. ' + message);
	i++;
	ferror.println();
	ferror.close();

	
}

void LoggerClass::toFile(char* message)
{
	String s;
	int i = 0;
	File ferror = SPIFFS.open(FILEERROR, "a+");
	if (!ferror)
	{
		Serial.println("le chargement du fichier d erreur a echoue");
	}
	ferror.println(i + '. ' + message);
	i++;
	ferror.println();
	ferror.close();

}
void LoggerClass::toFile(char message)
{
	String s;
	int i=0;
	File ferror = SPIFFS.open(FILEERROR, "w");
	if (!ferror)
	{
		Serial.println("le chargement du fichier d erreur a echoue");
	}
	ferror.println(message);
	i++;
	ferror.println();
	ferror.close();

}

void LoggerClass::readFerror()
{
	String s;

	File ferror = SPIFFS.open(FILEERROR, "r");
	if (!ferror)
	{
		Serial.println("le chargement du fichier d'erreur a echoue");

	}
	while (ferror.available())
	{
		s = ferror.readString();	
	}
	Serial.println(s);
	ferror.close();
}

LoggerClass Logger;


