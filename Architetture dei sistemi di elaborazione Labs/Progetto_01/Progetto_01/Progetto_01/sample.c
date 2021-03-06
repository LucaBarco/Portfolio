/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT and joystick buttons
 * Note(s):
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	
	init_timer(0,0x00225510);							// t=0.09s ,f=25000000 --> cc=0.09*25000000=2250000 -> 0x00225510
	init_timer(1,0x59682F00);							// t=60s , f=25000000 --> cc=60*25000000=1500000000 -> 0x59682F00
	init_timer(2,0x005F5E10);							// t=0.25s , f=25000000 --> cc=0.25*25000000=6250000 -> 0x005F5E10
	init_timer(3,0x002625A0);							// t=0.1s, f=25000000 --> cc=0.1*25000000=2500000 ->  0x002625A0
	enable_RIT();													/* RIT enabled												*/
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
