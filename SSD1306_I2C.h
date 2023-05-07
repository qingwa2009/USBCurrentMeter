#include "SSD1306.h"
#include "MyTWI.h"

#define CMD 0x00
#define DATA 0x40

#define SSD1306_I2C_ADDRESS SSD1306_I2C_ADDR

void _writeCmd(uint8_t cmd)
{
    TWIMasterSyncStart(SSD1306_I2C_ADDRESS, TWI_WRITE_MODE);
    TWIMasterSyncWriteByteWaitAck(CMD);
    TWIMasterSyncWriteByteWaitAck(cmd);
    TWIMasterSyncStop();
}

void _writeData8(uint8_t data)
{
    TWIMasterSyncStart(SSD1306_I2C_ADDRESS, TWI_WRITE_MODE);
    TWIMasterSyncWriteByteWaitAck(DATA);
    TWIMasterSyncWriteByteWaitAck(data);
    TWIMasterSyncStop();
}

inline void _INIT()
{
}

#define _BEFORE_DISPLAY \
    TWISaveFrequency(); \
    TWISetFrequency(SSD1306_I2C_FREQUENCY)

#define _START_DISPLAY \
    TWIMasterSyncStart(SSD1306_I2C_ADDRESS, TWI_WRITE_MODE)

#define _DATA_MODE_DISPLAY \
    TWIMasterSyncWriteByte(DATA)

#define _SEND_DISPLAY(x)         \
    TWIMasterSyncWriteWaitAck(); \
    TWIMasterSyncWriteByte(x)

#define _WAIT_SEND_DISPLAY \
    TWIMasterSyncWriteWaitAck()

#define _STOP_DISPLAY \
    TWIMasterSyncStop()

#define _AFTER_DISPLAY \
    TWIRestoreFrequency()
