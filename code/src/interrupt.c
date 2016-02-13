#include "../include/interrupt.h"

#define TMR0IE_MASK 0x20
#define TMR0IF_MASK 0x04

static interruptFunc intFuncs[CONFIG_NUM_OF_INTS];

void interrupt mainIntISR(void) {
    /* TMR0 interrupt handler */
    if ((INTCON & TMR0IE_MASK) && (INTCON & TMR0IF_MASK)) {
        INTCON &= ~TMR0IF_MASK; /* Clean flag */
        intFuncs[TMR0_INT_NUM]();
    }

    /* Other interrupt handlers here */
}

void interrupt_Assing(unsigned char intNumber, interruptFunc intFunc) {
    intFuncs[intNumber] = intFunc;
}
