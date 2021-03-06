/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "Relay.h"
#include "RelayCollection.h"
#include "WifiCredentials.h"

/* Default credentials for wemos AP */
const char *ssid = "wemos-iot-relay";
const char *password = "iotpassword";


char ssidClient[32];
char passwordClient[64];
bool providedCredentials = false;
wifiCredentials credentials;


ESP8266WebServer server(80);

/* Default relays available */
Relay relays[] = {
	Relay(16, 1, "Undefined"),
	Relay(5, 2, "Pin 5 -> D1"),
	Relay(4, 3, "Undefined"),
	Relay(0, 4, "Undefined")
};

RelayCollection relayCollection(relays);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

void setup() {
	delay(1000);
  	EEPROM.begin(512);
	WiFi.mode(WIFI_AP_STA);
	
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);

	setupServer();
	server.begin();

	Serial.println("HTTP server started");
	Serial.println(relays[1].toString());
}

void loop() {
	server.handleClient();
}
