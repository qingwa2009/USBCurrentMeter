#ifndef __SSD1306_H
#define __SSD1306_H

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_I2C_FREQUENCY 400000

#define SSD1306_LCD_WIDTH 128
#define SSD1306_LCD_HEIGHT 32

#define SSD1306_LCD_MAX_X (SSD1306_LCD_WIDTH - 1)
#define SSD1306_LCD_MAX_Y (SSD1306_LCD_HEIGHT - 1)

#define SSD1306_BUFFER_SIZE (SSD1306_LCD_WIDTH * SSD1306_LCD_HEIGHT / 8)

#define CMD_NOP 0xE3
#define CMD_DISPLAY_ON 0xAF
#define CMD_DISPLAY_OFF 0xAE
#define CMD_SET_COL_ADDR 0x21
#define CMD_SET_PAGE_ADDR 0x22
#define CMD_SET_CONTRAST 0x81

#define FONT_W 5
#define FONT_H 7

#define MAX_CURSOR_X ((SSD1306_LCD_WIDTH / (FONT_W + 1)) - 1)
#define MAX_CURSOR_Y ((SSD1306_LCD_HEIGHT / (FONT_H + 1)) - 1)

#define CURSORX_TO_X(x) ((FONT_W + 1) * (x))
#define CURSORY_TO_Y(y) ((FONT_H + 1) * (y))

extern int16_t SCREEN_W;
extern int16_t SCREEN_H;
extern int16_t SCREEN_MAX_X;
extern int16_t SCREEN_MAX_Y;

enum Color
{
    WHITE,
    BLACK,
    INVERSE
};

void _INIT();

#ifdef __cplusplus
extern "C"
{
#endif
#include "Print.h"
    class MySSD1306 : public Print
    {
    private:
        uint8_t cursorX = 0;
        uint8_t cursorY = 0;
        void printChar(uint8_t c, enum Color color);

    public:
        void init();
        void clear(uint8_t c);
        void setScreenDir(uint8_t dir);
        uint8_t getScreenDir();
        void display();
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, enum Color color);
        void drawPixel(int16_t x, int16_t y, enum Color color);
        uint8_t *getDrawBuffer();
        void drawHorizontalLine(int16_t x, int16_t y, int16_t length, enum Color color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t length, enum Color color);
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, enum Color color);
        void drawChar(int16_t x, int16_t y, uint8_t c, int8_t scale, enum Color color);
        void drawStr(int16_t x, int16_t y, uint8_t *s, int16_t count, int8_t scale, enum Color color);
        void inverseDisplay(uint8_t inverse);
        void whiteScreen(uint8_t on);
        void displayON(uint8_t on);
        void setContrast(uint8_t v);
        uint8_t getContrast();
        void setCursorX(uint8_t x);
        void setCursorY(uint8_t y);
        void setCursor(uint8_t x, uint8_t y);
        virtual size_t write(uint8_t c);
    };
#ifdef __cplusplus
}
#endif

#endif