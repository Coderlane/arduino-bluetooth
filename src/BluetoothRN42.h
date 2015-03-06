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

public:
  BluetoothRN42(int new_mode = 0,
                const char *new_name = NULL,
                const char *new_pin = NULL) :
    Bluetooth(new_mode, new_name, new_pin) {}

  void Setup();
  void Send(char *data, int len);
  void Recv(char *data, int len);
};

#endif

