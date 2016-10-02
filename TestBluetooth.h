
#ifndef TEST_BLUETOOTH_H
#define TEST_BLUETOOTH_H

#include "Bluetooth.h"
#include <Stream.h>

#define RING_SIZE 256

class TestSerial : public Stream
{
protected:
  uint8_t ring[RING_SIZE];

  int head;
  int tail;
  int len;

public:
  TestSerial() {
    head = tail = len = 0;
  }

  virtual int available() {
    return len;
  }

  virtual int availableForWrite() {
    if (len >= RING_SIZE)
      return 0;
    return RING_SIZE - len;
  }

  virtual int read() {
    int data;
    if (available() == 0)
      return -1;


    data = ring[tail];

    len--;
    tail++;
    if (tail >= RING_SIZE)
      tail = 0;

    return data;
  }

  virtual int peek() {
    if (available() == 0)
      return -1;

    return ring[tail];
  }

  virtual void flush() {
    return;
  }

  virtual size_t write(uint8_t data) {
    /* Check if we still have write space. */
    if (availableForWrite() == 0)
      return 0;

    ring[head] = data;

    len++;
    head++;
    if (head >= RING_SIZE)
      head = 0;

    return 1;
  }

  virtual size_t write(uint8_t *data, size_t size) {
    size_t len = 0;
    while (size--) {
      size_t rc = write(*data++);
      if (rc <= 0)
        break;
      len += rc;
    }
    return len;
  }
};

class TestBluetoothIO : public BluetoothIO
{
  Stream *serial;
public:
  TestBluetoothIO() {
    serial = NULL;
  }

  virtual void initSerial(Stream &new_stream) {
    serial = &new_stream;
    BluetoothIO::initSerial(new_stream);
  }

  virtual void begin(unsigned long) {
    return;
  }
};

class TestBluetooth : public Bluetooth
{
  TestBluetoothIO testIO;
  bool conn = true;

public:
  TestBluetooth(Stream &new_stream, int new_mode = 0,
      const char *new_name = NULL, const char *new_pin = NULL,
      const char *new_cod = NULL) : Bluetooth(new_mode,
        new_name, new_pin, new_cod) {
    testIO.initSerial(new_stream);
    initIO(testIO);
  }

  virtual void setup() {
    return;
  }

  virtual bool connected() {
    return conn;
  }

  void setConnected(bool new_conn) {
    conn = new_conn;
  }
};

#endif
