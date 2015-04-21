/**
 * @file BluetoothRN42.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef ARDUINO_BLUETOOTHRN42_H
#define ARDUINO_BLUETOOTHRN42_H

#include "Bluetooth.h"

class BluetoothRN42 : public Bluetooth
{
protected:
  int status_pin;
  bool inCommand;

  void enterCommand();
  void exitCommand();

public:
  BluetoothRN42(int new_status_pin, int new_mode = 0,
                const char *new_name = NULL,
                const char *new_pin = NULL) :
    Bluetooth(new_mode, new_name, new_pin) {
    status_pin = new_status_pin;
    inCommand = false;
  }

  int setMode(int new_mode);
  int setPin(const char *new_pin);
  int setName(const char *new_name);
  int setCod(const char *new_cod);

  virtual bool isConnected();
  virtual void setup();
};

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

#endif /* ARDUINO_BLUETOOTHRN42_H */
