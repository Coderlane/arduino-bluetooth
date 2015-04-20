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
  const char *cod;
  const char *name;
  const char *pin;

  int mode;

  virtual int setMode(int new_mode) {
    mode = new_mode;
    return 0;
  }

  virtual int setCod(const char *new_cod) {
    cod = new_cod;
    return 0;
  }

  virtual int setName(const char *new_name) {
    name = new_name;
    return 0;
  }

  virtual	int setPin(const char *new_pin) {
    pin = new_pin;
    return 0;
  }

public:
  Bluetooth(int new_rx_pin, int new_tx_pin,
            int new_mode = 0,
            const char *new_name = NULL,
            const char *new_pin = NULL,
            const char *new_cod = NULL)
    : SoftwareSerial(new_rx_pin, new_tx_pin) {

    name = new_name;
    pin = new_pin;
    mode = new_mode;
    cod = new_cod;
  }

  virtual void setup() = 0;
	virtual bool isConnected() = 0;

  const char *getName() {
    return name;
  }

  const char *getPin() {
    return pin;
  }

  int getMode() {
    return mode;
  }
};

#endif /* ARDUINO_BLUETOOTH_H */
