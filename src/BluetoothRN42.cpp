
#include <cstdlib>

#include "BluetoothRN42.h"

extern int delay(int);

void BluetoothRN42::Setup()
{
  //this->Begin(115200);

  // Start by printing w/o CR.
  this->print("$$$");

  delay(100);

  this->print("SM,");
  this->println(mode);

  if(name != NULL) {
  this->print("SN,");
    this->println(name);
  }

  if(pin != NULL) {
  this->print("SP,");
    this->println(pin);
  }

  this->println("---");
}
