#ifndef Relay_h
#define Relay_h

#include "Arduino.h"
#include "RelayObject.h"

class Relay {
    private:
        relayObject _state;
        void commit();

    public:
        Relay(int pin);
        Relay(int pin, char *alias);
        Relay(int pin, bool status);
        Relay(int pin, char *alias, bool status);
        Relay(int pin, char *alias, bool status, bool enabled);
        Relay(int pin, int id, char *alias, bool status, bool enabled);
        String toString();
        relayObject swap();
        relayObject getState();
        relayObject setStatus(bool status);
        relayObject setEnabled(bool enabled);
};

#endif