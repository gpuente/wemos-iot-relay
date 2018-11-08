#ifndef WifiCredentials_h
#define WifiCredentials_h

#include "Arduino.h"

struct wifiCredentials {
  char ssid[32];
  char password[64];
};

typedef struct wifiCredentials wifiCredentials;

#endif