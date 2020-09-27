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
#include "../led/led.h"
#include "../RIT/RIT.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	/* Interrupt Timer 0 (Timer for elevator moving) -> increment of position value and restart of timer*/
	if(!atdest()){
	if(isup()){
		incposition();
	} else if (isdown()){
		decposition();
	}
	else{
		// NOT MOVING
	}
} else{
	enable_timer(3);
	disable_timer(2);
}
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
	/* Interrupt Timer 1 (Timer of still not moving for 1 minute) -> alarm / right end of elevator moving*/
	//Turning on both the alarm leds
	if(!atdest()){
		LED_On(8);
		LED_On(10);
	}
	else{
		//elevator has reached its destination
		setreserved(0);
		
		if(isup()){
			LED_Off(9);
	}
		else if (isdown()){
			LED_Off(11);
		}
	}
		LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER2_IRQHandler (void)
{
	/* Interrupt Timer 2 (Timer for Led4 2Hz blinking when elevator is moving)*/
	static j=0;
	if(j%2==0){
	}
	else{
	}
	j++;
	if(j==10000){
		j=0;
	}
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER3_IRQHandler (void)
{
	/* Interrupt Timer 3 (Timer for Led4 5Hz blinking at the end of elevator moving)*/
	static int k=0;
	if(k%2==0){
	}
	else{
	}
	k++;
	if(k==10000){
		k=0;
	}
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
