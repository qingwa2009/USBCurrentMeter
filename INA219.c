#include "INA219.h"
#include <Arduino.h>

uint16_t _readReg(uint8_t addr)
{
    uint8_t buf[2];
    TWIMasterSyncStart(I2C_ADDR_INA219, TWI_WRITE_MODE);
    TWIMasterSyncWriteByteWaitAck(addr);
    TWIMasterSyncStart(I2C_ADDR_INA219, TWI_READ_MODE);
    TWIMasterSyncReadByteWaitAck(&buf[0], 0);
    TWIMasterSyncReadByteWaitAck(&buf[1], 1);
    TWIMasterSyncStop();
    return ((uint16_t)buf[0] << 8) + buf[1];
}

void _writeReg(uint8_t addr, uint16_t data)
{
    TWIMasterSyncStart(I2C_ADDR_INA219, TWI_WRITE_MODE);
    TWIMasterSyncWriteByteWaitAck(addr);
    TWIMasterSyncWriteByteWaitAck((uint8_t)(data >> 8));
    TWIMasterSyncWriteByteWaitAck((uint8_t)data);
    TWIMasterSyncStop();
}
void INA219_Reset()
{
    struct INA219_Config config = INA219_ReadConfig();
    config.rst = 1;
    INA219_WriteConfig(config);
}

void INA219_Init()
{
    INA219_Reset();
}

/**
 * 使用16v量程 0.1Ohm 1W采样电阻 连续采样模式
 * return curPerBit
 * curPerBit 在 INA219_ReadValueF 调用中要用到
*/
float INA219_MyDefaultConfig()
{
    float R = 0.1;

    //最大采集电压 Umax=sqrt(采样电阻功率*采样电阻阻值)=sqrt(1*0.1)=316.23mv 取最大电压量程+-320.00mv，
    //最大电流量程 Imax=0.320/0.1=3.2A
    //电流最小分辨率 Imin=3.2/2^15=0.00009765625A
    //校准值cal=0.04096*2^15/0.32=4194
    INA219_WriteCalibration(4194);
    uint16_t cal = INA219_ReadCalibration();
    float curPerBit = 0.04096f / (cal * R);

    struct INA219_Config config =
        {
            //pga Range ±320 mV 最低位0.01mv
            .pg0 = 1,
            .pg1 = 1,
            //bus range 16v 最低位4mv
            .brng = 0,
            //连续采样模式
            .mode1 = 1,
            .mode2 = 1,
            .mode3 = 1,
            //adc 12bit采样分辨率
            .sadc1 = 1,
            .sadc2 = 1,
            .sadc3 = 0,
            .sadc4 = 0,
            .badc1 = 1,
            .badc2 = 1,
            .badc3 = 0,
            .badc4 = 0,
        };
    INA219_WriteConfig(config);

    return curPerBit;
}
struct INA219_Config INA219_ReadConfig()
{
    uint16_t v = _readReg(INA219_CONFIG_REG);
    return *(struct INA219_Config *)&v;
}

void INA219_WriteConfig(struct INA219_Config config)
{
    _writeReg(INA219_CONFIG_REG, *(uint16_t *)&config);
}

uint16_t INA219_ReadCalibration()
{
    return _readReg(INA219_CALIBRATION_REG);
}

void INA219_WriteCalibration(uint16_t Calibration)
{
    _writeReg(INA219_CALIBRATION_REG, Calibration);
}
bool INA219_ReadValue(uint16_t *busValue, uint16_t *shuntValue, uint16_t *powValue, uint16_t *currentValue)
{
    uint16_t v;
    while (1)
    {
        v = _readReg(INA219_BUS_REG);
        if ((v & 0b1) == 1)
            return false; //overflow
        else if ((v >> 1) & 0b1)
            break;
    }
    *busValue = v >> 3;
    *shuntValue = _readReg(INA219_SHUNT_REG);
    *currentValue = _readReg(INA219_CURRENT_REG);
    *powValue = _readReg(INA219_POWER_REG);
    return true;
}
/**
 * curPerBit=0.04096/(calibration*R)
 * 
*/
bool INA219_ReadValueF(float curPerBit, float *busV, float *shuntV, float *pow, float *current)
{
    uint16_t b, s, p, c;
    if (!INA219_ReadValue(&b, &s, &p, &c))
        return false;
    *busV = ((int16_t)b) * 0.004f;
    *shuntV = ((int16_t)s) * 0.00001f;
    *current = curPerBit * (int16_t)c;
    *pow = 20 * curPerBit * (int16_t)p;
    return true;
}