void setupServer() {
	server.on("/", HTTP_GET, handleRoot);
	server.on("/connect", HTTP_POST, handleConnect);
	server.on("/on", HTTP_GET, handleOn);
	server.on("/off", HTTP_GET, handleOff);
	server.on("/api/v1/relay", HTTP_GET, getRelay);
	server.on("/api/v1/relays", HTTP_GET, getRelays);
	server.on("/api/v1/relay", HTTP_PUT, updateRelay);
	server.on("/api/v1/relay", HTTP_DELETE, deleteRelay);
	server.on("/api/v1/relay", HTTP_POST, createRelay);
}

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

void handleOn() {
	relays[1].setStatus(true);
	server.send(200, "text/html", "<h1>Relay: on</h1>");
}

void handleOff() {
	relays[1].setStatus(false);
	server.send(200, "text/html", "<h1>Relay: off</h1>");
}


/*
 * Send json of Relay by ID
 */
void getRelay() {
	if (server.arg("id") == "") {
		handleError(404, "id element not provided");
		return;
	}

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }
  
  char json[120];
  relayCollection.getByIndex(id).toJson().printTo(json);
 
  server.send(200, "application/json", json);
}

void getRelays() {

}


/*
 * Update a relay by ID
 * This method gets an json object from request, encode and set 
 * parameters requested by client.
 * On error, method response with error response.
 */
void updateRelay() {
  if (server.args() < 1) {
    handleError(404, "json object not provided");
    return;
  }

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg(0));

  if (!root.success()) {
    handleError(404, "parse json object failed");
    return;
  }

  if (!root.containsKey("id")) {
    handleError(404, "id not provided");
    return;
  }

  int id = root["id"];
  int index = relayCollection.getIndexById(id);

  if (index < 1) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  
  if (root.containsKey("status")) {
    bool status = root["status"];
    relay.setStatus(status);
  }

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}

void deleteRelay() {

}


/*
 * Send an error http response to client
 */
void handleError(int httpCode, String message) {
  StaticJsonBuffer<150> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["status"] = httpCode;
  root["message"] = message;

  char json[100];
  root.printTo(json);
  
	server.send(httpCode, "application/json", json);
}

void createRelay() {

}
