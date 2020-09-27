/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "../RIT/RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down1,down2; //variables for debouncing of key1 and key2
volatile int elevator_up=0,elevator_down=0,elevator_select=0,elevator_moving=0,elevator_reserved=0,floor_sorg=0,floor_dest=0,position=0,potential_alarm=0,elevator_alarm=0;

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

void RIT_IRQHandler (void)
{					
	static int j_select=0,j_up=0,j_down=0; //variables for debouncing of select, up and down of joystick

	/******** 
							select 	25
							down 26
							left 27
							right 28
							up 29 
	********/
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed */
		j_select++;
		switch(j_select){
			case 1:
				if(elevator_reserved==1 && floor_sorg==position && elevator_select==0){ //attivo solo se ascensore è stato prima riservato e se si trova al piano corretto
					disable_timer(1);	
					elevator_select=1;
					
						LED_On(7);
				}
				break;
			default:
				break;
		}
	}
	else{
			j_select=0;
		if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick Down pressed */
		j_down++;
		switch(j_down){
			case 1:
				//if elevator is active --> moving down
			if(elevator_select==1){
				if(elevator_moving==0){
					enable_timer(0); //timer0 activated only if it's the first movement 
					enable_timer(2); //2Hz blinking status led
					elevator_moving=1; //elevator is moving
				}
				if(potential_alarm==1 || elevator_alarm==1){
					//if the elevator was previously stopped --> disable timer 1, turn off status led and alarm leds, restart timer0
				disable_timer(1);
				reset_timer(1);
				enable_timer(0);
				LED_Off(7); //turn off status led
				enable_timer(2);
				potential_alarm=0;
				elevator_alarm=0;
				//turn off alarm leds
				LED_Off(3); 
				LED_Off(1);
				}
				floor_dest=0;     //reset for eventual reverse of movement
				floor_sorg=80;
				elevator_up=0;
				elevator_down=1; //elevator is moving down
			}
				break;
			default:
				break;
		}
	}
		else {
			j_down=0;
			if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick Up pressed */
		j_up++;
		switch(j_up){
			case 1:
				if(elevator_select==1){
					if(elevator_moving==0){
						enable_timer(0); //timer0 activated only if it's the first movement 
						enable_timer(2); //2Hz blinking status led
						elevator_moving=1; //elevator is moving
					}
					
					if(potential_alarm==1 || elevator_alarm==1){
						//if the elevator was previously stopped --> disable timer 1, turn off status led and alarm leds, restart timer0
				disable_timer(1); 
				reset_timer(1);
				enable_timer(0);
				LED_Off(7);
				enable_timer(2);
				potential_alarm=0;
				elevator_alarm=0;
				//turn off led 8 and 10
				LED_Off(3); 
				LED_Off(1);
				}
					floor_dest=80; //reset for eventual reverse of movement
					floor_sorg=0;
					elevator_down=0;
					elevator_up=1; //elevator is moving up
				}
				break;
			default:
				break;
		}
	}
			else{
				j_up=0;
				//None pressed
				if(elevator_reserved==1 && elevator_moving==1){
					//looking for alarm
					enable_timer(1);
					disable_timer(0);
					potential_alarm=1;
					disable_timer(2);
					reset_timer(2);
					LED_On(7);
				}
		}
	}
}
	
	/* button management */

	/******************************************************
	 ************* PANEL CONTROL FLOOR 1 ******************
   ******************************************************/

	if(down1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down1++;				
			switch(down1){
				case 2:
					if(elevator_reserved==0){
						elevator_reserved=1;
						//turn on led 9 and 11
						LED_On(2);
						LED_On(0);
						if(position!=80){
							floor_dest=80;
							floor_sorg=0;
							elevator_up=1;
							elevator_down=0;
							enable_timer(0); //starting movement to right floor
							enable_timer(2); //2Hz blinking status led
					}
				}
						else{
							floor_dest=0;
							floor_sorg=80;
						  enable_timer(1); //60s to press select button of joystick
						}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	
	/******************************************************
	 ************* PANEL CONTROL FLOOR 0 ******************
   ******************************************************/
	
		if(down2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			down2++;				
			switch(down2){
				case 2:
					if(elevator_reserved==0){
						elevator_reserved=1;
						//turn on led 9 and 11
						LED_On(2);
						LED_On(0);
						if(position!=0){
							floor_dest=0;
							floor_sorg=80;
							elevator_up=0;
							elevator_down=1;
							enable_timer(0); //starting movement to right floor
							enable_timer(2); //2Hz blinking status led
					}
				}
						else{
							floor_dest=80;
							floor_sorg=0;
						  enable_timer(1); //60s to press select button of joystick
						}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
