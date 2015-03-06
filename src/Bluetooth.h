/**
 * @file Bluetooth.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef ARDUINO_BLUETOOTH_H
#define ARDUINO_BLUETOOTH_H

#define NULL (void *)0

class Bluetooth
{
protected:
  const char *name;
  const char *pin;
  int mode;

public:
  Bluetooth(int new_mode = 0,
            const char *new_name = NULL,
            const char *new_pin = NULL) {
    name = new_name;
    pin = new_pin;
    mode = new_mode;
  }

  virtual void Setup() = 0;
  virtual void Send(char *data, int len) = 0;
  virtual void Recv(char *data, int len) = 0;
};

#endif /* ARDUINO_BLUETOOTH_H */
