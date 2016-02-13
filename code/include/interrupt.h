/*
 * Interrupt codes - part of sevenseg-multiplex
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

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <xc.h>

/*
 * Total number of int sources
 *		i.e. The number must consider
 * 			all defined interrupt sources numbers
 */
#define CONFIG_NUM_OF_INTS 1

/*
 * Define interrupt numbers here, may be any number 
 */
#define TMR0_INT_NUM 0

typedef void(*interruptFunc)(void);

/**
 * All interrupts are directed to this function
 *
 * This function don't need to be called
 */
void interrupt mainIntISR(void);

/**
 * Assing an interrupt function to a interrupt source
 * 
 * @param intNumber Previously defined interruption number
 * @param interruptFunv A function pointer to the specified interrupt source handler
 *
 * 		e.g. interrupt_Assing(TMR0_INT_NUM, sevenseg_Multiplex);
 *
 */
void interrupt_Assing(unsigned char intNumber, interruptFunc intFunc);

#endif /* INTERRUPT_H */