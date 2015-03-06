/**
 * @file Bluetooth.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef ARDUINO_BLUETOOTH_H
#define ARDUINO_BLUETOOTH_H

#include <Stream.h>
#include <SoftwareSerial.h>

class Bluetooth : public SoftwareSerial
{
protected:
  const char *name;
  const char *pin;

  int mode;

public:
  Bluetooth(int new_rx_pin, int new_tx_pin,
            int new_mode = 0,
            const char *new_name = NULL,
            const char *new_pin = NULL)
    : SoftwareSerial(new_rx_pin, new_tx_pin) {

    name = new_name;
    pin = new_pin;
    mode = new_mode;
  }

  virtual void Setup() = 0;
};

#endif /* ARDUINO_BLUETOOTH_H */
