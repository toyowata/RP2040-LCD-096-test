# RP2040-LCD-096-test
Waveshare RP2040-LCD-0.96 test program for Mbed OS

![](https://www.waveshare.com/media/catalog/product/cache/1/image/800x800/9df78eab33525d08d6e5fb8d27136e95/r/p/rp2040-lcd-0.96-1.jpg)

## How to build and flash to target board

### Preparation
* Install Mbed CLI1
https://os.mbed.com/docs/mbed-os/v6.15/build-tools/install-and-set-up.html
* Install picotool
https://github.com/raspberrypi/picotool/blob/master/README.md

### Mbed CLI1
```
$ mbed import https://github.com/toyowata/RP2040-LCD-096-test
$ cd RP2040-LCD-096-test
$ mbed compile -m RASPBERRY_PI_PICO -t gcc_arm
$ picotool load ./BUILD/RASPBERRY_PI_PICO/GCC_ARM/RP2040-LCD-096-test.bin
```

## How to create bitmap image

* Use GIMP to create the image, from menu [Image] - [Transform] - [Flip Virtucally]
* [File] - [Export As ...] and save as BMP
    * Check `Do not write color space information`
    * Select 16 bits, R5 G6 B5 format and press [Export] button
* Convert to C array format from 70 bytes offset (skip BMP header information)

```
# example by xxd command
$ xxd -s 70 -i image.bmp > image.h 
```
