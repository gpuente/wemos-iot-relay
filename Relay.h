#ifndef Relay_h
#define Relay_h

#include "Arduino.h"
#include "RelayObject.h"
#include "ArduinoJson.h"

class Relay {
  private:
    relayObject _state;
    void commit();

  public:
    Relay(int pin);
    Relay(int pin, String alias);
    Relay(int pin, bool status);
    Relay(int pin, int id, String alias);
    Relay(int pin, String alias, bool status);
    Relay(int pin, String alias, bool status, bool enabled);
    Relay(int pin, int id, String alias, bool status, bool enabled);
    String toString();
    relayObject swap();
    relayObject getState();
    relayObject setStatus(bool status);
    relayObject setEnabled(bool enabled);
    relayObject setPin(int pin);
    relayObject setAlias(String alias);
    JsonObject& toJson();
};

#endif
