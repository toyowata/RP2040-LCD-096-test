/* Mbed Microcontroller Library
 * Copyright (c) 2019-2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
 
#ifndef MBED_ST7735S_H
#define MBED_ST7735S_H

#include "mbed.h"
#include "GraphicsDisplay.h"

#define RGB(r,g,b)  (((r&0xF8)<<8)|((g&0xFC)<<3)|((b&0xF8)>>3)) // 5 red | 6 green | 5 blue

/* ST7735S Commands */

/* System Function Command List */

#define ST7735_NOP        0x00
#define ST7735_SWRESET    0x01
#define ST7735_RDDID      0x04
#define ST7735_RDDST      0x09
#define ST7735_RDDPM      0x0A
#define ST7735_RDDMADCTL  0x0B
#define ST7735_RDDCOLMOD  0x0C
#define ST7735_RDDIM      0x0D
#define ST7735_RDDSM      0x0E
#define ST7735_RDDSDR     0x0F

#define ST7735_SLPIN      0x10
#define ST7735_SLPOUT     0x11
#define ST7735_PTLON      0x12
#define ST7735_NORON      0x13

#define ST7735_INVOFF     0x20
#define ST7735_INVON      0x21
#define ST7735_GAMSET     0x26
#define ST7735_DISPOFF    0x28
#define ST7735_DISPON     0x29
#define ST7735_CASET      0x2A
#define ST7735_RASET      0x2B
#define ST7735_RAMWR      0x2C
#define ST7735_RAMRD      0x2E

#define ST7735_PTLAR      0x30
#define ST7735_SCRLAR     0x33
#define ST7735_TEOFF      0x34
#define ST7735_TEON       0x35
#define ST7735_MADCTL     0x36
#define ST7735_VSCSAD     0x37
#define ST7735_IDMOFF     0x38
#define ST7735_IDMON      0x39
#define ST7735_COLMOD     0x3A

#define ST7735_RDID1      0xDA
#define ST7735_RDID2      0xDB
#define ST7735_RDID3      0xDC

/* Panel Function Command List */

#define ST7735_FRMCTR1    0xB1
#define ST7735_FRMCTR2    0xB2
#define ST7735_FRMCTR3    0xB3
#define ST7735_INVCTR     0xB4

#define ST7735_PWCTR1     0xC0
#define ST7735_PWCTR2     0xC1
#define ST7735_PWCTR3     0xC2
#define ST7735_PWCTR4     0xC3
#define ST7735_PWCTR5     0xC4
#define ST7735_VMCTR1     0xC5
#define ST7735_VMOFCTR    0xC7

#define ST7735_WRID2      0xD1
#define ST7735_WRID3      0xD2
#define ST7735_NVFCTR1    0xD9
#define ST7735_NVFCTR2    0xDE
#define ST7735_NVFCTR3    0xDF

#define ST7735_GMCTRP1    0xE0
#define ST7735_GMCTRN1    0xE1

#define ST7735_GCV        0xFC

/* some RGB color definitions */

#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */

const int _width = 160;
const int _height = 80;

class ST7735S : public GraphicsDisplay {
public:

    /** Create a ST7735_TFT object connected to SPI and three pins. ST7735 requires rs pin to toggle between data/command
      *
      * @param mosi,miso,sclk SPI
      * @param cs pin connected to CS of display (called SS for 'Slave Select' in ST7735 datasheet)
      * @param rs pin connected to RS of display (called D/CX in ST7735 datasheet)
      * @param reset pin connected to RESET of display
      *
      */ 
    ST7735S(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rs, PinName reset, const char* name = "TFT");

    /** Get the width of the screen in pixel
    *
    * @param 
    * @returns width of screen in pixel
    *
    */    
    virtual int width();

    /** Get the height of the screen in pixel
    *
    * @returns height of screen in pixel 
    *
    */     
    virtual int height();

    /** Draw a pixel at x,y with color 
    *  
    * @param x horizontal position
    * @param y vertical position
    * @param color 16 bit pixel color
    */    
    virtual void pixel(int x, int y, int color);

    /** draw a circle
    *
    * @param x0,y0 center
    * @param r radius
    * @param color 16 bit color
    *
    */       
    void circle(int x, int y, int r, int color); 

    /** draw a filled circle
    *
    * @param x0,y0 center
    * @param r radius
    * @param color 16 bit color
    *
    * use circle with different radius,
    * can miss some pixel
    */    
    void fillcircle(int x, int y, int r, int color); 

    /** draw a 1 pixel line
    *
    * @param x0,y0 start point
    * @param x1,y1 stop point
    * @param color 16 bit color
    *
    */    
    void line(int x0, int y0, int x1, int y1, int color);

    /** draw a rect
    *
    * @param x0,y0 top left corner
    * @param x1,y1 down right corner
    * @param color 16 bit color
    *
    */    
    void rect(int x0, int y0, int x1, int y1, int color);

    /** draw a filled rect
    *
    * @param x0,y0 top left corner
    * @param x1,y1 down right corner
    * @param color 16 bit color
    *
    */    
    void fillrect(int x0, int y0, int x1, int y1, int color);

    /** setup cursor position
    *
    * @param x x-position (top left)
    * @param y y-position 
    */   
    void locate(int x, int y);

    /** Fill the screen with _backgroun color
    *
    */   
    virtual void cls (void);   

    /** calculate the max number of char in a line
    *
    * @returns max columns
    * depends on actual font size
    *
    */    
    int columns(void);

    /** calculate the max number of columns
    *
    * @returns max column
    * depends on actual font size
    *
    */   
    int rows(void);

    /** put a char on the screen
    *
    * @param value char to print
    * @returns printed char
    *
    */
    int _putc(int value);

    /** draw a character on given position out of the active font to the TFT
    *
    * @param x x-position of char (top left) 
    * @param y y-position
    * @param c char to print
    *
    */    
    virtual void character(int x, int y, int c);

    /** paint a bitmap on the TFT 
    *
    * @param *image pointer to the bitmap data
    * @param xStart, yStart : upper left corner 
    * @param W_Image width of bitmap
    * @param H_Image high of bitmap
    *
    *   bitmap format: 16 bit R5 G6 B5
    * 
    *   use Gimp to create / load , save as BMP, option 16 bit R5 G6 B5            
    *   use winhex to load this file and mark data stating at offset 0x46 to end
    *   use edit -> copy block -> C Source to export C array
    *   paste this array into your program
    * 
    *   define the array as static const unsigned char to put it into flash memory
    *   cast the pointer to (unsigned char *) :
    *   tft.Paint_DrawImage((unsigned char *)scala, 10, 40, 309, 50);
    */    
    void Paint_DrawImage(const unsigned char *image, uint16_t xStart, uint16_t yStart, uint16_t W_Image, uint16_t H_Image);

    /** select the font to use
    *
    * @param f pointer to font array 
    *                                                                              
    *   font array can created with GLCD Font Creator from http://www.mikroe.com
    *   you have to add 4 parameter at the beginning of the font array to use: 
    *   - the number of byte / char
    *   - the vertial size in pixel
    *   - the horizontal size in pixel
    *   - the number of byte per vertical line
    *   you also have to change the array to char[]
    *
    */  
    void set_font(unsigned char* f);

    SPI _spi;
    DigitalOut _cs;
    DigitalOut _rs;
    DigitalOut _reset;
    unsigned char* _font;
   
protected:

    /** draw a horizontal line
    *
    * @param x0 horizontal start
    * @param x1 horizontal stop
    * @param y vertical position
    * @param color 16 bit color                                               
    *
    */
    void hline(int x0, int x1, int y, int color);

    /** draw a vertical line
    *
    * @param x horizontal position
    * @param y0 vertical start 
    * @param y1 vertical stop
    * @param color 16 bit color
    */
    void vline(int y0, int y1, int x, int color);

    /** Set draw window region
    *
    * @param x horizontal position
    * @param y vertical position
    * @param w window width in pixel
    * @param h window height in pixels
    */    
    void window (unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    /** Set draw window region to whole screen
    *
    */  
    void WindowMax (void);

    /** Init the ST7735 controller
    *
    */    
    void init();

    /** Write data to the LCD controller
    *
    * @param dat data written to LCD controller
    * 
    */   
    void wr_dat(int value);

    /** Write a command the LCD controller 
    *
    * @param cmd: command to be written   
    *
    */   
    void wr_cmd(int value);

    /** write data to the LCD controller
    *
    * @param data to be written 
    *
    */    
    void wr_dat_only(unsigned short dat);

    /** Write a value to the to a LCD register
    *
    * @param reg register to be written
    * @param val data to be written
    */   
    void wr_reg (unsigned char reg, unsigned short val);

    unsigned int char_x;
    unsigned int char_y;

};

#endif
