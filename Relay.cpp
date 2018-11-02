#include "Arduino.h"
#include "Relay.h"
#include "ArduinoJson.h"

Relay::Relay(int pin) {
	_state.pin = pin;
	_state.id = pin;
	_state.alias = "";
	_state.status = false;
	_state.enabled = true;
	pinMode(pin, OUTPUT);
	commit();
}

Relay::Relay(int pin, char *alias) {
  _state.pin = pin;
  _state.id = pin;
  _state.alias = alias;
  _state.status = false;
  _state.enabled = true;
  pinMode(pin, OUTPUT);
  Serial.println(alias);
  char* text = alias;
  Serial.println(text);
  commit();
}

Relay::Relay(int pin, bool status) {
  _state.pin = pin;
  _state.id = pin;
  _state.alias = "";
  _state.status = status;
  _state.enabled = true;
  pinMode(pin, OUTPUT);
  commit();
}

Relay::Relay(int pin, int id, char *alias) {
  _state.pin = pin;
  _state.id = id;
  _state.alias = alias;
  _state.status = false;
  _state.enabled = true;
  pinMode(pin, OUTPUT);
  commit();
}

Relay::Relay(int pin, char *alias, bool status) {
  _state.pin = pin;
  _state.id = pin;
  _state.alias = alias;
  _state.status = status;
  _state.enabled = true;
  pinMode(pin, OUTPUT);
  commit();
}

Relay::Relay(int pin, char *alias, bool status, bool enabled) {
  _state.pin = pin;
  _state.id = pin;
  _state.alias = alias;
  _state.status = status;
  _state.enabled = enabled;
  pinMode(pin, OUTPUT);
  commit();
}

Relay::Relay(int pin, int id, char *alias, bool status, bool enabled) {
  _state.pin = pin;
  _state.id = id;
  _state.alias = alias;
  _state.status = status;
  _state.enabled = enabled;
  pinMode(pin, OUTPUT);
  commit();
}

void Relay::commit() {
  digitalWrite(_state.pin, _state.status);
}

String Relay::toString() {
  String result = "pin: " + String(_state.pin);
  result = result + ", id: " + String(_state.id);
  result = result + ", alias: " + String(_state.alias);
  result = result + ", status: " + String(_state.status);
  result = result + ", enabled: " + String(_state.enabled);
  return result;
}

relayObject Relay::swap() {
  _state.status = !_state.status;
  commit();
  return _state;
}

relayObject Relay::getState() {
  return _state;
}

relayObject Relay::setStatus(bool status) {
  _state.status = status;
  commit();
  return _state;
}

relayObject Relay::setEnabled(bool enabled) {
  _state.enabled = enabled;
  return _state;
}

relayObject Relay::setPin(int pin) {
  _state.pin = pin;
  return _state;
}

relayObject Relay::setAlias(char *alias) {
  _state.alias = alias;
  return _state;
}

JsonObject& Relay::toJson() {
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["pin"] = _state.pin;
  root["id"] = _state.id;
  root["alias"] = _state.alias;
  root["status"] = _state.status;
  root["enabled"] = _state.enabled;

  return root;
}

