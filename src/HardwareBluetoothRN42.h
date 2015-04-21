
#ifndef HARDWARE_BLUETOOTHRN42_H
#define HARDWARE_BLUETOOTHRN42_H

#include "BluetoothRN42.h"
#include "HardwareBluetooth.h"

class HardwareBluetoothRN42 : public BluetoothRN42
{
  HardwareBluetoothIO hwIO;

public:
  HardwareBluetoothRN42(HardwareSerial &new_serial,
                        int new_status_pin, int new_mode = 0,
                        const char *new_name = NULL,
                        const char *new_pin = NULL) :
    BluetoothRN42(new_status_pin, new_mode, new_name, new_pin) {
    hwIO.initSerial(new_serial);
    initIO(hwIO);
  }
};

#endif 
