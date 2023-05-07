#ifndef __INA219_H
#define __INA219_H
#include "MyTWI.h"
#define I2C_ADDR_INA219 0x40
#define INA219_CONFIG_REG 0x00
#define INA219_SHUNT_REG 0x01
#define INA219_BUS_REG 0x02 //BD12 BD11 BD10 BD9 BD8 BD7 BD6 BD5 BD4 BD3 BD2 BD1 BD0 — CNVR OVF
#define INA219_POWER_REG 0x03
#define INA219_CURRENT_REG 0x04
#define INA219_CALIBRATION_REG 0x05

struct INA219_Config
{
    uint8_t mode1 : 1;    //defalut 1 Selects continuous, triggered, or power-down mode of operation. 0:Power-down; 1:Shunt voltage, triggered; 2:Bus voltage, triggered; 3:Shunt and bus, triggered; 4:ADC off (disabled); 5:Shunt voltage, continuous; 6:Bus voltage, continuous; 7: Shunt and bus, continuous
    uint8_t mode2 : 1;    //defalut 1
    uint8_t mode3 : 1;    //defalut 1
    uint8_t sadc1 : 1;    //defalut 1 These bits adjust the Shunt ADC resolution (9-, 10-, 11-, or 12-bit) or set the number of samples used when averaging results for the Shunt Voltage Register (01h).
    uint8_t sadc2 : 1;    //defalut 1
    uint8_t sadc3 : 1;    //defalut 0
    uint8_t sadc4 : 1;    //defalut 0
    uint8_t badc1 : 1;    //defalut 1 These bits adjust the Bus ADC resolution (9-, 10-, 11-, or 12-bit) or set the number of samples used when averaging results for the Bus Voltage Register (02h).
    uint8_t badc2 : 1;    //defalut 1
    uint8_t badc3 : 1;    //defalut 0
    uint8_t badc4 : 1;    //defalut 0
    uint8_t pg0 : 1;      //defalut 1 PGA (Shunt Voltage Only) Sets PGA gain and range. 0 ±40mV, 1 ±80mV, 2 ±160mV, 3 ±320 mV
    uint8_t pg1 : 1;      //defalut 1 PGA (Shunt Voltage Only) Sets PGA gain and range. 0 ±40mV, 1 ±80mV, 2 ±160mV, 3 ±320 mV
    uint8_t brng : 1;     //defalut 1 Bus Voltage Range  0 = 16V 1 = 32V
    uint8_t reserved : 1; //defalut 0
    uint8_t rst : 1;      //defalut 0 Setting this bit to '1' generates a system reset that is the same as power-on reset. Resets all registers to default values; this bit self-clears.
};

#ifdef __cplusplus
extern "C"
{
#endif
    void INA219_Init();
    struct INA219_Config INA219_ReadConfig();
    void INA219_WriteConfig(struct INA219_Config config);
    uint16_t INA219_ReadCalibration();
    void INA219_WriteCalibration(uint16_t Calibration);
    bool INA219_ReadValue(uint16_t *busValue, uint16_t *ShuntValue, uint16_t *powValue, uint16_t *currentValue);
    bool INA219_ReadValueF(float curPerBit, float *busV, float *shuntV, float *pow, float *current);
    float INA219_MyDefaultConfig();
#ifdef __cplusplus
}
#endif

#endif