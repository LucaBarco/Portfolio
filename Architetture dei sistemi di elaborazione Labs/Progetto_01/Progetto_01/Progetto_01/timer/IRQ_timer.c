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
#include "../timer/timer.h"
#include "../led/led.h"
extern int elevator_up,elevator_down,elevator_select,elevator_moving,elevator_reserved,elevator_alarm,floor_sorg,floor_dest,position;
/*
LED 4 -> 7
LED 8 -> 3
LED 9 -> 2
LED 10 -> 1
LED 11 -> 0

elevator_up -> flag: elevator is moving up
elevator_down -> flag: elevator is moving down
elevator_select -> flag: elevator is active
elevator_moving -> flag: elevator is moving
elevator_reserved -> flag: elevator is reserved (pressed)
elevator_alarm -> flag: there is an alarm situation
floor_sorg -> variable that contains the number relative to the sorgent floor (0 for floor 0, 80 for floor 1)
floor_dest -> variable that contains the number relative to the destination floor (0 for floor 0, 80 for floor 1)
position -> variable that contains the current position of the elevator (range: 0-80)
*/

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
										Timer for moving of elevator
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	if(elevator_down){
		position--;
		}
		else if(elevator_up){
		position++;
		}
		
	if(position==floor_dest){
		if(elevator_reserved==1 && elevator_select==0){
			//end of reservation from another floor
			disable_timer(0);
			reset_timer(0);
			disable_timer(2);
			reset_timer(2);
			enable_timer(1); //60s to press select button of joystick
			enable_timer(3);
			floor_sorg=position;
			floor_dest=80-position;
		}
		else if (elevator_reserved==1 && elevator_select==1){
			//end user moving
			disable_timer(0);
			reset_timer(0);
			disable_timer(2);
			reset_timer(2);
			//enable_timer(1); //60s for the end of moving (let user to get off from the elevator
			elevator_reserved=0;
			elevator_moving=0;
			elevator_select=0;
			elevator_up=0;
			elevator_down=0;
			enable_timer(3); //timer for 5Hz blinking
			disable_timer(1);
			reset_timer(1);
			//enable_timer(1);
		}
	}
		
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
										Manages situations when elevator is still not moving
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(elevator_reserved==1 && elevator_select==0){
	//60s expired to activate elevator -> undo reservation
		elevator_reserved=0;
		//turning off all leds
		LED_Out(0x00);
	}
	else if (elevator_moving==1){
		//elevator stopped during movement --> ALARM
		//turn on alarm led 8 and 10
		LED_On(3);
		LED_On(1);
		elevator_alarm=1;
	}
	
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**									Timer for 2MHz Status Led Blinking
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	static int i=0;
	if(i%2==0){
		LED_On(7);
	}
	else{
		LED_Off(7);
	}
	i++;
	if(i==10000){
		i=0;
	}
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**									Timer for 2MHz Status Led Blinking
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
	static int i3=0;
	if(i3%2==0){
		LED_On(7);
	}
	else{
		LED_Off(7); 
	}
	i3++;
	if(i3==30){ 
		disable_timer(3);
		reset_timer(3);
		elevator_moving=0; //elevator movement ends after the end of 5Hz 3second blinking
		if(elevator_reserved==0){
		LED_Out(0x00); //turn off all leds
		}
	i3=0;
	}
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
