
#include <cstdlib>
#include <SoftwareSerial.h>

#include "BluetoothRN42.h"

extern int delay(int);

void BluetoothRN42::Setup()
{
	char mode_buff[(sizeof(int)*8+1)];

	Serial.Begin(115200);

	// Start by printing w/o CR.
	Serial.print("$$$");

	delay(100);

	Serial.print("SM,");
	Serial.println(itoa(mode, mode_buff, sizeof(mode_buff));

	if(name != NULL) {
		Serial.print("SN,");
		Serial.println(name);
	}

	if(pin != NULL) {
		Serial.print("SP,");
		Serial.println(pin);
	}

	Serial.println("---");
}
