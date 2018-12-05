// Hmi4DinBox Class: LCD Constrast Example
// by epsilonrt <https://github.com/epsilonrt>

// How to control the LCD ?

// Created 18 may 2018

// This example code is in the public domain.

#include <Hmi4DinBox.h>

const int hirqPin = 2;
Hmi4DinBox hmi (hirqPin);

byte ct;
void printContrast ();

void setup() {

  if (!hmi.begin (24)) {

    exit (1); // HMI failed to start !
  }
  ct = hmi.lcd.getcontrast();

  hmi.lcd.print ("Contrast value:");
  printContrast ();
}

void loop() {

  if (hmi.keyb.available()) { // check if keys are available
    byte key;

    key = hmi.keyb.key(); // get the next key
    if (hmi.keyb.pressed()) { // this key was pressed ?

      if ( (key == KUP) || (key == KDOWN)) {
        if (key == KUP) {

          hmi.lcd.adjcontrast (1); // increase contrast
        }
        else  {

          hmi.lcd.adjcontrast (-1); // decrease contrast
        }
        ct = hmi.lcd.getcontrast();
        printContrast ();
        hmi.led.toggle (LED_GREEN1);
      }
    }
  }
}

// displays the contrast value on the 2nd line
void printContrast () {
  hmi.lcd.setCursor (1, 0); //LINE 2 ADDRESS 0
  hmi.lcd.print (ct, DEC);
  hmi.lcd.write (' ');
}