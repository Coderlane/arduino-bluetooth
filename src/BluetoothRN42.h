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

  BluetoothRN42(const char *new_name = "",
                const char *new_pin = "",
                int new_mode = 0) :
    Bluetooth(new_name, new_pin, new_mode) {}

  void Setup();
  void Send(char *data, int len) = 0;
  void Recv(char *data, int len) = 0;
};

#endif

