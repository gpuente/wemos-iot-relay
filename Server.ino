void setupServer() {
	server.on("/", HTTP_GET, handleRoot);
	server.on("/connect", HTTP_POST, handleConnect);
  server.on("/scannetworks", HTTP_POST, scanWifiNetworks);
	server.on("/api/v1/relay", HTTP_GET, getRelay);
	server.on("/api/v1/relays", HTTP_GET, getRelays);
	server.on("/api/v1/relay", HTTP_PUT, updateRelay);
  server.on("/api/v1/relay/switch", HTTP_PUT, switchRelay);
	server.on("/api/v1/relay", HTTP_DELETE, deleteRelay);
	server.on("/api/v1/relay", HTTP_POST, createRelay);
}







void handleRoot() {
	server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"><style>.btn,form,select{width:100%}body{background:#f5f6fa;color:#9c9c9c;font:1rem \"PT Sans\",sans-serif;margin:10px 20px}h1{font-size:1.5em}input{display:block;margin:0 auto}form{max-width:380px;display:inline-block}.form-container{text-align:center}input[type=password],input[type=text]{background:#fff;color:#a3a3a3;font:inherit;box-shadow:0 6px 10px 0 rgba(0,0,0,.1);border:0;outline:0;padding:12px 18px;width:100%;margin:20px 0;box-sizing:border-box;border-radius:4px}input[type=text]{margin-bottom:0}select{color:#a3a3a3;font-size:17px;margin-top:20px;padding:12px 18px;border:0!important;-webkit-appearance:none;-moz-appearance:none;appearance:none;box-shadow:0 6px 10px 0 rgba(0,0,0,.1);background:url(\"data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='100' height='100' fill='%238C98F2'><polygon points='0,0 100,0 50,50'/></svg>\") no-repeat #fff;background-size:12px;background-position:calc(100% - 20px) center}select[disabled]{background-color:#eaeaea}.btn{display:block;background:0 0;color:inherit;font:inherit;border:0;outline:0;padding:0;transition:all .2s ease-in;cursor:pointer}.btn-primary{background:#7f8ff4;color:#fff;box-shadow:0 0 10px 2px rgba(0,0,0,.1);border-radius:2px;padding:12px 36px}.btn-primary:hover{background:#6c7ff2}.btn-primary:active{background:#7f8ff4;box-shadow:inset 0 0 10px 2px rgba(0,0,0,.2)}#refresh-section{padding-top:5px;text-align:left;height:20px}.hide{display:none}.right{float:right}.left{float:left}</style><title>Config Wemos IoT Relay</title></head><body><div class=\"form-container\"><h1>Connect to Wifi Network</h1><p>Please provide wifi credentials to connect your wemos-iot-relay to network</p><form action=\"/connect\" method=\"POST\"><input type=\"text\" name=\"ssid\" id=\"ssidText\" placeholder=\"SSID\" class=\"hide\"> <select name=\"ssid\" id=\"ssidSelect\"><option value=\"\" disabled=\"disabled\" selected=\"selected\">Select a WiFi network</option></select><div id=\"refresh-section\"><a id=\"refreshButton\" href=\"#\" class=\"left\">refresh</a> <span id=\"loadingLabel\" class=\"left hide\">loading data...</span> <a id=\"backButton\" href=\"#\" class=\"right hide\">back</a> <a id=\"changeInput\" href=\"#\" class=\"right\">or write manually</a></div><input type=\"password\" name=\"password\" id=\"password\" placeholder=\"Password\"> <input type=\"button\" value=\"Connect\" class=\"btn btn-primary\" onclick=\"submitForm(this.form)\"></form></div></body><script>var manuallySearch=!1,refreshButton=document.getElementById(\"refreshButton\"),backButton=document.getElementById(\"backButton\"),ssidText=document.getElementById(\"ssidText\"),ssidSelect=document.getElementById(\"ssidSelect\"),password=document.getElementById(\"password\"),changeInput=document.getElementById(\"changeInput\"),loadingLabel=document.getElementById(\"loadingLabel\"),networks=null,endpoint=\"http://\"+location.host+\"/scannetworks\",xhr=new XMLHttpRequest;function cleanSelectoptions(){for(var e=0;e<ssidSelect.length;e++)ssidSelect.remove(1)}function enableSelect(){ssidSelect.removeAttribute(\"disabled\"),loadingLabel.classList.add(\"hide\"),refreshButton.classList.remove(\"hide\"),changeInput.classList.remove(\"hide\")}function disableSelect(){ssidSelect.setAttribute(\"disabled\",\"disabled\"),loadingLabel.classList.remove(\"hide\"),refreshButton.classList.add(\"hide\"),changeInput.classList.add(\"hide\")}function printOptions(){networks.data.forEach(function(e){var t=document.createElement(\"option\");t.text=e.ssid,t.value=e.ssid,ssidSelect.appendChild(t)})}function submitForm(e){console.log(\"submit!\");var t=new XMLHttpRequest;t.onload=function(){200<=t.status&&t.status<300?(console.log(\"success!\"),console.log(t)):console.log(\"error\")},t.onerror=function(){console.log(\"error\")},t.open(\"POST\",\"/connect\"),t.setRequestHeader(\"Content-Type\",\"application/json;charset=UTF-8\"),t.timeout=15e3,t.send(JSON.stringify({ssid:manuallySearch?ssidText.value:ssidSelect.value,password:password.value}))}xhr.onload=function(){200<=xhr.status&&xhr.status<300?(console.log(\"success!\"),networks=JSON.parse(xhr.responseText),printOptions(),enableSelect(),console.log(networks)):(enableSelect(),console.log(\"error\"))},xhr.onerror=function(){console.log(\"error\"),enableSelect()},refreshButton.onclick=function(){console.log(\"refresh networks\"),disableSelect(),cleanSelectoptions(),xhr.timeout=5e3,xhr.open(\"POST\",endpoint),xhr.send()},changeInput.onclick=function(){backButton.classList.remove(\"hide\"),refreshButton.classList.add(\"hide\"),ssidText.classList.remove(\"hide\"),ssidSelect.classList.add(\"hide\"),changeInput.classList.add(\"hide\"),manuallySearch=!0},backButton.onclick=function(){backButton.classList.add(\"hide\"),refreshButton.classList.remove(\"hide\"),ssidText.classList.add(\"hide\"),ssidSelect.classList.remove(\"hide\"),changeInput.classList.remove(\"hide\"),manuallySearch=!1};</script></html>");
}







void handleConnect() {
  /*
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
*/
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

  if (!root.containsKey("ssid")) {
    handleError(404, "ssid not provided");
    return;
  }

  if (!root.containsKey("password")) {
    handleError(404, "password not provided");
    return;
  }

  String ssid = root["ssid"];
  String password = root["password"];

  Serial.println(ssid);
  Serial.println(password);

  ssid.toCharArray(ssidClient, 32);
  password.toCharArray(passwordClient, 64);

  connectToAP();
  
  server.send(200, "application/json", "{ \"status\": \"ok\" }");
}






void scanWifiNetworks() {
  Serial.println("Scanning networks");
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  StaticJsonBuffer<2200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& data = root.createNestedArray("data");

  if (n > 0) {
    int limit = (n > 15) ? 15 : n;
    
    for (int i = 0; i < limit; i++) {
      JsonObject& object = data.createNestedObject();
      object["index"] = i;
      object["ssid"] = WiFi.SSID(i);
      object["rssi"] = WiFi.RSSI(i);
      object["encryption"] = WiFi.encryptionType(i) == ENC_TYPE_NONE ? "none" : "*";
    }
  }
  
  char json[5000];
  root.printTo(json);

  server.send(200, "application/json", json);
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

  //server.send(200, "text/html", "<h1>Connected! IP: " + WiFi.localIP().toString() + "</h1>");
}






/*
 * Send json of Relay by ID
 * 
 * use: http://host/api/v1/relay?id=1
 * method: GET
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
  Relay& relay = relayCollection.getByIndex(index);
  relay.toJson().printTo(json);

  Serial.println(relay.toString());
 
  server.send(200, "application/json", json);
}






/*
 * Return a json Array with all relays objects available.
 * 
 * use: http://host/api/v1/relays
 * method: GET
 */
void getRelays() {
  Relay*& collection = relayCollection.getCollection();
  Serial.println(collection[1].toString());

  int arrayLength = sizeof(collection);
  String response = "{\"data\":[";
  
  for (int i = 0; i < arrayLength; i++) {
    JsonObject& json = collection[i].toJson();
    char value[120];
    json.printTo(value);
    response = response + String(value);
 
    if (i < (arrayLength - 1)) {
      response = response + ",";
    }
  }

  response = response + "]}";
  
  server.send(200, "application/json", response);
}







/*
 * Update a relay by ID
 * This method gets an json object from request, encode and set 
 * parameters requested by client.
 * On error, method response with error response.
 * 
 * use: http://host/api/v1/relay
 * method: PUT
 * params: { "id": 1, "status": true, "alias": "some text", "enabled": true }
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

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  
  if (root.containsKey("status")) {
    bool status = root["status"];
    relay.setStatus(status);
  }

 
  if (root.containsKey("alias")) {
    String alias = root["alias"];
    relay.setAlias(alias);
  }

  
  if (root.containsKey("enabled")) {
    bool enabled = root["enabled"];
    relay.setEnabled(enabled);
  }

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}







/*
 * Change the enabled property of a relay to false
 * If property enable of a relay is false, the relay can't turn on
 * 
 * use: http://host/api/v1/relay?id=1
 * method: DELETE
 */
void deleteRelay() {
  if (server.arg("id") == "") {
    handleError(404, "id not provided");
    return;
  }

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  relay.setEnabled(false);

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}





/*
 * Switch status of a relay
 * 
 * use: http://host/api/v1/relay/switch?id=1
 * method: PUT
 */
void switchRelay() {
  if (server.arg("id") == "") {
    handleError(404, "id not provided");
    return;
  }

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  relay.swap();

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
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






/*
 * Set enabled true to a relay available
 * 
 * use: http://host/api/v1/relay
 * method: POST
 * params: { "id": 1, "alias": "some text" }
 */
void createRelay() {
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

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
 
  if (root.containsKey("alias")) {
    String alias = root["alias"];
    relay.setAlias(alias);
  }

  relay.setEnabled(true);
  relay.setStatus(false);

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}
