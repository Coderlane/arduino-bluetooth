/**
 * @file Bluetooth.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Stream.h>

#define NULL 0

class BluetoothIO : public Stream
{
protected:
  Stream *stream;

  BluetoothIO() {
    stream = NULL;
  }

  virtual void initSerial(Stream &new_stream) {
    stream = &new_stream;
  }

public:
  virtual void begin(unsigned long baud) = 0;

  virtual int available() {
    return stream->available();
  }

  virtual int read() {
    return stream->read();
  }

  virtual int peek()  {
    return stream->peek();
  }

  virtual void flush()  {
    stream->flush();
  }

  virtual size_t write(uint8_t data) {
    return stream->write(data);
  }
};

class Bluetooth : public Stream
{
protected:
  BluetoothIO *io;

  const char *cod = NULL;
  const char *name = NULL;
  const char *pin = NULL;

  int mode = 0;

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

  void initIO(BluetoothIO &new_io) {
    io = &new_io;
  }

public:
  Bluetooth(int new_mode = 0,
            const char *new_name = NULL,
            const char *new_pin = NULL,
            const char *new_cod = NULL) {
    name = new_name;
    pin = new_pin;
    mode = new_mode;
    cod = new_cod;
  }

  virtual void setup() = 0;
  virtual bool connected() = 0;

  const char *getName() {
    return name;
  }

  const char *getPin() {
    return pin;
  }

  int getMode() {
    return mode;
  }

  virtual int available() {
    return io->available();
  }

  virtual int read() {
    return io->read();
  }

  virtual int peek()  {
    return io->peek();
  }

  virtual void flush()  {
    io->flush();
  }

  virtual size_t write(uint8_t data) {
    return io->write(data);
  }

  virtual size_t write(uint8_t *data, size_t size)
  {
    size_t len = 0;
    while (size--) {
     len += write(*data++);
    }
    return len;
  }
};

#endif /* BLUETOOTH_H */
