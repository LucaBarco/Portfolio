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
#include "RIT.h"
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

int down=0;
int note=0;
void RIT_IRQHandler (void)
{				

	static int select=0;
	static int i=0;	
	
	int vettK[13]={1062,1125,1192,1263,1339,1417,1502,1592,1684,1786,1890,2006,2120};

	/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */
				/*C: *523 Hz --> k=25M/(523*45)= 1062
				B: 494Hz --> k=25M/(494*45)= 1125
				Bb: 466 Hz --> k=25M/(466*45)= 1192
				A: 440 Hz --> k=25M/(440*45)= 1263
				Ab: 415 Hz --> k=25M/(415*45)= 1339
				G: 392 Hz --> k=25M/(392*45)= 1417
				Gb: 370 Hz --> k=25M/(370*45)= 1502
				F: 349 Hz --> k=25M/(349*45)= 1592
				E: 330 Hz --> k=25M/(330*45)= 1684
				Eb: 311 Hz --> k=25M/(311*45)= 1786
				D: 294 Hz --> k=25M/(294*45)= 1890
				Db: 277 Hz --> k=25M/(277*45)= 2006
				C: 262 Hz --> k=25M/(262*45)= 2120
	 */	
	/* button management */
	if(down!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down++;				
			switch(down){
				case 2:
					
				init_timer(0,vettK[note-1]);
				reset_timer(0);
				enable_timer(0);
			
				
					
				
					if(i%2==0)
						LED_Out(0xAA);
					else
						LED_Out(0x55);
					i++;
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down=0;			
			disable_timer(0);
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
		
	/* joystick management */
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	/* Joytick Select pressed */
		select++;
		switch(select){
			case 1:
				if(i%2==0)
					LED_Out(0xF0);
				else
					LED_Out(0x0F);
				i++;
				break;
			default:
				break;
		}
	}
	else{
			select=0;
	}
		
	/* ADC management */
	ADC_start_conversion();		
			
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
