/**
 * @file BluetoothRN42.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2015-03-04
 */

#ifndef BLUETOOTHRN42_H
#define BLUETOOTHRN42_H

#include "Bluetooth.h"

#define RN42_POWER_16_STR  "0010"
#define RN42_POWER_12_STR  "000C"
#define RN42_POWER_8_STR   "0008"
#define RN42_POWER_4_STR   "0004"
#define RN42_POWER_0_STR   "0000"
#define RN42_POWER_N4_STR  "FFFC"
#define RN42_POWER_N8_STR  "FFF8"
#define RN42_POWER_N12_STR "FFF4"

enum rn42_power_e {
	RN42_POWER_16  = 7,
	RN42_POWER_12  = 6,
	RN42_POWER_8   = 5,
	RN42_POWER_4   = 4,
	RN42_POWER_0   = 3,
	RN42_POWER_N4  = 2,
	RN42_POWER_N8  = 1,
	RN42_POWER_N12 = 0
};

#define RN42_POWER_MAX RN42_POWER_16
#define RN42_POWER_MIN RN42_POWER_N12

class BluetoothRN42 : public Bluetooth
{
protected:
  int status_pin;
  bool inCommand;

  void enterCommand();
  void exitCommand();

	static const char * const power_level_strs[];

public:
  BluetoothRN42(int new_status_pin, int new_mode = 0,
                const char *new_name = NULL,
                const char *new_pin = NULL) :
    Bluetooth(new_mode, new_name, new_pin) {
    status_pin = new_status_pin;
    inCommand = false;
  }

  int setMode(int new_mode);
  int setPin(const char *new_pin);
  int setName(const char *new_name);
  int setCod(const char *new_cod);
	
	// Device Specific
	int setInquryScanWindow(const char *scan_window);
	int setPageScanWindow(const char *scan_window);
	int setBonding(bool bonding_enabled);
	int setPower(enum rn42_power_e power_level);

	// Gotta implement
  virtual bool isConnected();
  virtual void setup();
};

#endif /* BLUETOOTHRN42_H */
