#ifndef __MYMYPIN_H
#define __MYMYPIN_H
#include <Arduino.h>
/*D----------------------------------------------*/
#define MYPIN_0_WRITE_MODE (DDRD |= _BV(DDD0))
#define MYPIN_1_WRITE_MODE (DDRD |= _BV(DDD1))
#define MYPIN_2_WRITE_MODE (DDRD |= _BV(DDD2))
#define MYPIN_3_WRITE_MODE (DDRD |= _BV(DDD3))
#define MYPIN_4_WRITE_MODE (DDRD |= _BV(DDD4))
#define MYPIN_5_WRITE_MODE (DDRD |= _BV(DDD5))
#define MYPIN_6_WRITE_MODE (DDRD |= _BV(DDD6))
#define MYPIN_7_WRITE_MODE (DDRD |= _BV(DDD7))

#define MYPIN_0_WRITE_HIGH (PORTD |= _BV(PORTD0))
#define MYPIN_1_WRITE_HIGH (PORTD |= _BV(PORTD1))
#define MYPIN_2_WRITE_HIGH (PORTD |= _BV(PORTD2))
#define MYPIN_3_WRITE_HIGH (PORTD |= _BV(PORTD3))
#define MYPIN_4_WRITE_HIGH (PORTD |= _BV(PORTD4))
#define MYPIN_5_WRITE_HIGH (PORTD |= _BV(PORTD5))
#define MYPIN_6_WRITE_HIGH (PORTD |= _BV(PORTD6))
#define MYPIN_7_WRITE_HIGH (PORTD |= _BV(PORTD7))

#define MYPIN_0_WRITE_LOW (PORTD &= ~(_BV(PORTD0)))
#define MYPIN_1_WRITE_LOW (PORTD &= ~(_BV(PORTD1)))
#define MYPIN_2_WRITE_LOW (PORTD &= ~(_BV(PORTD2)))
#define MYPIN_3_WRITE_LOW (PORTD &= ~(_BV(PORTD3)))
#define MYPIN_4_WRITE_LOW (PORTD &= ~(_BV(PORTD4)))
#define MYPIN_5_WRITE_LOW (PORTD &= ~(_BV(PORTD5)))
#define MYPIN_6_WRITE_LOW (PORTD &= ~(_BV(PORTD6)))
#define MYPIN_7_WRITE_LOW (PORTD &= ~(_BV(PORTD7)))

#define MYPIN_0_READ_MODE (DDRD &= ~(_BV(DDD0)))
#define MYPIN_1_READ_MODE (DDRD &= ~(_BV(DDD1)))
#define MYPIN_2_READ_MODE (DDRD &= ~(_BV(DDD2)))
#define MYPIN_3_READ_MODE (DDRD &= ~(_BV(DDD3)))
#define MYPIN_4_READ_MODE (DDRD &= ~(_BV(DDD4)))
#define MYPIN_5_READ_MODE (DDRD &= ~(_BV(DDD5)))
#define MYPIN_6_READ_MODE (DDRD &= ~(_BV(DDD6)))
#define MYPIN_7_READ_MODE (DDRD &= ~(_BV(DDD7)))

#define MYPIN_0_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD0);    \
        DDRD &= ~(_BV(DDD0));    \
    } while (0)
#define MYPIN_1_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD1);    \
        DDRD &= ~(_BV(DDD1));    \
    } while (0)
#define MYPIN_2_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD2);    \
        DDRD &= ~(_BV(DDD2));    \
    } while (0)
#define MYPIN_3_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD3);    \
        DDRD &= ~(_BV(DDD3));    \
    } while (0)
#define MYPIN_4_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD4);    \
        DDRD &= ~(_BV(DDD4));    \
    } while (0)
#define MYPIN_5_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD5);    \
        DDRD &= ~(_BV(DDD5));    \
    } while (0)
#define MYPIN_6_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD6);    \
        DDRD &= ~(_BV(DDD6));    \
    } while (0)
#define MYPIN_7_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTD |= _BV(PORTD7);    \
        DDRD &= ~(_BV(DDD7));    \
    } while (0)

#define MYPIN_0_READ_HIGH ((PIND & (_BV(PIND0))) > 0)
#define MYPIN_1_READ_HIGH ((PIND & (_BV(PIND1))) > 0)
#define MYPIN_2_READ_HIGH ((PIND & (_BV(PIND2))) > 0)
#define MYPIN_3_READ_HIGH ((PIND & (_BV(PIND3))) > 0)
#define MYPIN_4_READ_HIGH ((PIND & (_BV(PIND4))) > 0)
#define MYPIN_5_READ_HIGH ((PIND & (_BV(PIND5))) > 0)
#define MYPIN_6_READ_HIGH ((PIND & (_BV(PIND6))) > 0)
#define MYPIN_7_READ_HIGH ((PIND & (_BV(PIND7))) > 0)

// #define MYPIN_0_WRITE_TOGGLE (PIND |= (_BV(PIND0)))
// #define MYPIN_1_WRITE_TOGGLE (PIND |= (_BV(PIND1)))
// #define MYPIN_2_WRITE_TOGGLE (PIND |= (_BV(PIND2)))
// #define MYPIN_3_WRITE_TOGGLE (PIND |= (_BV(PIND3)))
// #define MYPIN_4_WRITE_TOGGLE (PIND |= (_BV(PIND4)))
// #define MYPIN_5_WRITE_TOGGLE (PIND |= (_BV(PIND5)))
// #define MYPIN_6_WRITE_TOGGLE (PIND |= (_BV(PIND6)))
// #define MYPIN_7_WRITE_TOGGLE (PIND |= (_BV(PIND7)))

// #define MYPIN_0_PCINT_MASK1 (PCMSK2 |= _BV(PCINT16))
// #define MYPIN_1_PCINT_MASK1 (PCMSK2 |= _BV(PCINT17))
// #define MYPIN_2_PCINT_MASK1 (PCMSK2 |= _BV(PCINT18))
// #define MYPIN_3_PCINT_MASK1 (PCMSK2 |= _BV(PCINT19))
// #define MYPIN_4_PCINT_MASK1 (PCMSK2 |= _BV(PCINT20))
// #define MYPIN_5_PCINT_MASK1 (PCMSK2 |= _BV(PCINT21))
// #define MYPIN_6_PCINT_MASK1 (PCMSK2 |= _BV(PCINT22))
// #define MYPIN_7_PCINT_MASK1 (PCMSK2 |= _BV(PCINT23))

// #define MYPIN_0_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT16)))
// #define MYPIN_1_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT17)))
// #define MYPIN_2_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT18)))
// #define MYPIN_3_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT19)))
// #define MYPIN_4_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT20)))
// #define MYPIN_5_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT21)))
// #define MYPIN_6_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT22)))
// #define MYPIN_7_PCINT_MASK0 (PCMSK2 &= ~(_BV(PCINT23)))

// #define MYPIN_0_7_PCINT_ENABLE (PCICR |= _BV(PCIE2))
// #define MYPIN_0_7_PCINT_DISABLE (PCICR &= ~(_BV(PCIE2)))
/*B----------------------------------------------*/
#define MYPIN_8_WRITE_MODE (DDRB |= _BV(DDB0))
#define MYPIN_9_WRITE_MODE (DDRB |= _BV(DDB1))
#define MYPIN_10_WRITE_MODE (DDRB |= _BV(DDB2))
#define MYPIN_11_WRITE_MODE (DDRB |= _BV(DDB3))
#define MYPIN_12_WRITE_MODE (DDRB |= _BV(DDB4))
#define MYPIN_13_WRITE_MODE (DDRB |= _BV(DDB5))

#define MYPIN_8_WRITE_HIGH (PORTB |= _BV(PORTB0))
#define MYPIN_9_WRITE_HIGH (PORTB |= _BV(PORTB1))
#define MYPIN_10_WRITE_HIGH (PORTB |= _BV(PORTB2))
#define MYPIN_11_WRITE_HIGH (PORTB |= _BV(PORTB3))
#define MYPIN_12_WRITE_HIGH (PORTB |= _BV(PORTB4))
#define MYPIN_13_WRITE_HIGH (PORTB |= _BV(PORTB5))

#define MYPIN_8_WRITE_LOW (PORTB &= ~(_BV(PORTB0)))
#define MYPIN_9_WRITE_LOW (PORTB &= ~(_BV(PORTB1)))
#define MYPIN_10_WRITE_LOW (PORTB &= ~(_BV(PORTB2)))
#define MYPIN_11_WRITE_LOW (PORTB &= ~(_BV(PORTB3)))
#define MYPIN_12_WRITE_LOW (PORTB &= ~(_BV(PORTB4)))
#define MYPIN_13_WRITE_LOW (PORTB &= ~(_BV(PORTB5)))

#define MYPIN_8_READ_MODE (DDRB &= ~(_BV(DDB0)))
#define MYPIN_9_READ_MODE (DDRB &= ~(_BV(DDB1)))
#define MYPIN_10_READ_MODE (DDRB &= ~(_BV(DDB2)))
#define MYPIN_11_READ_MODE (DDRB &= ~(_BV(DDB3)))
#define MYPIN_12_READ_MODE (DDRB &= ~(_BV(DDB4)))
#define MYPIN_13_READ_MODE (DDRB &= ~(_BV(DDB5)))

#define MYPIN_8_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTB |= _BV(PORTB0);    \
        DDRB &= ~(_BV(DDB0));    \
    } while (0)
#define MYPIN_9_READ_MODE_PULLUP \
    do                           \
    {                            \
        PORTB |= _BV(PORTB1);    \
        DDRB &= ~(_BV(DDB1));    \
    } while (0)
#define MYPIN_10_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTB |= _BV(PORTB2);     \
        DDRB &= ~(_BV(DDB2));     \
    } while (0)
#define MYPIN_11_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTB |= _BV(PORTB3);     \
        DDRB &= ~(_BV(DDB3));     \
    } while (0)
#define MYPIN_12_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTB |= _BV(PORTB4);     \
        DDRB &= ~(_BV(DDB4));     \
    } while (0)
#define MYPIN_13_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTB |= _BV(PORTB5);     \
        DDRB &= ~(_BV(DDB5));     \
    } while (0)

#define MYPIN_8_READ_HIGH ((PINB & (_BV(PINB0))) > 0)
#define MYPIN_9_READ_HIGH ((PINB & (_BV(PINB1))) > 0)
#define MYPIN_10_READ_HIGH ((PINB & (_BV(PINB2))) > 0)
#define MYPIN_11_READ_HIGH ((PINB & (_BV(PINB3))) > 0)
#define MYPIN_12_READ_HIGH ((PINB & (_BV(PINB4))) > 0)
#define MYPIN_13_READ_HIGH ((PINB & (_BV(PINB5))) > 0)

// #define MYPIN_8_WRITE_TOGGLE (PINB |= (_BV(PINB0)))
// #define MYPIN_9_WRITE_TOGGLE (PINB |= (_BV(PINB1)))
// #define MYPIN_10_WRITE_TOGGLE (PINB |= (_BV(PINB2)))
// #define MYPIN_11_WRITE_TOGGLE (PINB |= (_BV(PINB3)))
// #define MYPIN_12_WRITE_TOGGLE (PINB |= (_BV(PINB4)))
// #define MYPIN_13_WRITE_TOGGLE (PINB |= (_BV(PINB5)))

// #define MYPIN_8_PCINT_MASK1 (PCMSK0 |= _BV(PCINT0))
// #define MYPIN_9_PCINT_MASK1 (PCMSK0 |= _BV(PCINT1))
// #define MYPIN_10_PCINT_MASK1 (PCMSK0 |= _BV(PCINT2))
// #define MYPIN_11_PCINT_MASK1 (PCMSK0 |= _BV(PCINT3))
// #define MYPIN_12_PCINT_MASK1 (PCMSK0 |= _BV(PCINT4))
// #define MYPIN_13_PCINT_MASK1 (PCMSK0 |= _BV(PCINT5))

// #define MYPIN_8_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT0)))
// #define MYPIN_9_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT1)))
// #define MYPIN_10_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT2)))
// #define MYPIN_11_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT3)))
// #define MYPIN_12_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT4)))
// #define MYPIN_13_PCINT_MASK0 (PCMSK0 &= ~(_BV(PCINT5)))

// #define MYPIN_8_13_PCINT_ENABLE (PCICR |= _BV(PCIE0))
// #define MYPIN_8_13_PCINT_DISABLE (PCICR &= ~(_BV(PCIE0)))
/*C----------------------------------------------*/
#define MYPIN_A0_WRITE_MODE (DDRC |= _BV(DDC0))
#define MYPIN_A1_WRITE_MODE (DDRC |= _BV(DDC1))
#define MYPIN_A2_WRITE_MODE (DDRC |= _BV(DDC2))
#define MYPIN_A3_WRITE_MODE (DDRC |= _BV(DDC3))
#define MYPIN_A4_WRITE_MODE (DDRC |= _BV(DDC4))
#define MYPIN_A5_WRITE_MODE (DDRC |= _BV(DDC5))

#define MYPIN_A0_WRITE_HIGH (PORTC |= _BV(PORTC0))
#define MYPIN_A1_WRITE_HIGH (PORTC |= _BV(PORTC1))
#define MYPIN_A2_WRITE_HIGH (PORTC |= _BV(PORTC2))
#define MYPIN_A3_WRITE_HIGH (PORTC |= _BV(PORTC3))
#define MYPIN_A4_WRITE_HIGH (PORTC |= _BV(PORTC4))
#define MYPIN_A5_WRITE_HIGH (PORTC |= _BV(PORTC5))

#define MYPIN_A0_WRITE_LOW (PORTC &= ~(_BV(PORTC0)))
#define MYPIN_A1_WRITE_LOW (PORTC &= ~(_BV(PORTC1)))
#define MYPIN_A2_WRITE_LOW (PORTC &= ~(_BV(PORTC2)))
#define MYPIN_A3_WRITE_LOW (PORTC &= ~(_BV(PORTC3)))
#define MYPIN_A4_WRITE_LOW (PORTC &= ~(_BV(PORTC4)))
#define MYPIN_A5_WRITE_LOW (PORTC &= ~(_BV(PORTC5)))

#define MYPIN_A0_READ_MODE (DDRC &= ~(_BV(DDC0)))
#define MYPIN_A1_READ_MODE (DDRC &= ~(_BV(DDC1)))
#define MYPIN_A2_READ_MODE (DDRC &= ~(_BV(DDC2)))
#define MYPIN_A3_READ_MODE (DDRC &= ~(_BV(DDC3)))
#define MYPIN_A4_READ_MODE (DDRC &= ~(_BV(DDC4)))
#define MYPIN_A5_READ_MODE (DDRC &= ~(_BV(DDC5)))

#define MYPIN_A0_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC0);     \
        DDRC &= ~(_BV(DDC0));     \
    } while (0)
#define MYPIN_A1_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC1);     \
        DDRC &= ~(_BV(DDC1));     \
    } while (0)
#define MYPIN_A2_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC2);     \
        DDRC &= ~(_BV(DDC2));     \
    } while (0)
#define MYPIN_A3_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC3);     \
        DDRC &= ~(_BV(DDC3));     \
    } while (0)
#define MYPIN_A4_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC4);     \
        DDRC &= ~(_BV(DDC4));     \
    } while (0)
#define MYPIN_A5_READ_MODE_PULLUP \
    do                            \
    {                             \
        PORTC |= _BV(PORTC5);     \
        DDRC &= ~(_BV(DDC5));     \
    } while (0)

#define MYPIN_A0_READ_HIGH ((PINC & (_BV(PINC0))) > 0)
#define MYPIN_A1_READ_HIGH ((PINC & (_BV(PINC1))) > 0)
#define MYPIN_A2_READ_HIGH ((PINC & (_BV(PINC2))) > 0)
#define MYPIN_A3_READ_HIGH ((PINC & (_BV(PINC3))) > 0)
#define MYPIN_A4_READ_HIGH ((PINC & (_BV(PINC4))) > 0)
#define MYPIN_A5_READ_HIGH ((PINC & (_BV(PINC5))) > 0)

// #define MYPIN_A0_WRITE_TOGGLE (PINC |= (_BV(PINC0)))
// #define MYPIN_A1_WRITE_TOGGLE (PINC |= (_BV(PINC1)))
// #define MYPIN_A2_WRITE_TOGGLE (PINC |= (_BV(PINC2)))
// #define MYPIN_A3_WRITE_TOGGLE (PINC |= (_BV(PINC3)))
// #define MYPIN_A4_WRITE_TOGGLE (PINC |= (_BV(PINC4)))
// #define MYPIN_A5_WRITE_TOGGLE (PINC |= (_BV(PINC5)))

// #define MYPIN_A0_PCINT_MASK1 (PCMSK1 |= _BV(PCINT8))
// #define MYPIN_A1_PCINT_MASK1 (PCMSK1 |= _BV(PCINT9))
// #define MYPIN_A2_PCINT_MASK1 (PCMSK1 |= _BV(PCINT10))
// #define MYPIN_A3_PCINT_MASK1 (PCMSK1 |= _BV(PCINT11))
// #define MYPIN_A4_PCINT_MASK1 (PCMSK1 |= _BV(PCINT12))
// #define MYPIN_A5_PCINT_MASK1 (PCMSK1 |= _BV(PCINT13))

// #define MYPIN_A0_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT8)))
// #define MYPIN_A1_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT9)))
// #define MYPIN_A2_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT10)))
// #define MYPIN_A3_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT11)))
// #define MYPIN_A4_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT12)))
// #define MYPIN_A5_PCINT_MASK0 (PCMSK1 &= ~(_BV(PCINT13)))

// #define MYPIN_A0_A5_PCINT_ENABLE (PCICR |= _BV(PCIE0))
// #define MYPIN_A0_A5_PCINT_DISABLE (PCICR &= ~(_BV(PCIE0)))
/*一级--------------------------------------------*/
#define _MYPIN_WRITE_MODE(x) MYPIN_##x##_WRITE_MODE
#define _MYPIN_WRITE_HIGH(x) MYPIN_##x##_WRITE_HIGH
#define _MYPIN_WRITE_LOW(x) MYPIN_##x##_WRITE_LOW
#define _MYPIN_READ_MODE(x) MYPIN_##x##_READ_MODE
#define _MYPIN_READ_MODE_PULLUP(x) MYPIN_##x##_READ_MODE_PULLUP
#define _MYPIN_READ_HIGH(x) MYPIN_##x##_READ_HIGH
// #define _MYPIN_WRITE_TOGGLE(x) MYPIN_##x##_WRITE_TOGGLE
// #define _MYPIN_PCINT_MASK1(x) MYPIN_##x##_PCINT_MASK1
// #define _MYPIN_PCINT_MASK0(x) MYPIN_##x##_PCINT_MASK0

/*二级--------------------------------------------*/
#define MYPIN_WRITE_MODE(x) _MYPIN_WRITE_MODE(x)
#define MYPIN_WRITE_HIGH(x) _MYPIN_WRITE_HIGH(x)
#define MYPIN_WRITE_LOW(x) _MYPIN_WRITE_LOW(x)
#define MYPIN_READ_MODE(x) _MYPIN_READ_MODE(x)
#define MYPIN_READ_MODE_PULLUP(x) _MYPIN_READ_MODE_PULLUP(x)
#define MYPIN_READ_HIGH(x) _MYPIN_READ_HIGH(x)
#define MYPIN_READ_LOW(x) !_MYPIN_READ_HIGH(x)
// #define MYPIN_WRITE_TOGGLE(x) _MYPIN_WRITE_TOGGLE(x)
// //pin change interrupt mask 1
// #define MYPIN_PCINT_MASK1(x) _MYPIN_PCINT_MASK1(x)
// //pin change interrupt mask 0
// #define MYPIN_PCINT_MASK0(x) _MYPIN_PCINT_MASK0(x)

#ifdef __cplusplus
extern "C"
{
#endif
    // //必须先调用MYPIN_PCINT_MASK1(x) mask哪个pin可以触发中断，
    // //然后调用该函数使能中断
    // void myPinChangeInterruptEnableUsed();
    // //先调用MYPIN_PCINT_MASK0(x) unmask不要的pin，
    // //调用该函数，该函数会统计unmask的pin，然后关闭用不到的中断。
    // void myPinChangeInterruptDisableUnused();
    // //设置中断处理函数
    // void myPinChangeInterruptFunction(void (*func_pcint0_7)(), void (*func_pcint8_13)(), void (*func_pcintA0_A5)());
#ifdef __cplusplus
}
#endif

#endif
