/* Mbed Microcontroller Library
 * Copyright (c) 2019-2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "USBSerial.h"
#include "ST7735S.h"

#include "fonts/Arial12x12.h"
#include "fonts/Arial24x23.h"
#include "fonts/Arial28x28.h"
#include "fonts/font_big.h"
#include "images/ImageData.h"
#include "images/ekimemo.h"

const uint16_t color[18] = {
    Black,
    Navy,
    DarkGreen,
    DarkCyan,
    Maroon,
    Purple,
    Olive,
    LightGrey,
    DarkGrey,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
    Orange,
    GreenYellow
};

DigitalOut back_light(p25);
ST7735S tft(ST7735S_MOSI, ST7735S_MISO, ST7735S_SCLK, ST7735S_CS, ST7735S_RS, ST7735S_RESET);

#define DEMO_COLOR      0
#define DEMO_RECT       0
#define DEMO_ANIMATION  0
#define DEMO_TEXT       0
#define DEMO_CLOCK      1
#define DEMO_BITMAP     1
#define DEMO_SCROLL     0

int main()
{
    back_light = 1;

    tft.claim(stdout);      // send stdout to the TFT display
    tft.background(Black);
    tft.cls();
    tft.disp(1);

    while(1) {
#if DEMO_COLOR
        // Color bar
        for(int i = 0; i < 16; i++) {
            tft.fillrect(i * (_width / 16), 0, (i + 1) * (_width / 16), 79, color[i+1]);
        }
        ThisThread::sleep_for(4000ms);
#endif

#if DEMO_RECT
        // Rect
        tft.background(DarkGrey);
        tft.foreground(White);
        tft.cls();
        for(int i = 0; i < 160; i += 8) {
            for(int j = 0; j < 80; j += 8) {
                //tft.rect(i, j, i + 8, j + 8, White);
                tft.rect(i, j, i + 8, j + 8, color[rand() % 18 + 1]);
            }
        }
        tft.rect(0, 0, 159, 79, DarkGrey);
        ThisThread::sleep_for(4000ms);
#endif

#if DEMO_ANIMATION
        // Animation
        tft.set_font((unsigned char*) Arial12x12);
        tft.background(Blue);
        tft.foreground(White);
        tft.fillrect(0, 0, 159, 79, Blue);
        for(int x = 159; x >= 0; x--) {
            tft.rect(0, 0, x, (x/2), Red);
            if (x - 119 > 0) {
                tft.circle(x - 40, 40, x - 119, Yellow);
            }
            tft.locate(10,10);
            tft.printf("X=%3d, y=%2d", x, x/2);
            ThisThread::sleep_for(30ms);
            tft.rect(0, 0, x, (x/2), Blue);
            if (x - 119 > 0) {
                tft.circle(x - 40, 40, x - 119, Blue);
            }
        }
        ThisThread::sleep_for(4000ms);
#endif

#if DEMO_TEXT
        // Draw text
        tft.foreground(Yellow);
        tft.background(Navy);
        tft.cls();
        tft.set_font((unsigned char*) Arial12x12);
        tft.locate(2, 4);
        tft.printf("ABCDabcd1234");
        tft.set_font((unsigned char*) Arial24x23);
        tft.locate(2, 18);
        tft.printf("ABCDabcd");
        tft.set_font((unsigned char*) Arial28x28);
        tft.locate(2, 46);
        tft.printf("ABCDabcd");
        ThisThread::sleep_for(4000ms);
#endif

#if DEMO_CLOCK
        // Draw text
        tft.foreground(Yellow);
        tft.background(DarkGrey);
        tft.cls();
        tft.set_font((unsigned char*) Neu42x35);
        char s[6];
        for (int i = 0; i < 5; i++) {
            tft.locate(20, 40-(35/2));
            sprintf(s, "12:3%c", i + '0');
            tft.printf("%s", s);
            ThisThread::sleep_for(1000ms);
        }
        ThisThread::sleep_for(2000ms);
#endif

#if DEMO_BITMAP
        // Bitmap
        tft.Paint_DrawImage(gImage_0inch96_1, 0, 0, 160, 80);
        ThisThread::sleep_for(4000ms);
#endif

#if DEMO_SCROLL
        // Scroll
        for (int i = 0; i < (284 - 80); i+=2) {
            tft.Paint_DrawImage(ekimemo_bmp + (i * 160 * 2), 0, 0, 160, 80);
            ThisThread::sleep_for(1ms);
        }
        tft.Paint_DrawImage(ekimemo_bmp, 0, 0, 160, 80);
        ThisThread::sleep_for(4000ms);
#endif

    }
}
