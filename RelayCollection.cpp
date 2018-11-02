#include "Arduino.h"
#include "Relay.h"
#include "RelayCollection.h"

RelayCollection::RelayCollection(Relay *collection) {
	_collection = collection;
}

Relay& RelayCollection::getByIndex(int index) {
  return _collection[index];
}

/*
 * Find Relay inside array by id.
 * Return index (int). if Relay is not found, return -1
 */
int RelayCollection::getIndexById(int id) {
  int index = -1;
  int arrayLength = sizeof(_collection);

  for (int i = 0; i < arrayLength; i++) {
    if (_collection[i].getState().id == id) {
      index = i;
      break;
    }
  }

  return index;
}

bool RelayCollection::hasIndex(int index) {
  if (index < 0) {
    return false;
  }

  return index < sizeof(_collection) ? true : false;
}

