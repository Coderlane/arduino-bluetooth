#include <ArduinoUnit.h>
#include <TestBluetooth.h>

TestSerial testSerial;
TestBluetooth bluetooth(testSerial, 0, "BlueController");

test(read_write_serial)
{
  int rc;
  const char test_char = 'a';

  rc = testSerial.write(test_char);
  assertEqual(rc, 1);

  rc = testSerial.write(test_char);
  assertEqual(rc, 1);

  rc = testSerial.read();
  assertEqual(rc, test_char);

  rc = testSerial.read();
  assertEqual(rc, test_char);
}

test(read_write)
{
  int rc;
  size_t test_buff_len = 5;
  const char *test_buff = "test";
  char buff[test_buff_len];

  rc = bluetooth.write((uint8_t *) test_buff, test_buff_len);
  assertEqual(rc, test_buff_len);

  rc = bluetooth.readBytes((uint8_t*) buff, test_buff_len);
  assertEqual(rc, test_buff_len);

  assertEqual(strncmp(test_buff, buff, test_buff_len), 0);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only

  bluetooth.setup();
}

void loop()
{
  Test::run();
}
