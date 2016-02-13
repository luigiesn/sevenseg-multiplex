/*
 * sevenseg-multiplex
 * Copyright (C) 2015 - Luigi E. Sica Nery
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/sevenseg.h"

/* This contain all numbers from 0 to 9 definitions */
static unsigned char numbers[] = {
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_C | CONFIG_SEG_D | CONFIG_SEG_E | CONFIG_SEG_F),
    (CONFIG_SEG_B | CONFIG_SEG_C),
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_G | CONFIG_SEG_E | CONFIG_SEG_D),
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_G | CONFIG_SEG_C | CONFIG_SEG_D),
    (CONFIG_SEG_B | CONFIG_SEG_G | CONFIG_SEG_C | CONFIG_SEG_F),
    (CONFIG_SEG_A | CONFIG_SEG_F | CONFIG_SEG_G | CONFIG_SEG_C | CONFIG_SEG_D),
    (CONFIG_SEG_A | CONFIG_SEG_C | CONFIG_SEG_D | CONFIG_SEG_E | CONFIG_SEG_F | CONFIG_SEG_G),
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_C),
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_C | CONFIG_SEG_D | CONFIG_SEG_E | CONFIG_SEG_F | CONFIG_SEG_G),
    (CONFIG_SEG_A | CONFIG_SEG_B | CONFIG_SEG_C | CONFIG_SEG_D | CONFIG_SEG_F | CONFIG_SEG_G),
};

static unsigned char displaysSegments[CONFIG_NUMBER_OF_DISPLAYS];
static unsigned char displaysSelectors[CONFIG_NUMBER_OF_DISPLAYS];
static unsigned char nextDisplay;
static unsigned char selectors;

void sevenseg_Init(void) {
    selectors = 0;

#if CONFIG_NUMBER_OF_DISPLAYS > 0
    displaysSelectors[0] = CONFIG_DISPLAY_0_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_0_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 1
    displaysSelectors[1] = CONFIG_DISPLAY_1_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_1_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 2
    displaysSelectors[2] = CONFIG_DISPLAY_2_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_2_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 3
    displaysSelectors[3] = CONFIG_DISPLAY_3_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_3_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 4
    displaysSelectors[4] = CONFIG_DISPLAY_4_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_4_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 5
    displaysSelectors[5] = CONFIG_DISPLAY_5_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_5_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 6
    displaysSelectors[6] = CONFIG_DISPLAY_6_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_6_SELECTOR_POSITON;
#endif
#if CONFIG_NUMBER_OF_DISPLAYS > 7
    displaysSelectors[7] = CONFIG_DISPLAY_7_SELECTOR_POSITON;
    selectors |= CONFIG_DISPLAY_7_SELECTOR_POSITON;
#endif
    CONFIG_DISPLAY_SELECTOR_PORT_DIR &= ~selectors;
    CONFIG_DISPLAY_SELECTOR_PORT_OUT &= ~selectors;

    CONFIG_DISPLAY_SEGMENTS_PORT_DIR = 0x00; /* All as output */
    CONFIG_DISPLAY_SEGMENTS_PORT_OUT = 0x00; /* Turn off*/

    nextDisplay = 0;

    unsigned char i;

    /* Blank all displays */
    for (i = 0; i > CONFIG_NUMBER_OF_DISPLAYS; i++) {

        displaysSegments[i] = CONFIG_TURN_OFF;
    }
}

void sevenseg_SetValue(unsigned char num, unsigned char value, unsigned char dot) {
    displaysSegments[num] = numbers[value];
    /* Enable dot */
    if (dot) {
        displaysSegments[num] |= CONFIG_SEG_DOT;
    }
#if CONFIG_COMMON_TERMINAL == 1
    displaysSegments[num] = ~displaysSegments[num];
#endif
}

void sevenseg_Multiplex(void) {
    /* Change the display to show*/
    CONFIG_DISPLAY_SELECTOR_PORT_OUT &= ~selectors;
    CONFIG_DISPLAY_SEGMENTS_PORT_OUT = displaysSegments[nextDisplay];
    CONFIG_DISPLAY_SELECTOR_PORT_OUT = displaysSelectors[nextDisplay];

    nextDisplay++;
    if (nextDisplay >= CONFIG_NUMBER_OF_DISPLAYS)
        nextDisplay = 0;

}