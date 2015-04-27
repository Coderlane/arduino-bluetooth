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
  io->begin(115500);
  delay(500);
  
  enterCommand();
  io->println("U,9600,N");
  ////io->println("SU,96");
  delay(500);
  io->begin(9600);
  
  //setMode(mode);
  //setPin(pin);
  setName(name);
  //setCod(cod);

  pinMode(status_pin, INPUT);

  exitCommand();
}

void BluetoothRN42::enterCommand()
{
  if(inCommand) {
    return;
  }

  // Start by printing w/o CR.
  io->print("$$$");

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

  io->println("---");
  delay(50);
}

int BluetoothRN42::setMode(int new_mode)
{
  if(!inCommand) {
    return -1;
  }

  // Set the mode
  io->print("SM,");
  io->println(new_mode);
  delay(50);
  return Bluetooth::setMode(new_mode);
}

int BluetoothRN42::setPin(const char *new_pin)
{
  if(!inCommand) {
    return -1;
  }

  io->print("SP,");
  io->println(new_pin);
  delay(50);
  return Bluetooth::setPin(new_pin);
}

int BluetoothRN42::setName(const char *new_name)
{
  if(!inCommand) {
    return -1;
  }

  io->print("SN,");
  io->println(new_name);
  delay(50);
  return Bluetooth::setName(new_name);
}

int BluetoothRN42::setCod(const char *new_cod)
{
  if(!inCommand) {
    return -1;
  }

  // Print the first two characters.
  io->print("SC,00");
  io->print(new_cod[5]);
  io->println(new_cod[4]);
  delay(50);

  // Print the last four characters.
  io->print("SD,");
  io->print(new_cod[3]);
  io->print(new_cod[2]);
  io->print(new_cod[1]);
  io->println(new_cod[0]);
  delay(50);
  
  return Bluetooth::setCod(new_cod);
}

bool BluetoothRN42::isConnected()
{
	return digitalRead(status_pin) == HIGH;
}
