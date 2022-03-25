/* Mbed Microcontroller Library
 * Copyright (c) 2019-2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ST7735S.h"
#include "mbed.h"

ST7735S::ST7735S(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rs, PinName reset, const char *name)
    : GraphicsDisplay(name), _spi(mosi, miso, sclk), _cs(cs), _rs(rs), _reset(reset)
{
    init();
    char_x = 0;
    char_y = 0;
}

int ST7735S::width()
{
    return _width;
}

int ST7735S::height()
{
    return _height;
}

void ST7735S::wr_cmd(int cmd)
{
    _rs = 0; // rs low, cs low for transmitting command
    _cs = 0;
    _spi.write(cmd);
    _cs = 1;
}

void ST7735S::wr_dat(int dat)
{
    _rs = 1; // rs high, cs low for transmitting data
    _cs = 0;                         
    _spi.write(dat);                                                           
    _cs = 1;
}

void ST7735S::wr_reg (unsigned char reg, unsigned short val)
{
    wr_cmd(reg);
    wr_dat(val);
}

void ST7735S::init()
{    
    // init SPI
    _spi.format(8, 3);
    _spi.frequency(20000000);
    
    _reset = 1;
    ThisThread::sleep_for(10ms);
    _reset = 0;
    ThisThread::sleep_for(10ms);
    _reset = 1;
    ThisThread::sleep_for(120ms);

    wr_cmd(ST7735_SWRESET);
    ThisThread::sleep_for(150ms);
    wr_cmd(ST7735_SLPOUT);
    ThisThread::sleep_for(120ms);

    wr_cmd(ST7735_INVON);

    wr_cmd(ST7735_FRMCTR1);
    wr_dat(0x05);
    wr_dat(0x3A);
    wr_dat(0x3A);

    wr_cmd(ST7735_FRMCTR2);
    wr_dat(0x05);
    wr_dat(0x3A);
    wr_dat(0x3A);

    wr_cmd(ST7735_FRMCTR3);
    wr_dat(0x05);
    wr_dat(0x3A);
    wr_dat(0x3A);
    wr_dat(0x05);
    wr_dat(0x3A);
    wr_dat(0x3A);

    wr_cmd(ST7735_INVCTR);
    wr_dat(0x03);

    wr_cmd(ST7735_PWCTR1);
    wr_dat(0x62);
    wr_dat(0x02);
    wr_dat(0x04);

    wr_cmd(ST7735_PWCTR2);
    wr_dat(0xC0);

    wr_cmd(ST7735_PWCTR3);
    wr_dat(0x0D);
    wr_dat(0x00);

    wr_cmd(ST7735_PWCTR4);
    wr_dat(0x8D);
    wr_dat(0x6A);   

    wr_cmd(ST7735_PWCTR5);
    wr_dat(0x8D); 
    wr_dat(0xEE); 

    wr_cmd(ST7735_VMCTR1);
    wr_dat(0x0E);    

    wr_cmd(ST7735_GMCTRP1);
    wr_dat(0x10);
    wr_dat(0x0E);
    wr_dat(0x02);
    wr_dat(0x03);
    wr_dat(0x0E);
    wr_dat(0x07);
    wr_dat(0x02);
    wr_dat(0x07);
    wr_dat(0x0A);
    wr_dat(0x12);
    wr_dat(0x27);
    wr_dat(0x37);
    wr_dat(0x00);
    wr_dat(0x0D);
    wr_dat(0x0E);
    wr_dat(0x10);

    wr_cmd(ST7735_GMCTRN1);
    wr_dat(0x10);
    wr_dat(0x0E);
    wr_dat(0x03);
    wr_dat(0x03);
    wr_dat(0x0F);
    wr_dat(0x06);
    wr_dat(0x02);
    wr_dat(0x08);
    wr_dat(0x0A);
    wr_dat(0x13);
    wr_dat(0x26);
    wr_dat(0x36);
    wr_dat(0x00);
    wr_dat(0x0D);
    wr_dat(0x0E);
    wr_dat(0x10);

    wr_cmd(ST7735_COLMOD); 
    wr_dat(0x05);

    wr_cmd(ST7735_MADCTL);
    wr_dat(0xA8);

    wr_cmd(ST7735_DISPON);

    WindowMax ();
}

void ST7735S::pixel(int x, int y, int color)
{
    if ((x >= _width) || (y >= _height))
        return;
    
    window(x, y, x, y);
    _rs = 1; 
    _cs = 0;
    _spi.write(color >> 8);
    _spi.write(color);
    _cs = 1;
}

void ST7735S::window (unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    x++;
    w++;
    y += 26;
    h += 26;

    wr_cmd(ST7735_CASET);
    _rs = 1;
    _cs = 0;
    _spi.write(x >> 8);
    _spi.write(x);   // XSTART 
    _spi.write(w >> 8);
    _spi.write(w);   // XEND
    _cs = 1;

    wr_cmd(ST7735_RASET);
    _rs = 1;
    _cs = 0;
    _spi.write(y >> 8);
    _spi.write(y);    // YSTART
    _spi.write(h >> 8);
    _spi.write(h);    // YEND
    _cs = 1;

    wr_cmd(ST7735_RAMWR);
}

void ST7735S::WindowMax (void)
{
    window(0, 0, _width - 1,  _height - 1);
}

void ST7735S::cls (void)
{
    uint8_t b0, b1;
    b0 = (uint8_t)(_background >> 8);
    b1 = (uint8_t)(_background);
    WindowMax();
    _rs = 1;
    _cs = 0;
    for (int i = 0; i < (_width * _height); i++) {
        _spi.write(b0);
        _spi.write(b1);
    }
    _cs = 1;
}

void ST7735S::circle(int x0, int y0, int r, int color)
{
    int draw_x0, draw_y0;
    int draw_x1, draw_y1;
    int draw_x2, draw_y2;
    int draw_x3, draw_y3;
    int draw_x4, draw_y4;
    int draw_x5, draw_y5;
    int draw_x6, draw_y6;
    int draw_x7, draw_y7;
    int xx, yy;
    int di;

    if (r == 0) {       /* no radius */
        return;
    }

    draw_x0 = draw_x1 = x0;
    draw_y0 = draw_y1 = y0 + r;
    if (draw_y0 < _height) {
        pixel(draw_x0, draw_y0, color);     /* 90 degree */
    }

    draw_x2 = draw_x3 = x0;
    draw_y2 = draw_y3 = y0 - r;
    if (draw_y2 >= 0) {
        pixel(draw_x2, draw_y2, color);    /* 270 degree */
    }

    draw_x4 = draw_x6 = x0 + r;
    draw_y4 = draw_y6 = y0;
    if (draw_x4 < _width) {
        pixel(draw_x4, draw_y4, color);     /* 0 degree */
    }

    draw_x5 = draw_x7 = x0 - r;
    draw_y5 = draw_y7 = y0;
    if (draw_x5>=0) {
        pixel(draw_x5, draw_y5, color);     /* 180 degree */
    }

    if (r == 1) {
        return;
    }

    di = 3 - 2*r;
    xx = 0;
    yy = r;
    while (xx < yy) {

        if (di < 0) {
            di += 4*xx + 6;
        } else {
            di += 4*(xx - yy) + 10;
            yy--;
            draw_y0--;
            draw_y1--;
            draw_y2++;
            draw_y3++;
            draw_x4--;
            draw_x5++;
            draw_x6--;
            draw_x7++;
        }
        xx++;
        draw_x0++;
        draw_x1--;
        draw_x2++;
        draw_x3--;
        draw_y4++;
        draw_y5++;
        draw_y6--;
        draw_y7--;

        if ( (draw_x0 <= _width) && (draw_y0>=0) ) {
            pixel(draw_x0, draw_y0, color);
        }

        if ( (draw_x1 >= 0) && (draw_y1 >= 0) ) {
            pixel(draw_x1, draw_y1, color);
        }

        if ( (draw_x2 <= _width) && (draw_y2 <= _height) ) {
            pixel(draw_x2, draw_y2, color);
        }

        if ( (draw_x3 >=0 ) && (draw_y3 <= _height) ) {
            pixel(draw_x3, draw_y3, color);
        }

        if ( (draw_x4 <= _width) && (draw_y4 >= 0) ) {
            pixel(draw_x4, draw_y4, color);
        }

        if ( (draw_x5 >= 0) && (draw_y5 >= 0) ) {
            pixel(draw_x5, draw_y5, color);
        }
        if ( (draw_x6 <= _width) && (draw_y6 <= _height) ) {
            pixel(draw_x6, draw_y6, color);
        }
        if ( (draw_x7 >= 0) && (draw_y7 <= _height) ) {
            pixel(draw_x7, draw_y7, color);
        }
    }
}

void ST7735S::fillcircle(int x, int y, int r, int color)
{
    for (int i = 0; i <= r; i++) {
        circle(x, y, i, color);
    }
}

void ST7735S::hline(int x0, int x1, int y, int color)
{
    int w = x1 - x0 + 1;
    window(x0, y, x1, y);
    _rs = 1;
    _cs = 0;
    for (int x=0; x<w; x++) {
        _spi.write(color >> 8);
        _spi.write(color);
    }
    _cs = 0;
}

void ST7735S::vline(int x, int y0, int y1, int color)
{
    int h = y1 - y0 + 1;
    window(x, y0, x, y1);
    _rs = 1;
    _cs = 0;
    for (int y=0; y<h; y++) {
        _spi.write(color >> 8);
        _spi.write(color);
    }
    _cs = 1;
}

void ST7735S::line(int x0, int y0, int x1, int y1, int color)
{
    int   dx = 0, dy = 0;
    int   dx_sym = 0, dy_sym = 0;
    int   dx_x2 = 0, dy_x2 = 0;
    int   di = 0;

    dx = x1-x0;
    dy = y1-y0;

    if (dx == 0) {        /* vertical line */
        if (y1 > y0)
            vline(x0,y0,y1,color);
        else
            vline(x0,y1,y0,color);
        return;
    }

    if (dx > 0) {
        dx_sym = 1;
    } else {
        dx_sym = -1;
    }
    if (dy == 0) {        /* horizontal line */
        if (x1 > x0)
            hline(x0,x1,y0,color);
        else
            hline(x1,x0,y0,color);
        return;
    }

    if (dy > 0) {
        dy_sym = 1;
    } else {
        dy_sym = -1;
    }

    dx = dx_sym*dx;
    dy = dy_sym*dy;

    dx_x2 = dx*2;
    dy_x2 = dy*2;

    if (dx >= dy) {
        di = dy_x2 - dx;
        while (x0 != x1) {
            pixel(x0, y0, color);
            x0 += dx_sym;
            if (di<0) {
                di += dy_x2;
            } else {
                di += dy_x2 - dx_x2;
                y0 += dy_sym;
            }
        }
        pixel(x0, y0, color);
    } else {
        di = dx_x2 - dy;
        while (y0 != y1) {
            pixel(x0, y0, color);
            y0 += dy_sym;
            if (di < 0) {
                di += dx_x2;
            } else {
                di += dx_x2 - dy_x2;
                x0 += dx_sym;
            }
        }
        pixel(x0, y0, color);
    }
    return;
}

void ST7735S::rect(int x0, int y0, int x1, int y1, int color)
{
    if (x1 > x0)
        hline(x0,x1,y0,color);
    else 
        hline(x1,x0,y0,color);

    if (y1 > y0)
        vline(x0,y0,y1,color);
    else
        vline(x0,y1,y0,color);

    if (x1 > x0)
        hline(x0,x1,y1,color);
    else
        hline(x1,x0,y1,color);

    if (y1 > y0)
        vline(x1,y0,y1,color);
    else
        vline(x1,y1,y0,color);
}

void ST7735S::fillrect(int x0, int y0, int x1, int y1, int color)
{
    int h = y1 - y0 + 1;
    int w = x1 - x0 + 1;
    int fill_size = h * w;

    window(x0, y0, x1, y1);
    _rs = 1;
    _cs = 0;
    for (int i = 0; i < fill_size; i++) {
        _spi.write(color >> 8);
        _spi.write(color);
    }
    _cs = 1;
}

void ST7735S::locate(int x, int y)
{
    char_x = x;
    char_y = y;
}

int ST7735S::columns()
{
    return (_width / _font[1]);
}

int ST7735S::rows()
{
    return (_height / _font[2]);
}

int ST7735S::_putc(int value)
{
    if (value == '\n') {    // new line
        char_x = 0;
        char_y = char_y + _font[2];
        if (char_y >= _height - (unsigned int )_font[2]) {
            char_y = 0;
        }
    } else {
        character(char_x, char_y, value);
    }
    return value;
}

void ST7735S::character(int x, int y, int c)
{
    unsigned int hor, vert, offset, bpl;
    unsigned char* ch;
    unsigned char z, w;

    if ((c < 31) || (c > 127)) return;   // test char range

    // read font parameter from start of array
    offset = _font[0];  // bytes / char
    hor = _font[1];     // get hor size of font
    vert = _font[2];    // get vert size of font
    bpl = _font[3];     // bytes per line

    if (char_x + hor > (unsigned int)_width) {
        char_x = 0;
        char_y = char_y + vert;
        if (char_y >= _height - (unsigned int)_font[2]) {
            char_y = 0;
        }
    }

    window(char_x, char_y, char_x + hor - 1, char_y + vert - 1); // char box
    _rs = 1;
    _cs = 0;
    ch = &_font[((c -32) * offset) + 4];   // start of char bitmap
    w = ch[0];                                  // width of actual char
    for (unsigned int j = 0; j < vert; j++) {            //  vert line
        for (unsigned int i = 0; i < hor; i++) {         //  horz line
            z =  ch[bpl * i + ((j & 0xF8) >> 3) + 1];
            if (( z & (1 << (j & 0x07)) ) == 0x00) {
                _spi.write(_background >> 8);
                _spi.write(_background);
            } else {
                _spi.write(_foreground >> 8);
                _spi.write(_foreground);
            }
        }
    }
    _cs = 1;

    if (((unsigned int)w + 2) < hor) {      // x offset to next char
        char_x += (w + 2);
    } else {
        char_x += hor;
    }
}

void ST7735S::set_font(unsigned char* f)
{
    _font = f;
}

void ST7735S::Paint_DrawImage(const unsigned char *image, uint16_t xStart, uint16_t yStart, uint16_t W_Image, uint16_t H_Image)
{
    window(xStart, yStart, xStart + W_Image - 1, yStart + H_Image - 1);
    _rs = 1;
    _cs = 0;
    for(int j = 0; j < H_Image; j++) {
        int offset = (j * W_Image * 2);
        for (int i = 0; i < (W_Image * 2); i+=2) {
            _spi.write(*(image + offset + i + 1));
            _spi.write(*(image + offset + i));
        }
    }
    _cs = 1;
}
