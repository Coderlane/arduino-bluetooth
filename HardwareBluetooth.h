

#ifndef HARDWARE_BLUETOOTH_H
#define HARDWARE_BLUETOOTH_H

#include "Bluetooth.h"
#include <HardwareSerial.h>

class HardwareBluetoothIO : public BluetoothIO
{
private:
  HardwareSerial *serial;

public:
  HardwareBluetoothIO() {
    serial = NULL;
  }

  virtual void initSerial(HardwareSerial &new_serial) {
    serial = &new_serial;
    BluetoothIO::initSerial((Stream &)new_serial);
  }

  virtual void begin(unsigned long baud) {
    serial->begin(baud);
  }
};

#endif
