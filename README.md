# Upload Command

`platformio run --target upload` Build project and upload firmware to the all devices specified in Project Configuration File platformio.ini

## Current issues:

- Missing trace on board in upper right corner between I2C pull-up resistors
- Feather pin 9 is not capable of PWM, despite documentation.  can't use motor controllers
  as intended.

## Links

- [Ardunio example I2C](https://www.arduino.cc/en/Tutorial/DigitalPotentiometer)
- [Compass Datasheet](http://cache.freescale.com/files/sensors/doc/data_sheet/MAG3110.pdf)
- [Compass Appnote](http://www.nxp.com/assets/documents/data/en/application-notes/AN4984.pdf)
