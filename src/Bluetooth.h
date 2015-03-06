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

class Bluetooth : public Stream
{
protected:
  friend class SoftwareSerial;

  const char *name;
  const char *pin;

  int rx_pin;
  int tx_pin;
  int mode;

  SoftwareSerial serial;

public:
  Bluetooth(int new_rx_pin, int new_tx_pin,
            int new_mode = 0,
            const char *new_name = NULL,
            const char *new_pin = NULL)
    : serial(new_rx_pin, new_tx_pin) {

    name = new_name;
    pin = new_pin;
    mode = new_mode;

    rx_pin = new_rx_pin;
    tx_pin = new_tx_pin;
  }

  virtual void Setup() = 0;

  int available() {
    return serial.available();
  }
  int read() {
    return serial.read();
  }
  int peek() {
    return serial.peek();
  }
  void flush() {
    serial.flush();
  }

  size_t write(uint8_t data) {
    return serial.write(data);
  }

  size_t write(const uint8_t *buffer, size_t size) {
    return serial.write(buffer, size);
  }
};

#endif /* ARDUINO_BLUETOOTH_H */
