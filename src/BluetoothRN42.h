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
private:
	int status_pin;
  bool inCommand = false;

  void enterCommand();
  void exitCommand();

public:
  BluetoothRN42(int new_rx_pin, int new_tx_pin,
                int new_status_pin, int new_mode = 0,
                const char *new_name = NULL,
                const char *new_pin = NULL) :
    Bluetooth(new_rx_pin, new_tx_pin, new_mode, new_name, new_pin) {
    status_pin = new_status_pin;

  }

  int setMode(int new_mode);
  int setPin(const char *new_pin);
  int setName(const char *new_name);
  int setCod(const char *new_cod);

  bool isConnected();

  void setup();
};
#endif

