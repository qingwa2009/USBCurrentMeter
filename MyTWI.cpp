#include "MyTWI.h"
// #include "SerialC.h"

// #undef DEBUG
#ifdef DEBUG
/*Serial.print(...)*/
#define DBG(...) Serial.print(__VA_ARGS__)
/*Serial.println(...)*/
#define DBG_L(...) Serial.println(__VA_ARGS__)
#else
#define DBG(...)
#define DBG_L(...)
#endif

#define TWI_STATUS (TWSR & 0b11111000)

#define _TWI_INTERRUPT_DISABLE() (TWCR &= ~(_BV(TWINT) | _BV(TWIE)))

/*开始发送*/
#define _MASTER_SEND(data)             \
    do                                 \
    {                                  \
        TWDR = (data);                 \
        TWCR = _BV(TWINT) | _BV(TWEN); \
    } while (0);

#define _SLAVE_SEND(data)                            \
    do                                               \
    {                                                \
        TWDR = (data);                               \
        TWCR = (_BV(TWINT) | _BV(TWEA) | _BV(TWEN)); \
    } while (0);

#define _SLAVE_SEND_LAST_INTERRUPT(data)             \
    do                                               \
    {                                                \
        TWDR = (data);                               \
        TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWIE)); \
    } while (0);

#define _REPLY_NEXT_ACK \
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN);

#define _REPLY_NEXT_NACK \
    TWCR = _BV(TWINT) | _BV(TWEN);

#define _REPLY_NEXT_NACK_INTERRUPT \
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE);

#define _REPLY(ack) \
    TWCR = (ack) ? (_BV(TWINT) | _BV(TWEA) | _BV(TWEN)) : (_BV(TWINT) | _BV(TWEN));

#define _SEND_START \
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);

#define _SEND_STOP \
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

#define _MASTER_RECV_REQUEST(finalRecv) \
    _REPLY(!(finalRecv));

#define _SLAVE_PENDING \
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE); /*使能应答，使能TWI，使能中断*/

/*等待停止执行结束*/
#define _WAIT_FOR_STOP()      \
    while (TWCR & _BV(TWSTO)) \
        ;

#ifdef DEBUG
#define _WAIT_TWI(errMsg) \
    if (_waitOrTimeout()) \
        DBG_L(errMsg);
#else
#define _WAIT_TWI(errMsg)            \
    while (!bit_is_set(TWCR, TWINT)) \
        ;
#endif

bool _waitOrTimeout()
{
    uint32_t t0 = millis();
    uint32_t tt = 200;
    while (!bit_is_set(TWCR, TWINT))
    {
        if (millis() - t0 > tt)
            return true;
    }
    return false;
}

void initMyTWI(uint32_t frequency)
{
    TWISetFrequency(frequency);
    DBG_L("initMyTWI...");
    // TWCR = _BV(TWEA) | _BV(TWEN) | _BV(TWIE); /*使能应答，使能TWI，使能中断*/
}

/*SLC_F=CPU_CLK/(16+2*bitRate*prescale) 最大1MHz 最小490Hz*/
void TWISetFrequency(uint32_t f)
{
    if (f > 30418)
    {
        TWSR &= ~(_BV(TWPS1) | _BV(TWPS0)); /*prescale 1*/
        TWBR = (F_CPU / f - 16) / 2 / 1;
    }
    else if (f > 7782)
    {
        TWSR &= ~(_BV(TWPS1) | _BV(TWPS0)); /*prescale 1/4*/
        TWSR |= _BV(TWPS0);
        TWBR = (F_CPU / f - 16) / 2 / 4;
    }
    else if (f > 1956)
    {
        TWSR &= ~(_BV(TWPS1) | _BV(TWPS0)); /*prescale 1/16*/
        TWSR |= _BV(TWPS1);
        TWBR = (F_CPU / f - 16) / 2 / 16;
    }
    else
    {
        // TWSR &= ~(_BV(TWPS1) | _BV(TWPS0));
        TWSR |= _BV(TWPS1) | _BV(TWPS0); /*prescale 1/64*/
        TWBR = (F_CPU / f - 16) / 2 / 64;
    }
}

static uint8_t _twbr;
void TWISaveFrequency()
{
    _twbr = TWBR;
}

void TWIRestoreFrequency()
{
    TWBR = _twbr;
}

void _masterSendData(uint8_t data);
void _masterSendSLAW();
void _masterSendStart();
void _masterSendSLAR();
void _masterRecvData(uint8_t finalRecv);

/*轮询模式发送开始read 1 write 0，开始失败会调用stop*/
bool TWIMasterSyncStart(uint8_t addr, enum TWIReadWriteMode mode)
{

    _SEND_START

    _WAIT_TWI(F("TWIMasterSyncStart timeout 1!!!"))

    uint8_t status = TWI_STATUS;
    if (status == TWI_STA_OK || status == TWI_RSTA_OK)
    {
        _MASTER_SEND(mode ? ((addr << 1) | 1) : (addr << 1))
        _WAIT_TWI(F("TWIMasterSyncStart timeout 2!!!"))

        status = TWI_STATUS;
        if (status == TWI_MT_SLAW_ACK || status == TWI_MR_SLAR_ACK)
        {
            return 1;
        }
    }
    TWIMasterSyncStop();

    return 0;
}

/*轮询模式发送数据，调用完记得调用TWIMasterSyncWriteWaitAck等待应答结果*/
void TWIMasterSyncWriteByte(uint8_t data)
{
    _MASTER_SEND(data)
}

/*轮询模式等待应答，与TWIMasterSyncWriteByte配合使用*/
bool TWIMasterSyncWriteWaitAck()
{
    _WAIT_TWI(F("TWIMasterSyncWriteWaitAck timeout!!!"))

    return (TWI_STATUS == TWI_MT_DATA_ACK);
}

/*轮询模式发送数据，会等待应答*/
bool TWIMasterSyncWriteByteWaitAck(uint8_t data)
{
    _MASTER_SEND(data)
    _WAIT_TWI(F("TWIMasterSyncWriteByteWaitAck timeout!!!"))

    return (TWI_STATUS == TWI_MT_DATA_ACK);
}

/*轮询模式高速发送数据*/
void TWIMasterSyncWrite(uint8_t *data, uint16_t len)
{
    TWIMasterSyncWriteByte(data[0]);
    uint16_t i;
    for (i = 1; i < len; i++)
    {
        TWIMasterSyncWriteWaitAck();
        TWIMasterSyncWriteByte(data[i]);
    }
    TWIMasterSyncWriteWaitAck();
}

/*轮询模式发起读请求，调用完记得调用TWIMasterSyncReadByte等待应答结果*/
void TWIMasterSyncReadRequest(bool finalRead)
{
    _MASTER_RECV_REQUEST(finalRead)
}

/*轮询模式等待读取结果，与TWIMasterSyncReadByte配合使用*/
bool TWIMasterSyncReadByte(uint8_t *data)
{
    _WAIT_TWI(F("TWIMasterSyncReadByte!!!"))

    uint8_t status = TWI_STATUS;
    if (status == TWI_MR_DATA_ACK || status == TWI_MR_DATA_NACK)
    {
        *data = TWDR;
        return 1;
    }
    return 0;
}

/*轮询模式读取数据，会等待数据；*/
bool TWIMasterSyncReadByteWaitAck(uint8_t *data, bool finalRead)
{
    _MASTER_RECV_REQUEST(finalRead)
    _WAIT_TWI(F("TWIMasterSyncReadByteWaitAck timeout!!!"))
    uint8_t status = TWI_STATUS;
    if (status == TWI_MR_DATA_ACK || status == TWI_MR_DATA_NACK)
    {
        *data = TWDR;
        return 1;
    }
    return 0;
}

/*轮询模式高速读取数据*/
void TWIMasterSyncRead(uint8_t *buf, uint16_t len)
{
    TWIMasterSyncReadRequest(len == 1);
    uint16_t i;
    for (i = 1; i < len; i++)
    {
        TWIMasterSyncReadByte(buf);
        TWIMasterSyncReadRequest(i == len - 1);
        buf++;
    }
    TWIMasterSyncReadByte(buf);
}

/*轮询模式发送停止*/
void TWIMasterSyncStop()
{
    _SEND_STOP
    _WAIT_FOR_STOP()
}

/*设置作为从机时的地址；
addrMask：对应地址位掩码，对应位为1将忽略检查该位，默认0所有地址位必须一致；
*/
// void TWISetAddr(uint8_t addr, uint8_t enableGeneralCall, uint8_t addrMask)
// {
//     TWAR = ((addr << 1) | (enableGeneralCall ? 1 : 0));
//     TWAMR = addrMask;
// }

static void (*_slaveRecvEv)(bool isGeneralCall, bool isFromARBLost) = 0;
static void (*_slaveSendEv)(bool isFromARBLost) = 0;

ISR(TWI_vect)
{

    uint8_t status = TWI_STATUS;
    struct SS
    {
        uint8_t noused1 : 3;
        uint8_t isFromARBLost : 1;
        uint8_t isGeneralCall : 1;
        uint8_t noused2 : 3;
    } *s = (struct SS *)&status;
    switch (status)
    {
    case TWI_SR_SLAW_ACK:          /*011 00 000*/
    case TWI_SR_ARB_LOST_SLAW_ACK: /*011 01 000*/
    case TWI_SR_GCALL_ACK:         /*011 10 000*/
    case TWI_SR_ARB_LOST_GCAL_ACK: /*011 11 000*/
        if (_slaveRecvEv)
        {
            _slaveRecvEv(s->isGeneralCall, s->isFromARBLost);
            break;
        }
    case TWI_ST_SLAR_ACK:          /*1010 1000*/
    case TWI_ST_ARB_LOST_SLAR_ACK: /*1011 0000*/
        if (_slaveSendEv)
        {
            _slaveSendEv(s->isGeneralCall);
            break;
        }
    default:
        _SLAVE_PENDING
        break;
    }
}

void TWIAttachSlaveRecvEvent(void (*slaveRecvEv)(bool isGeneralCall, bool isFromARBLost))
{
    _slaveRecvEv = slaveRecvEv;
    _SLAVE_PENDING
}

/*必须在SlaveRecvEc事件中调用*/
uint16_t TWISlaveRecvSync(uint8_t *buf, uint16_t len)
{
    _REPLY_NEXT_ACK
    uint16_t i = 0;
    len--;
    for (; i < len; i++)
    {

        _WAIT_TWI(F("TWISlaveRecvSync timeout 1!!!"))

        if (TWI_STATUS == TWI_SR_RECV_STOP_OR_RESTA)
        {
            _SLAVE_PENDING
            return i;
        }
        buf[i] = TWDR;

        _REPLY_NEXT_ACK
    }

    _WAIT_TWI(F("TWISlaveRecvSync timeout 2!!!"))

    if (TWI_STATUS == TWI_SR_RECV_STOP_OR_RESTA)
    {
        _SLAVE_PENDING
        return i;
    }
    buf[i] = TWDR;

    _REPLY_NEXT_NACK_INTERRUPT
    return i + 1;
}

void TWIAttachSlaveSendEvent(void (*slaveSendEv)(bool isFromARBLost))
{
    _slaveSendEv = slaveSendEv;
    _SLAVE_PENDING
}

/*必须在SlaveSendEv事件中调用*/
uint16_t TWISlaveSendSync(uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;

    if (len > 1)
    {
        _SLAVE_SEND(buf[i]);
        i++;
        len--;
        for (; i < len; i++)
        {
            _WAIT_TWI(F("TWISlaveSendSync timeout 1!!!"))

            if (TWI_STATUS != TWI_ST_DATA_ACK)
            {
                _SLAVE_PENDING
                return i;
            }
            _SLAVE_SEND(buf[i]);
        }
        _WAIT_TWI(F("TWISlaveSendSync timeout 2!!!"))
        if (TWI_STATUS != TWI_ST_DATA_ACK)
        {
            _SLAVE_PENDING
            return i;
        }
    }

    _SLAVE_SEND_LAST_INTERRUPT(buf[i]);

    return i + 1;
}
/*扫描i2c设备，输出到串口*/
void TWIScanDevices()
{
    Serial.println(F("Scanning i2c devices..."));
    uint16_t i;
    for (i = 1; i < 128; i++)
    {
        if (TWIMasterSyncStart(i, TWI_WRITE_MODE))
        {
            Serial.print("addr: ");
            Serial.print(i, HEX);
            Serial.println("    OK!");
            TWIMasterSyncStop();
        }
    }
    Serial.println(F("search finished!"));
}