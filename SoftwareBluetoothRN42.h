
#ifndef SOFTWARE_BLUETOOTHRN42_H
#define SOFTWARE_BLUETOOTHRN42_H

#include "BluetoothRN42.h"
#include "SoftwareBluetooth.h"

class SoftwareBluetoothRN42 : BluetoothRN42
{
private:
  SoftwareBluetoothIO swIO;

public:
  SoftwareBluetoothRN42(SoftwareSerial &new_serial,
                        int new_status_pin, int new_mode = 0,
                        const char *new_name = NULL,
                        const char *new_pin = NULL) :
    BluetoothRN42(new_status_pin, new_mode, new_name, new_pin) {
    swIO.initSerial(new_serial);
    initIO(swIO);
  }
};

#endif 
