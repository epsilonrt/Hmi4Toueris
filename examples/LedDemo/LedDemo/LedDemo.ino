// Hmi4DinBox Class: LED Example
// by epsilonrt <https://github.com/epsilonrt>

// How to control the leds ?

// Created 18 may 2018

// This example code is in the public domain.
#ifdef __unix__
#include <Piduino.h>  // All the magic is here ;-)
#else
// Defines the serial port as the console on the Arduino platform
#define Console Serial
#endif

#include <Hmi4DinBox.h>

const int lcdContrast = 34; // 24 if you use a 5V power supply, 34 if you use a 3.3V power supply
const bool lcdBoost = true; // false if you use a 5V power supply, true if you use a 3.3V power supply

Hmi4DinBox hmi;
void printLed (int led);

void setup() {

  Console.begin (115200);
  Wire.begin(); // change this if you use another I2C port or if you use non standard I2C pins
  if (!hmi.begin (lcdContrast, lcdBoost)) {

    Console.println("hmi.begin() failed !");
    exit (1); // HMI failed to start !
  }
  hmi.lcd.cursor();
  hmi.lcd.blink();
  hmi.lcd.clear();
  hmi.lcd.print ("12345");
}

void loop() {

  // turn on all leds
  hmi.led.writeAll();
  // Pause
  delay (2000);

  // turn off all leds
  hmi.led.writeAll (0);
  // Pause
  delay (2000);

  // turn on the LEDs one by one.
  hmi.led.set (LED1);
  delay (500);
  hmi.led.set (LED2);
  delay (500);
  hmi.led.set (LED3);
  delay (500);
  hmi.led.set (LED4);
  delay (500);
  hmi.led.set (LED5);
  delay (500);
  // Pause
  delay (2000);

  // turn off the LEDs one by one with a for loop
  for (int led = LED1; led <= LED5; led++) {
    hmi.led.clear (led);
    delay (500);
  }
  // Pause
  delay (2000);

  // turn on the LEDs one by with a for loop, using toggle and get value.
  for (int led = LED1; led <= LED5; led++) {
    hmi.led.toggle (led);
    printLed (led);
    delay (500);
  }
  // Pause
  delay (2000);

  // turn off the LEDs one by with a for loop, using toggle() and get()
  for (int led = LED1; led <= LED5; led++) {
    hmi.led.toggle (led);
    printLed (led);
    delay (500);
  }
  // Pause
  delay (2000);
}

void printLed (int led) {
  hmi.lcd.setCursor (1, led);
  if (hmi.led.get (led)) {
    hmi.lcd.write ('O');
  }
  else {

    hmi.lcd.write ('_');
  }
}
