#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <xc.h>

/*
 * Global configurations
 */
#define CONFIG_NUMBER_OF_DISPLAYS   3 /* 8 maximum */
#define CONFIG_COMMON_TERMINAL      0 /* 0 for cathode and 1 for anode*/

/*
 * General displays hardware definitions
 */
#define CONFIG_DISPLAY_SEGMENTS_PORT_OUT    PORTB
#define CONFIG_DISPLAY_SEGMENTS_PORT_DIR    TRISB
#define CONFIG_DISPLAY_SELECTOR_PORT_OUT    PORTC
#define CONFIG_DISPLAY_SELECTOR_PORT_DIR    TRISC

/*
 * Configuration of diplays segments to easy the
 * hardware design. Thus occupy one PORT
 */
#define CONFIG_SEG_A                        (0b00000001)
#define CONFIG_SEG_B                        (0b00000010)
#define CONFIG_SEG_C                        (0b00000100)
#define CONFIG_SEG_D                        (0b00001000)
#define CONFIG_SEG_E                        (0b00010000)
#define CONFIG_SEG_F                        (0b00100000)
#define CONFIG_SEG_G                        (0b01000000)
#define CONFIG_SEG_DOT                      (0b10000000)

/*
 * Turn off definition must not be a printable value
 * 		i.e. 15 < CONFIG_TURN_OFF < 2556
 */
#define CONFIG_TURN_OFF                     255


/* 
 * This definitions must be replicated many as the
 * defined number of displays .
 * 		i.e. CONFIG_DISPLAY_X_SELECTOR_POSITON and the
 *			 "X" must be replaced by a display number.
 *
 * All displays selectors must be defined with a relative
 * to a physical port pin position and may be changed to 
 * easy the hardware design.
 */
#define CONFIG_DISPLAY_0_SELECTOR_POSITON     (0b00000001)
#define CONFIG_DISPLAY_1_SELECTOR_POSITON     (0b00000010)
#define CONFIG_DISPLAY_2_SELECTOR_POSITON     (0b00000100)

/**
 * @brief Here all hardware dependencies are initialized.
 *
 * PORT and TRIS values are defined accord to CONFIG macros
 * and all display are turned off.
 *
 */
void sevenseg_Init(void);

/**
 * @brief Set a value on a specific display.
 *
 * @param num Display to change the value.
 *      i.e. Select a value less or equal to "CONFIG_NUMBER_OF_DISPLAYS"
 *           macro value. 
 * @param value Value that will be set.
 *		i.e. This value must be between 0 and 9 inclusives
 			 Diplays go to blank state if value is "CONFIG_TURN_OFF".
 *
 * @param dot Set dot state.
 *		e.g. If "dot" equals "1", turn on the dot LED
 *			 and if "0", turn off. 
 */
void sevenseg_SetValue(unsigned char num, unsigned char value, unsigned char dot);

/**
 * @brief This function must be called to do multiplex all displays.
 * 
 * e.g. Can be called in a main infinite loop or
 * 		in a timer triggered interrupt routine to 
 *		keep cahnge on precise time intervals.   
 */
void sevenseg_Multiplex(void);

#endif /* SEVENSEG_H */