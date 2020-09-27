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

volatile int down1=0,down2=0; // variables for debouncing of KEY1 AND KEY2
volatile int elevator_up=0,elevator_down=0,elevator_select=0,elevator_moving=0,elevator_reserved=0,floor_sorg=0,floor_dest=0,position=0;

int isup(void){return elevator_up;}
int isdown(void){return elevator_down;}
int ismoving(void){return elevator_moving;}
int isselect(void){return elevator_select;}
int getposition(void){return position;}
void setposition(int pos){position=pos;}
int incposition(void){position++; return position;}
int decposition(void){position--; return position;}
int atdest(void){return position==floor_dest;}
void setreserved(int res){elevator_reserved=res;}
void setselect(int sel){elevator_select=sel;}

void RIT_IRQHandler (void)
{			
/******** 
							select 	25
							down 26
							left 27
							right 28
							up 29 
	********/
		
	static int j_select=0,j_up=0,j_down=0; //variabili per il debouncing del joystick
	static int i=0;	
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed -> activation of elevator */
		j_select++;
		switch(j_select){
			case 1:
				//select-> attivo ascensore
				if(elevator_reserved==1 && floor_sorg==position && elevator_select==0){ //attivo solo se ascensore è stato rpima riservato e se si trova al piano corretto
						elevator_select=1;
						elevator_moving=1;
						LED_On(4);
				}
				break;
			default:
				break;
		}
	}
	else{
			j_select=0;
		if ((LPC_GPIO1->FIOPIN & (1<<26))==0){
			/* Joystick Down pressed -> the elevator must go down*/
			j_up++;
			switch(j_up){
				case 1:
					//se ascensore è attivo, mi muovo verso l'alto
				if(elevator_select==1){
					elevator_moving=1;
					disable_timer(1);
				if(elevator_down==1){
						floor_dest=80;
					}
					else{
						floor_dest=0;
					}	
				  elevator_up=1;
					elevator_down=0;
				if(position!=floor_dest){
						enable_timer(0);
					//blinking 2MHz
					enable_timer(2);
				}
				else{
					//sono a destinazione
					//blinkign 5Mhz per 3s
					disable_timer(2);
					enable_timer(1);
					for(i=0;i<30;i++){
						enable_timer(3);
						}
				}
			}
					break;
				default:
					break;
			}
		}
		else {
			j_up=0;
			if((LPC_GPIO1->FIOPIN & (1<<29))==0){
				/* Joystick Up pressed -> the elevator must go up*/
				j_down++;
				switch (j_down){
					case 1:
						//se ascensore è attivo, mi muovo verso il basso
					if(elevator_select==1){
						elevator_moving=1;
						disable_timer(1);
					if(elevator_up==1){
						floor_dest=0;
					}
					else{
						floor_dest=80;
					}
						elevator_up=0;
						elevator_down=1;
					if(position!=floor_dest){
						enable_timer(0);
						//blinking 2Mhz
						enable_timer(2);
					}
					else{
						//sono a destinazione
						//blinkign 5Mhz per 3s
					enable_timer(1);
					for(i=0;i<30;i++){
						enable_timer(3);
					}
					}
				}
						break;
					default:
					break;
				}
			}
			else{
				j_down=0;
				//verify if the elevator has stopped while it was moving or if it has reached its destination
				if(elevator_moving==1){
					reset_timer(1);
					enable_timer(1);
					elevator_moving=0;
				}
			}
		}
	}
	
	/* button management */
	if(down1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down1++;				
			switch(down1){
				case 2:
					//azione da eseguire la prima volta
					
				// Elevator reserved for floor 1
				if(elevator_reserved==0){
					floor_sorg=80;
					floor_dest=0;
					elevator_reserved=1;
					if (position==floor_sorg){
					elevator_moving=0;
				}
					else if(position==floor_dest){
						elevator_moving=1;
						//elevator must go up --> start moving
						//moving > WRITE CODE
						elevator_up=1;
						position=floor_sorg;
						enable_timer(0);
						//blin	king 2Mhz
						enable_timer(2);
						
						//blinking 5Mhz
						elevator_up=0;
						disable_timer(2);
						for(i=0;i<30;i++){
						enable_timer(3);
						}
					}
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
	if (down2!=0){
		
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			down2++;				
			switch(down2){
				case 2:
					//azione da eseguire la prima volta
					
				// Elevator reserved for floor 0
				if(elevator_reserved==0){
					floor_sorg=0;
					floor_dest=80;
					elevator_reserved=1;
					if(position==floor_sorg){
					elevator_moving=0;
				}
					else if (position==floor_dest){
						//elevator must go down --> start moving
						elevator_reserved=1;
						//moving -> WRITE CODE
						elevator_down=1;
						position=floor_sorg;
						while(position!=floor_dest){
							enable_timer(0);
							enable_timer(2);
						}
						elevator_down=0;
						for(i=0;i<30;i++){
						enable_timer(3);
						}
						}
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
