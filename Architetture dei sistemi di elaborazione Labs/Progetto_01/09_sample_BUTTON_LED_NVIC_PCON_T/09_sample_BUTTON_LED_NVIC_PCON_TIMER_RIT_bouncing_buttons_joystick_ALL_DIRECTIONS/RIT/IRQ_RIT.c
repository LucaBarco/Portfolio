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

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;

void RIT_IRQHandler (void)
{					
	static int select=0;
	static int i=0;	
	static int leds=0; // contiente il vettore dei led da accendere o spegnere
	/******** 
	         dallo schematico 
							select 	25
							down 26
							left 27
							right 28
							up 29 
	********/
	
	if(((LPC_GPIO1->FIOPIN & (31<<25)) ^ (31<<25)) !=0 ){		//controllo che almeno un input del joystick sia attivo 
																													// con la and estraiamo i 5 bit corrispondent agli input
																													// con la xor verifichiamo che almeno uno sia attivo (ovvero il bit è a 0)
		select++;				// serve per l'intermittenza (bouncing)
				
		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	//pressione pulsante select 
			
			switch(select){
				case 1:
				if(i%2==0)
					leds=0x80;
				else
					leds=0x01;
				i++;
				break;
				default:
				break;
			}
		} if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	//down
				leds|=0x30;
		}if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	//up
				leds|=0x0C;
		}if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	//right
				leds|=0x03;
		}if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	//left
				leds|=0xC0;
		}
			LED_Out(leds);
	}
	else {		//resetto tutto se non è selezionato nulla	
			select=0;
			leds=0;	
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
