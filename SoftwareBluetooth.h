
#ifndef SOFTWARE_BLUETOOTH_H
#define SOFTWARE_BLUETOOTH_H

#include "Bluetooth.h"
#include <SoftwareSerial.h>

class SoftwareBluetoothIO : public BluetoothIO
{
  SoftwareSerial *serial;
public:
  SoftwareBluetoothIO() {
    serial = NULL;
  }

  virtual void initSerial(SoftwareSerial &new_serial) {
    serial = &new_serial;
    BluetoothIO::initSerial((Stream &)new_serial);
  }

  virtual void begin(unsigned long baud) {
    serial->begin(baud);
  }
};

#endif
