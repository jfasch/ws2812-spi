Links
=====

* WS2812 definition, gimings, protocol ...:
  https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
* SPI on Raspberry: https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf
  
  Especially taking care of "2.3.1. SPI implementation details", where
  they say that there is a garanteed gap between two bytes. During
  that time the MOSI signal is also low (alas it's SPI).
