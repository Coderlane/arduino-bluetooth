/**
 * @file BluetoothRN42.cpp
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-05
 */

#include "BluetoothRN42.h"
#include "Arduino.h"

void BluetoothRN42::setup()
{
  this->begin(115200);

  enterCommand();

	setMode(mode);
	setPin(pin);
	setName(name);
	setCod(cod);

	pinMode(status_pin, INPUT);

	exitCommand();
}

void BluetoothRN42::enterCommand()
{
  if(inCommand) {
    return;
  }

  // Start by printing w/o CR.
  this->print("$$$");

  // Wait for chip
  delay(100);

  inCommand = true;
}

void BluetoothRN42::exitCommand()
{
  if(!inCommand) {
    return;
  }

  inCommand = false;

  this->println("---");
}

int BluetoothRN42::setMode(int new_mode)
{
  if(!inCommand) {
    return -1;
  }

  // Set the mode
  this->print("SM,");
  this->println(new_mode);

  return Bluetooth::setMode(new_mode);
}

int BluetoothRN42::setPin(const char *new_pin)
{
  if(!inCommand) {
    return -1;
  }

  this->print("SP,");
  this->println(new_pin);

  return Bluetooth::setPin(new_pin);
}

int BluetoothRN42::setName(const char *new_name)
{
  if(!inCommand) {
    return -1;
  }

  this->print("SN,");
  this->println(new_name);

  return Bluetooth::setName(new_name);
}

int BluetoothRN42::setCod(const char *new_cod)
{
  if(!inCommand) {
    return -1;
  }

  // Print the first two characters.
  this->print("SC,00");
  this->print(new_cod[5]);
  this->println(new_cod[4]);

  // Print the last four characters.
  this->print("SD,");
  this->print(new_cod[3]);
  this->print(new_cod[2]);
  this->print(new_cod[1]);
  this->println(new_cod[0]);

  return Bluetooth::setCod(new_cod);
}

bool BluetoothRN42::isConnected()
{
	return digitalRead(status_pin) == HIGH;

// Old way of doing is connected.
#if 0
  char status[6] = "";
  if(!inCommand) {
    return -1;
  }

  this->println("GC");

  this->readBytes(status, sizeof(status));
  status[5] = '\0';

  if(strcmp(status, "1,0,0") == 0) {
		// Connection is up.
    return 1;
  }

	// Connection is down.
  return 0;
#endif
}
