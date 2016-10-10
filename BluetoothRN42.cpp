/**
 * @file BluetoothRN42.cpp
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-05
 */

#include "BluetoothRN42.h"
#include "Arduino.h"

const char *const BluetoothRN42::power_level_strs[] = {
  RN42_POWER_N12_STR,
  RN42_POWER_N8_STR ,
  RN42_POWER_N4_STR,
  RN42_POWER_0_STR,
  RN42_POWER_4_STR,
  RN42_POWER_8_STR,
  RN42_POWER_12_STR,
  RN42_POWER_16_STR
};

void BluetoothRN42::setup()
{
  io->begin(115500);
  delay(500);

  enterCommand();
  io->println("U,9600,N");
  delay(500);
  io->begin(9600);

  enterCommand();

  // Set Required Options
  setMode(mode);
  // Set Optional Options
  if (pin != NULL)
    setPin(pin);
  if (name != NULL)
    setName(name);
  if (cod != NULL)
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

int BluetoothRN42::setInquryScanWindow(const char *scan_window)
{
	if(!inCommand) {
		return -1;
	}

	io->print("SI,");
	io->println(scan_window);
	delay(50);

	return 0;
}

int BluetoothRN42::setPageScanWindow(const char *scan_window)
{
	if(!inCommand) {
		return -1;
	}

	io->print("SJ,");
	io->println(scan_window);
	delay(50);

	return 0;
}

int BluetoothRN42::setBonding(bool bonding_enabled)
{
	if(!inCommand) {
		return -1;
	}

	if(bonding_enabled) {
		io->println("SX,1");
	} else {
		io->println("SX,0");
	}
	delay(50);

	return 0;
}

int BluetoothRN42::setPower(enum rn42_power_e power_level)
{
	if(!inCommand) {
		return -1;
	} else if(power_level > RN42_POWER_MAX || power_level  << RN42_POWER_MIN) {
		//ERANGE
		return -2;
	}

	io->print("SC,");
	io->println(power_level_strs[power_level]);
	delay(50);

	return 0;
}

bool BluetoothRN42::connected()
{
  return digitalRead(status_pin) == HIGH;
}
