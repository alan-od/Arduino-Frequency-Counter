/*
 * 
 * Main header file
 * 
 * Sets various pins high or low or sets up a pulse
 * 
 * 
 * 
 *  Author: Alan O'Donovan
 *  Copyright (c) 2016 Alan O'Donnovan.  All rights reserved.
 *   
 *  This file is part of Frequency_counter
 *
 *  Frequency_counter is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Frequency_counter is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Frequency-counter.  If not, see <http://www.gnu.org/licenses/>. 
 *   
 * 
 */

#ifndef FREQ_PINS
#define FREQ_PINS

#define NOP __asm__("nop\n\t");

//----------Set up pin macros----------------
//See circuit diagram
//Clocks U7 (Flush Counters)
#define CK_U  PORTB |= (1 << PORTB4)  // Pin D12
#define CK_D  PORTB &= ~(1 << PORTB4)
#define FLUSH_74323 CK_U,CK_U,CK_D,CK_D,CK_D,CK_U,CK_U,CK_U  //sets up a pulse

//Clears U7 (Clear Counters)
#define CL_H PORTB |= (1 << PORTB5)  //Pin D13 (LED pin)
#define CL_L PORTB &= ~(1 << PORTB5)
#define CLEAR CL_H,CL_H,CL_H,CL_H,CL_L

//Set U1 74HC74 Preset to 1 or 0
#define ENABLE_1HZ    PORTC |= (1<<PORTC1)  // Pin A1
#define DISABLE_1HZ   PORTC &= ~(1<<PORTC1) 

//Set U4B pin 4 to 1 or 0 (internal timebase)
#define INT_TB_HI     PORTC |= (1<<PORTC2)  //Pin A2
#define INT_TB_LOW    PORTC &= ~(1<<PORTC2)

//Set Sel to 1 or 0 (selects prescaler)
#define SEL_HF     PORTC |= (1<<PORTC0)  //Pin A0
#define SEL_LF    PORTC &= ~(1<<PORTC0)

#endif
