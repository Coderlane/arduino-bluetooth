#include <HardwareBluetoothRN42.h>

const int status_pin = 2;      // D2
const int status_led_pin = 3;  // D3

long cur_millis = 0;
long prev_millis = 0;
long interval_millis = 100;
int status_led_state = LOW;
int recent_disconnect = 0;

HardwareBluetoothRN42 bluetooth(Serial1, status_pin, 3, "BlueHost");

void connection_up();
void connection_lost();
void connection_down();

void setup()
{
  delay(1000);
  analogReference(DEFAULT);
  bluetooth.setup();
  bluetooth.setTimeout(10);
  pinMode(status_led_pin, OUTPUT);
}

void loop ()
{
  long cur_millis = millis();
  if (cur_millis - prev_millis > interval_millis) {
    prev_millis = cur_millis;

    if (bluetooth.connected()) {
      connection_up();
    } else if (recent_disconnect < 50) {
      connection_lost();
    } else {
      connection_down();
    }
  }
}

inline void connection_up()
{
  char buff[64];
  int percent;
  // Connection is up.

  bluetooth.readBytesUntil('\n', buff, sizeof(buff));

  recent_disconnect = 0;
  interval_millis = 100;

  if (status_led_state != HIGH) {
    // Turn on LED
    digitalWrite(status_led_pin, HIGH);
    status_led_state = HIGH;
  }
}

inline void connection_lost()
{
  // Connection recently lost.
  // Attempt to resend quickly :)

  interval_millis = 500;
  recent_disconnect++;

  // Blink LED
  if (status_led_state == LOW) {
    digitalWrite(status_led_pin, HIGH);
    status_led_state = HIGH;
  } else {
    digitalWrite(status_led_pin, LOW);
    status_led_state = LOW;
  }
}

inline void connection_down()
{
  // Connection has been lost for a while.

  interval_millis = 2000;
  if (status_led_state != LOW) {
    // Turn off LED
    digitalWrite(status_led_pin, LOW);
    status_led_state = LOW;
  }
}
