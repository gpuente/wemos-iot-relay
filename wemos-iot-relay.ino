/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "Relay.h"

/* Set these to your desired credentials. */
const char *ssid = "wemos-iot-relay";
const char *password = "iotpassword";
// const int RELAY = 5;

char ssidClient[32];
char passwordClient[64];
bool providedCredentials = false;

ESP8266WebServer server(80);
Relay relay(5);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"><title>Config Wemos IoT Relay</title><style>body{background:#f5f6fa;color:#9c9c9c;font:1rem \"PT Sans\", sans-serif;margin:10px 20px}h1{font-size:1.5em}input{display:block;margin:0 auto}form{width:100%;max-width:380px;display:inline-block}.form-container{text-align:center}input[type=\"password\"],input[type=\"text\"]{background:#fff;color:#a3a3a3;font:inherit;box-shadow:0 6px 10px 0 rgba(0, 0, 0, 0.1);border:0;outline:0;padding:12px 18px;width:100%;margin:20px 0;box-sizing:border-box}.btn{display:block;background:transparent;color:inherit;font:inherit;border:0;outline:0;padding:0;transition:all 200ms ease-in;cursor:pointer;width:100%}.btn-primary{background:#7f8ff4;color:#fff;box-shadow:0 0 10px 2px rgba(0, 0, 0, 0.1);border-radius:2px;padding:12px 36px}.btn-primary:hover{background:#6c7ff2}.btn-primary:active{background:#7f8ff4;box-shadow:inset 0 0 10px 2px rgba(0, 0, 0, 0.2)}</style></head><body><div class=\"form-container\"><h1>Connect to Wifi Network</h1><p>Please provide wifi credentials to connect your wemos-iot-relay to network</p><form action=\"/connect\" method=\"POST\"> <input type=\"text\" name=\"ssid\" class=\"inputText\" placeholder=\"SSID\"> <input type=\"password\" name=\"password\" class\"inputText\" placeholder=\"Password\"> <input type=\"submit\" value=\"Connect\" class=\"btn btn-primary\"></form></div></body></html>");
}

void handleConnect() {
  server.arg("ssid").toCharArray(ssidClient, 32);
  server.arg("password").toCharArray(passwordClient, 64);
  
  Serial.println();
  Serial.print("ssid: ");
  Serial.print(ssidClient);
  Serial.println();
  Serial.print("password: ");
  Serial.print(passwordClient);
  Serial.println();
  connectToAP();
  //server.send(200, "text/html", "<h1>Connected!</h1>");
}

void handleOn() {
  // digitalWrite(RELAY, HIGH);
  relay.setStatus(true);
  server.send(200, "text/html", "<h1>Relay: on</h1>");
}

void handleOff() {
  // digitalWrite(RELAY, LOW);
  relay.setStatus(false);
  server.send(200, "text/html", "<h1>Relay: off</h1>");
}

void connectToAP() {
  Serial.println("Connecting to: ");
  Serial.print(String(ssidClient));
  WiFi.begin(ssidClient, passwordClient);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.send(200, "text/html", "<h1>Connected! IP: " + WiFi.localIP().toString() + "</h1>");
}

void setup() {
	delay(1000);
  // pinMode(RELAY, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", HTTP_GET, handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);
	server.begin();
	Serial.println("HTTP server started");

  Serial.println(relay.toString());
}

void loop() {
	server.handleClient();
}
