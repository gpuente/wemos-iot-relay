#ifndef RelayCollection_h
#define RelayCollection_h

#include "Arduino.h"
#include "Relay.h"

class RelayCollection {
  private:
    Relay *_collection;

  public:
    RelayCollection(Relay *collection);
    Relay& getByIndex(int index);
    Relay*& getCollection();
    int getIndexById(int id);
    bool hasIndex(int index);
};

#endif
