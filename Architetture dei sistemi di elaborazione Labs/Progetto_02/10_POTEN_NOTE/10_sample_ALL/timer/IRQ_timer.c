/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../dac/dac.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint16_t SinTable[32] =                                       /* ÕýÏÒ±í                       */
{
   256, 306, 354, 398, 436, 468, 492, 506, 511, 506, 492, 468, 436, 398, 354, 306, 256, 206, 158, 114, 75, 43, 20, 5, 0, 5, 20, 43, 75, 114, 158, 206



};

void TIMER0_IRQHandler (void)
{
	static int ticks=0;
	/* DAC management */	

	
	DAC_convert (SinTable[ticks]<<6);
	ticks++;
	if(ticks==32) ticks=0;

	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
