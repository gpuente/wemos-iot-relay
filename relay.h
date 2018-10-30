#include <Arduino.h>

#ifndef Relay_h
#define Relay_h

typedef struct {
    int pin;
    int id;
    String alias;
    bool status;
    bool enabled;
} relayObject;

class Relay {
    private:
        relayObject _state;
        void commit();

    public:
        Relay(int pin);
        Relay(int pin, String alias);
        Relay(int pin, bool status);
        Relay(int pin, String alias, bool status);
        Relay(int pin, String alias, bool status, bool enabled);
        Relay(int pin, int id, String alias, bool status, bool enabled);
        String toString();
        relayObject swap();
        relayObject getState();
        relayObject setStatus(bool status);
        relayObject setEnabled(bool enabled);
};

Relay::Relay(int pin) {
    _state.pin = pin;
    _state.id = pin;
    _state.alias = "";
    _state.status = false;
    _state.enabled = true;
    pinMode(pin, OUTPUT);
    commit();
}

Relay::Relay(int pin, String alias) {
    _state.pin = pin;
    _state.id = pin;
    _state.alias = alias;
    _state.status = false;
    _state.enabled = true;
    pinMode(pin, OUTPUT);
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

Relay::Relay(int pin, String alias, bool status) {
    _state.pin = pin;
    _state.id = pin;
    _state.alias = alias;
    _state.status = status;
    _state.enabled = true;
    pinMode(pin, OUTPUT);
    commit();
}

Relay::Relay(int pin, String alias, bool status, bool enabled) {
    _state.pin = pin;
    _state.id = pin;
    _state.alias = alias;
    _state.status = status;
    _state.enabled = enabled;
    pinMode(pin, OUTPUT);
    commit();
}

Relay::Relay(int pin, int id, String alias, bool status, bool enabled) {
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
    result = ", id: " + String(_state.id);
    result = ", alias: " + _state.alias;
    result = ", status: " + String(_state.status);
    result = ", enabled: " + String(_state.enabled);
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

#endif