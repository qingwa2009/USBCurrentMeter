
#include "MyPin.h"
// static void (*_func_pcint0_7)() = 0;
// static void (*_func_pcint8_13)() = 0;
// static void (*_func_pcintA0_A5)() = 0;

// /*pin 8~13*/
// ISR(PCINT0_vect)
// {
//     if (_func_pcint8_13)
//         _func_pcint8_13();
// }

// /*pin A0~A5*/
// ISR(PCINT1_vect)
// {
//     if (_func_pcintA0_A5)
//         _func_pcintA0_A5();
// }

// /*pin 0~7*/
// ISR(PCINT2_vect)
// {
//     if (_func_pcint0_7)
//         _func_pcint0_7();
// }

// void myPinChangeInterruptFunction(void (*func_pcint0_7)(), void (*func_pcint8_13)(), void (*func_pcintA0_A5)())
// {
//     _func_pcint0_7 = func_pcint0_7;
//     _func_pcint8_13 = func_pcint8_13;
//     _func_pcintA0_A5 = func_pcintA0_A5;
// }

// void myPinChangeInterruptEnableUsed()
// {
//     if (PCMSK0)
//         PCICR |= _BV(PCIE0);
//     if (PCMSK1)
//         PCICR |= _BV(PCIE1);
//     if (PCMSK2)
//         PCICR |= _BV(PCIE2);
// }

// void myPinChangeInterruptDisableUnused()
// {
//     if (!PCMSK0)
//         PCICR &= ~(_BV(PCIE0));
//     if (!PCMSK1)
//         PCICR &= ~(_BV(PCIE1));
//     if (!PCMSK2)
//         PCICR &= ~(_BV(PCIE2));
// }
