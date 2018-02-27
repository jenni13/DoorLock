// 
// 
// 

#include "ConnectionManager.h"

const char *ssid_wifi = "SFR_6CD0";
const char *password_wifi = "fa4rselutockervolder";
const char *ssid = "DOORLOCK001";
const char *password = "password";  //at least 8 character long

void ConnectionManagerClass::modeAccessPoint()
{
	WiFi.mode(WIFI_AP); //only Access point. to do both -> (WiFi.mode(WIFI_AP_STA));
	WiFi.softAP(ssid, password);
	Serial.println();

	Serial.print("Server IP address: ");
	Serial.println(WiFi.softAPIP());

	Serial.print("Server MAC address: ");
	Serial.println(WiFi.softAPmacAddress());

}

void ConnectionManagerClass::modeAccessPointAndWifi()
{
	int event;
	int startMillis = millis();
	int currentMillis;
	WiFi.mode(WIFI_AP_STA);

	WiFi.begin(ssid_wifi, password_wifi);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
		currentMillis = millis();
		Serial.println(currentMillis - startMillis );
		if (currentMillis - startMillis > 30000)
		{
			Serial.println(this->checkStatus(event));
			break;
		}

	}
	//If connection successful show IP address in serial monitor and connect in AP mode too
	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.println("");
		Serial.print("Connected to ");
		Serial.println(ssid_wifi);
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());

		/*connection AP*/
		WiFi.softAP(ssid, password);
		Serial.println();

		Serial.print("Server IP address: ");
		Serial.println(WiFi.softAPIP());

		Serial.print("Server MAC address: ");
		Serial.println(WiFi.softAPmacAddress());
	}
	else /*probleme connection, connect in AP mode only*/
	{
		Serial.println("La connection wifi a echoue, connexion en mode AP uniquement en cours");
		this->modeAccessPoint();
	}

}

String ConnectionManagerClass::checkStatus(int event)
{
	String status;
	switch (event) {
	case WL_NO_SHIELD:
		status = "WiFi shield not present";
		return status ;

	case WL_NO_SSID_AVAIL:
		status = "No ssid available" ;
		return status;

	case WL_CONNECTED:
		status = "Connected";
		return status;

	case WL_CONNECT_FAILED:
		status = "Connection failed";
		return status;

	case WL_DISCONNECTED:
		status = "Disconnected";
		return status;

	case WL_CONNECTION_LOST:
		status = "Connection lost";
		return status;
	default:
		status = "something went wrong";
		return status;
	}
}

/*void ConnectionManagerClass::modeOta()
{
	ArduinoOTA.setHostname(HOSTNAME);
	ArduinoOTA.begin();
	Logger.Log(F("Ota Appearing Ok..."));
}*/

