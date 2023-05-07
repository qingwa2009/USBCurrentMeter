#ifndef _MY_TWI_H
#define _MY_TWI_H
#include <Arduino.h>

//ack：i want more; i have more;
//nack：i don't want more; i dont have more

#define TWI_STA_OK 0x08       /*start sended*/
#define TWI_RSTA_OK 0x10      /*repeated start sended*/
#define TWI_MT_SLAW_ACK 0x18  /*SLA+W sended and ack recved*/
#define TWI_MT_SLAW_NACK 0x20 /*SLA+W sended and nack recved*/
#define TWI_MT_DATA_ACK 0x28  /*data sended and ack recved*/
#define TWI_MT_DATA_NACK 0x30 /*data sended and nack recved*/
#define TWI_ARB_LOST 0x38     /*ARB lost*/
#define TWI_MR_SLAR_ACK 0x40  /*SLA+R sended and ack recved*/
#define TWI_MR_SLAR_NACK 0x48 /*SLA+R sended and nack recved*/
#define TWI_MR_DATA_ACK 0x50  /*data recved and ack sended*/
#define TWI_MR_DATA_NACK 0x58 /*data recved and nack sended*/

#define TWI_SR_SLAW_ACK 0x60           /*being addressed and ack sended*/
#define TWI_SR_ARB_LOST_SLAW_ACK 0x68  /*ARB lost as master and being addressed and ack sended*/
#define TWI_SR_GCALL_ACK 0x70          /*being general called and ack sended*/
#define TWI_SR_ARB_LOST_GCAL_ACK 0x78  /*ARB lost as master and general called and ack sended*/
#define TWI_SR_ADDR_DATA_ACK 0x80      /*data recved from addressed and ack sended */
#define TWI_SR_ADDR_DATA_NACK 0x88     /*data recved from addressed and nack sended*/
#define TWI_SR_GCALL_DATA_ACK 0x90     /*data recved from general called and ack sended*/
#define TWI_SR_GCALL_DATA_NACK 0x98    /*data recved from general called and nack sended*/
#define TWI_SR_RECV_STOP_OR_RESTA 0xA0 /*recved master stop or repeated start condition*/

#define TWI_ST_SLAR_ACK 0xA8          /*being addressed and ack sended*/
#define TWI_ST_ARB_LOST_SLAR_ACK 0xB0 /*ARB lost as master and being addressed and ack sended*/
#define TWI_ST_DATA_ACK 0xB8          /*data sended and ack recved*/
#define TWI_ST_DATA_NACK 0xC0         /*data sended and nack recved*/
#define TWI_ST_LAST_DATA_ACK 0xC8     /*last data sended and ack recved*/

#define TWI_MS_NO_STATUS 0xF8 /*TWI is runing and have not finished yet, TWI interrupt is not set*/
#define TWI_MS_BUS_ERROR 0x00 /*Bus error, occurs when a START or STOP condition occurs at an illegal position in the format frame */

#define TWI_STATE_FREE 0x00    /*空闲*/
#define TWI_STATE_HANG_ON 0xFF /*挂起，霸占bus*/
#define TWI_STATE_SENDING_START 0x01
#define TWI_STATE_SENDING_REPEAT_START 0x03
#define TWI_STATE_SENDING_SLA_W 0x04
#define TWI_STATE_SENDING_SLA_R 0x05
#define TWI_STATE_SENDING_DATA 0x06
#define TWI_STATE_READING_DATA 0x07
#define TWI_STATE_SENDING_STOP 0x0F

#define TWI_STATE_SLAVE_RECVING 0x10

#define TWI_ERR_OK 0x00
#define TWI_ERR_START_FAILED 0x01
#define TWI_ERR_RESTART_FAILED 0x02
#define TWI_ERR_STATE_NO_FREE 0xFF

#define TWI_ERR_SLAW_NACK TWI_MT_SLAW_NACK
#define TWI_ERR_DATA_NACK TWI_MT_DATA_NACK
#define TWI_ERR_ARB_LOST TWI_ARB_LOST
#define TWI_ERR_SLAR_NACK TWI_MR_SLAR_NACK

#define TWI_ERR_SLAR_RECV_STOP TWI_SR_RECV_STOP_OR_RESTA

#define TWI_MODE_MT 0x00
#define TWI_MODE_MR 0x01
#define TWI_MODE_ST 0x02
#define TWI_MODE_SR 0x03

// #define bool char

#ifdef __cplusplus
extern "C"
{
#endif
    /*read 1 write 0*/
    enum TWIReadWriteMode
    {
        TWI_WRITE_MODE = 0,
        TWI_READ_MODE = 1
    };

    void initMyTWI(uint32_t frequency);
    void TWISetFrequency(uint32_t f);
    void TWISaveFrequency();
    void TWIRestoreFrequency();

    // void TWISetAddr(uint8_t addr, uint8_t enableGeneralCall, uint8_t addrMask);

    bool TWIMasterSyncStart(uint8_t addr, enum TWIReadWriteMode mode);
    void TWIMasterSyncStop();
    void TWIMasterSyncWriteByte(uint8_t data);
    bool TWIMasterSyncWriteWaitAck();
    bool TWIMasterSyncWriteByteWaitAck(uint8_t data);
    void TWIMasterSyncReadRequest(bool finalRead);
    bool TWIMasterSyncReadByte(uint8_t *data);
    bool TWIMasterSyncReadByteWaitAck(uint8_t *data, bool finalRead);
    void TWIMasterSyncRead(uint8_t *buf, uint16_t len);
    void TWIMasterSyncWrite(uint8_t *data, uint16_t len);

    void TWIAttachSlaveRecvEvent(void (*slaveRecvEv)(bool isGeneralCall, bool isFromARBLost));
    uint16_t TWISlaveRecvSync(uint8_t *buf, uint16_t len);
    void TWIAttachSlaveSendEvent(void (*slaveSendEv)(bool isFromARBLost));
    uint16_t TWISlaveSendSync(uint8_t *buf, uint16_t len);

    void TWIScanDevices();
#ifdef __cplusplus
}
#endif

#endif