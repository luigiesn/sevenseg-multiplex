#include "../include/interrupt.h"
#include "../include/sevenseg.h"

/*
 * sevenseg-multiplex code application example using timer interrupt to control
 * the display changing interval time
 */

void main(void) {
    /* Config timer 0*/
    OPTION_REG &= ~0x20; /*  Internal instruction cycle clock */
    OPTION_REG &= ~0x04; /* Prescaler assigned to Timer0 */
    OPTION_REG |= 0x07; /* Prescaler to 1:16 */

    INTCON &= ~0x04; /* Clean flag */
    INTCON |= 0x20; /* Enable TIMER0 interrupt */

    GIE = 1;

    /* Assing seven segments to timer0 interrupt*/
    interrupt_Assing(TMR0_INT_NUM, sevenseg_Multiplex);

    /* Intialize displays*/
    sevenseg_Init();

    /* Set values*/
    sevenseg_SetValue(0, 1, 0);
    sevenseg_SetValue(1, 2, 0);
    sevenseg_SetValue(2, 3, 0);

    for (;;) {
        /* Don't need to do nothing in this case, timer0 interrupt routine
         * do the all dirty job */

        /* Stay here for()ever! */
    }

}