/**
 * @file Bluetooth.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef ARDUINO_BLUETOOTH_H
#define ARDUINO_BLUETOOTH_H

class Bluetooth
{
private:
  const char *name;
  const char *pin;
  int mode;

public:
  Bluetooth(const char *new_name = "",
            const char *new_pin = "",
            int new_mode = 0) {
    name = new_name;
    pin = new_pin;
    mode = new_mode;
  }

  virtual void Setup() = 0;
  virtual void Send(char *data, int len) = 0;
  virtual void Recv(char *data, int len) = 0;
};


#endif /* ARDUINO_BLUETOOTH_H */
