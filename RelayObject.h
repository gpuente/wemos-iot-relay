#ifndef RelayObject_h
#define RelayObject_h

#include "Arduino.h"

struct relayObject {
  int pin;
  int id;
  char *alias;
  bool status;
  bool enabled;
};

typedef struct relayObject relayObject;

#endif
