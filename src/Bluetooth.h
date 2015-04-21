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
#include <HardwareSerial.h>

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
    stream->write(data);
  }
};

class HardwareBluetoothIO : public BluetoothIO
{
private:
  HardwareSerial *serial;

public:
  HardwareBluetoothIO() {
    serial = NULL;
  }

  virtual void initSerial(HardwareSerial &new_serial) {
    serial = &new_serial;
    BluetoothIO::initSerial((Stream &)new_serial);
  }

  virtual void begin(unsigned long baud) {
    serial->begin(baud);
  }
};

class SoftwareBluetoothIO : public BluetoothIO
{
  SoftwareSerial *serial;
public:
  SoftwareBluetoothIO() {
    serial = NULL;
  }

  virtual void initSerial(SoftwareSerial &new_serial) {
    serial = &new_serial;
    BluetoothIO::initSerial((Stream &)new_serial);
  }

  virtual void begin(unsigned long baud) {
    serial->begin(baud);
  }
};

class Bluetooth : public Stream
{
protected:
  BluetoothIO *io;

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
    io->write(data);
  }
};

#endif /* ARDUINO_BLUETOOTH_H */
