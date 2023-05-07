#include <Arduino.h>
#include <avr/eeprom.h>
#include "MyPin.h"
#include "MyTWI.h"
#include "INA219.h"
#include "SSD1306.h"
// #define DEBUG

#ifdef DEBUG
/*Serial.print(...)*/
#define DBG(...) Serial.print(__VA_ARGS__)
/*Serial.println(...)*/
#define DBG_L(...) Serial.println(__VA_ARGS__)
#else
#define DBG(...)
#define DBG_L(...)
#endif

float curPerBit;

#define ROW0_Y 0
#define ROW1_Y 8
#define ROW2_Y 16
#define ROW3_Y 24
#define MAX_CHAR_COLUMN 128 / 6

#define BIT_VAL(v, b) ((uint8_t)((v)&_BV(b))) >> (b)
#define PIN_b0 2
#define PIN_b1 3
#define SCAN_BTNS() (((~PIND) >> 2) & 0b11)
#define B0 0
#define B1 1

#define MAX_INDEX 2

unsigned long t0;
unsigned long st;
float ph = 0, ih = 0;

uint8_t mode;
uint8_t br;
uint8_t screenDir;
uint8_t preBtns;
int8_t index;

MySSD1306 lcd;

void reset()
{
    ph = 0;
    ih = 0;
    t0 = millis();
    st = t0;

    index = 0;
    preBtns = SCAN_BTNS();
    mode = 0;
}

void setup()
{
    // Serial.begin(250000);
    initMyTWI(400000);
    // TWIScanDevices();
    INA219_Init();
    lcd.init();
    curPerBit = INA219_MyDefaultConfig();
    MYPIN_READ_MODE_PULLUP(PIN_b0);
    MYPIN_READ_MODE_PULLUP(PIN_b1);
    // MCUCR &= ~(_BV(ISC11) | _BV(ISC10) | _BV(ISC01) | _BV(ISC00));
    // MCUCR |= _BV(ISC10) | _BV(ISC00);
    // GICR |= _BV(INT0) | _BV(INT1);

    // struct INA219_Config config;
    // config = INA219_ReadConfig();
    // uint16_t v = *(uint16_t *)&config;
    // uint8_t mode = (v >> 0) & 0b111;
    // uint8_t sadc = (v >> 3) & 0b1111;
    // uint8_t badc = (v >> 7) & 0b1111;
    // uint8_t pg = (v >> 11) & 0b11;
    // uint8_t brng = (v >> 13) & 0b1;

    // DBG("INA219 mode: ");
    // DBG_L(mode, BIN);
    // DBG("INA219 sadc: ");
    // DBG_L(sadc, BIN);
    // DBG("INA219 badc: ");
    // DBG_L(badc, BIN);
    // DBG("INA219 pg: ");
    // DBG_L(pg, BIN);
    // DBG("INA219 brng: ");
    // DBG_L(brng, BIN);

    // uint16_t cal = INA219_ReadCalibration();
    // DBG("INA219 calibration: ");
    // DBG_L(cal);
    screenDir = eeprom_read_byte(0);
    if (screenDir != 255)
        lcd.setScreenDir(screenDir);
    else
        screenDir = lcd.getScreenDir();

    br = eeprom_read_byte((uint8_t *)1);
    if (br != 255)
        lcd.setContrast(br);
    else
        br = lcd.getContrast();
    reset();
}

float convertUnit(float v, float precision, char *unit)
{

    if (v < precision && v > -precision)
    {
        *unit = ' ';
        return 0;
    }
    if (v < 0.001)
    {
        *unit = 'u';
        return v * 1E6;
    }
    if (v < 1)
    {
        *unit = 'm';
        return v * 1E3;
    }
    *unit = ' ';
    return v;
}
uint8_t animoffset;

void loop()
{
    animoffset++;
    animoffset %= 11;

    unsigned long t1 = millis();
    uint32_t dt = t1 - t0;
    float dth = ((float)dt / (1000.0 * 3600.0));

    // TWIScanDevices();
    // DBG_L("Hello World!");
    lcd.clear(0);

    float busValue, shuntValue, powValue, currentValue;
    if (INA219_ReadValueF(curPerBit, &busValue, &shuntValue, &powValue, &currentValue))
    {
        lcd.setCursor(0, 0);
        // lcd.print("Shunt V(mV): ");
        // lcd.println(shuntValue * 1000);
        // char sss[] = " mV: -000.00\r\n"
        //              " mA: -000.00\r\n"
        //              "mWh: -000.00\r\n"
        //              "mAh: -000.00\r\n";
        char unit;
        busValue = convertUnit(busValue, 0.001, &unit);
        lcd.print(' ');
        lcd.print(unit);
        lcd.print("V: ");
        lcd.println(busValue);

        ih += currentValue * dth;
        currentValue = convertUnit(currentValue, 0.000001, &unit);
        lcd.print(' ');
        lcd.print(unit);
        lcd.print("A: ");
        lcd.println(currentValue);

        ph += powValue * dth;
        powValue = convertUnit(ph, 0.000001, &unit);
        lcd.print(unit);
        lcd.print("Wh: ");
        lcd.println(powValue);

        powValue = convertUnit(ih, 0.000001, &unit);
        lcd.print(unit);
        lcd.print("Ah: ");
        lcd.println(powValue);

        char ss[] = "00:00:00";
        unsigned long ttt = (t1 - st) / 1000;
        uint8_t tttt = (ttt / 3600); // % 24;
        ss[0] = '0' + tttt / 10;
        ss[1] = '0' + tttt % 10;
        tttt = (ttt / 60) % 60;
        ss[3] = '0' + tttt / 10;
        ss[4] = '0' + tttt % 10;
        tttt = ttt % 60;
        ss[6] = '0' + tttt / 10;
        ss[7] = '0' + tttt % 10;
        lcd.setCursor(13, 0);
        lcd.print(ss);

        t0 = t1;
    }
    else
    {
        // lcd.println("Measure overflow!");
    }

    uint8_t btns = SCAN_BTNS();
    if (btns != preBtns)
    {
        if (btns == 0b11)
        {
            switch (index)
            {
            case 0:
                reset();
                break;
            case 1:
                if (screenDir)
                {
                    screenDir = 0;
                    lcd.setScreenDir(0);
                    eeprom_write_byte(0, 0);
                }
                else
                {
                    screenDir = 2;
                    lcd.setScreenDir(2);
                    eeprom_write_byte(0, 2);
                }
                break;
            case 2:
                mode = !mode;
                if (mode == 0)
                    eeprom_write_byte((uint8_t *)1, br);
                break;
            default:
                break;
            }
        }
        else if (mode == 0 && preBtns == 0b01 && (!(btns & 0b01)))
        {
            if (screenDir == 0)
            {
                index++;
                if (index > MAX_INDEX)
                    index = MAX_INDEX;
            }
            else
            {
                index--;
                if (index < 0)
                    index = 0;
            }
        }
        else if (mode == 0 && preBtns == 0b10 && (!(btns & 0b10)))
        {
            if (screenDir == 2)
            {
                index++;
                if (index > MAX_INDEX)
                    index = MAX_INDEX;
            }
            else
            {
                index--;
                if (index < 0)
                    index = 0;
            }
        }
        preBtns = btns;
    }
    else if (mode == 1)
    {
        if ((btns == 0b01 && screenDir == 0) || (btns == 0b10 && screenDir == 2))
        {
            br++;
            if (br > 254)
                br = 254;
            lcd.setContrast(br);
        }
        else if ((btns == 0b10 && screenDir == 0) || (btns == 0b01 && screenDir == 2))
        {
            br--;
            if (br < 1)
                br = 1;
            lcd.setContrast(br);
        }
    }

    if (mode == 0)
    {
        lcd.setCursor(13, index + 1);
        lcd.print((char)animoffset);
    }
    uint8_t xx[] = {13, 13, 13};
    xx[index] = 14;
    lcd.setCursor(xx[0], 1);
    lcd.print("Reset");
    lcd.setCursor(xx[1], 2);
    lcd.print("Rotate");
    lcd.setCursor(xx[2], 3);
    lcd.print("\x0f:");
    if (mode == 1)
        lcd.print((char)25);
    lcd.print(br);
    if (mode == 1)
        lcd.print((char)24);

    lcd.display();
    // delay(10);
}