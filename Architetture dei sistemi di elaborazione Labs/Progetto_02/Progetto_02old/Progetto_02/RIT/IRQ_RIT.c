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
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


/***********************************************************************************************************/
/*********************************VARIABILI GESTIONE MOVIMENTO ASCENSORE************************************/
/***********************************************************************************************************/
volatile int down1,down2,down3; //variables for debouncing of key1 and key2
volatile int elevator_up=0,elevator_down=0,elevator_select=0,elevator_moving=0,elevator_reserved=0,
							floor_sorg=0,floor_dest=0,position=0,potential_alarm=0,
							elevator_alarm=0, elevator_emergency=0,elevator_maintenance=0;
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
elevator_emergency -> flag: there is an emergency
elevator_maintenance -> flag: maintenance mode is on
floor_sorg -> variable that contains the number relative to the sorgent floor (0 for floor 0, 80 for floor 1)
floor_dest -> variable that contains the number relative to the destination floor (0 for floor 0, 80 for floor 1)
position -> variable that contains the current position of the elevator (range: 0-80)
*/

/***********************************************************************************************************/
/*********************************VARIABILI GESTIONE SUONI E TOUCHSCREEN************************************/
/***********************************************************************************************************/
volatile int nbutton=0; /*indica quale pulsante sul touch screen è premuto: 
													1: SAVE
													2: QUIT
													3: SELECT 1
													4: SELECT 2*/
													
volatile int modTone=0; //flag -> se 1 sono in modalità modifica tono
int note1=3,note2=3; //indici per accedere al vettore di frequenze vettK
volatile int nTone=0; //indica il numero della selezione del tono coinvolta nella modifica
int suono=0; //flag che indica se sto riproducendo un suono o no



/*************************************************************************************************************/
void RIT_IRQHandler (void)
{	
	/*if(elevator_reserved==0 && elevator_emergency==0 && elevator_maintenance==0){
		init_timer(1,0x59682F00);							// t=60s , f=25000000 --> cc=60*25000000=1500000000 -> 0x59682F00
		reset_timer(1);
	}*/
if(elevator_maintenance==0){	
	manageJoystick();
	manageFloorPanels();
	manageEmergencyButton();
}
	manageTouchPanel();	
	/* ADC management */
	ADC_start_conversion();		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

void manageJoystick(void){
	
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
				if(elevator_reserved==1 && floor_sorg==position && elevator_select==0 && elevator_alarm==0 ){ //attivo solo se ascensore è stato prima riservato e se si trova al piano corretto
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
						if(elevator_select==1 && elevator_alarm==0){
							if(elevator_moving==0){
								enable_timer(0); //timer0 activated only if it's the first movement 
								enable_timer(2); //2Hz blinking status led
								elevator_moving=1; //elevator is moving
							}
							if(potential_alarm==1 && elevator_alarm==0){
								//if the elevator was previously stopped --> disable timer 1, turn off status led and alarm leds, restart timer0
								EmergencyModeOff();
								enable_timer(0);
								enable_timer(2);
								potential_alarm=0;
								/*elevator_alarm=0;*/
							//turn off alarm leds
							//LED_Off(3); 
							//LED_Off(1);
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
										if(elevator_select==1 && elevator_alarm==0){
											if(elevator_moving==0){
												enable_timer(0); //timer0 activated only if it's the first movement 
												enable_timer(2); //2Hz blinking status led
												elevator_moving=1; //elevator is moving
											}
											
											if(potential_alarm==1 && elevator_alarm==0){
												//if the elevator was previously stopped --> disable timer 1, turn off status led, restart timer0
										disable_timer(1); 
										reset_timer(1);
										enable_timer(0);
										LED_Off(7);
										enable_timer(2);
										potential_alarm=0;
										/*elevator_alarm=0;*/
										//turn off led 8 and 10
										//LED_Off(3); 
										//LED_Off(1);
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
							if(elevator_reserved==1 && elevator_moving==1 && elevator_emergency==0){
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
}
void manageFloorPanels(void){
/******************************************************
	 ************* PANEL CONTROL FLOOR 1 ******************
   ******************************************************/

	if(down1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down1++;				
			switch(down1){
				case 2:
					if(elevator_reserved==0 || elevator_alarm==1){
						elevator_reserved=1;
						if(elevator_alarm==1){
						//stop emergency
							EmergencyModeOff();
						}
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
						if(position!=floor_sorg){
							floor_dest=0;
							floor_sorg=80;
						}
				}
						else{
							if(elevator_alarm==0){
							floor_dest=0;
							floor_sorg=80;
						  enable_timer(1); //60s to press select button of joystick
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
	
	/******************************************************
	 ************* PANEL CONTROL FLOOR 0 ******************
   ******************************************************/
	
		if(down2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			down2++;				
			switch(down2){
				case 2:
					if(elevator_reserved==0 || elevator_alarm==1){
						elevator_reserved=1;
						if(elevator_alarm==1){
						//stop emergency
							EmergencyModeOff();
						}
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
						if(position!=floor_sorg){
							//per gestire caso in  cui l'ascensore sia tornato indietro da dove è partito
							floor_dest=80;
							floor_sorg=0;
						}
				}
						else{
							if(elevator_alarm==0){
							floor_dest=80;
							floor_sorg=0;
						  enable_timer(1); //60s to press select button of joystick
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
}
void manageEmergencyButton(void){
	/******************************************************
	 ****************** EMERGENCY BUTTON ******************
   ******************************************************/
	
		if(down3!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT0 pressed */
			down3++;	

			
			switch(down3){
				case 2:
					elevator_emergency=1;
					LED_On(3);
					LED_On(1);
			
				disable_timer(3);
				disable_timer(2);
				init_timer(3,0x002FAF08);												// t=0.125 , f=25000000 --> cc=0.125*25000000=3125000 -> 0x002FAF80 BLINK 4Hz
				reset_timer(3);
				enable_timer(3);
				
					break;
				
				case 41: //40 volte --> 2 secondi 
					//activate emergency mode
					elevator_alarm=1;
					EmergencyModeOn();
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			if(down3<41){
			//if accidentally --> 2 cases
				if(elevator_emergency==1 || potential_alarm==1){
					//in emergency mode --> stop emergency
					EmergencyModeOff();
					potential_alarm=0;
				}
			}
			down3=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
}
void manageTouchPanel(void){

/******************************************************************/
	/******************** MANAGEMENT PANEL ****************************/
	/******************************************************************/
	
	getDisplayPoint(&display, Read_Ads7846(), &matrix ) ; //legge punto
	/*sprintf(coord,"%d,%d",display.x,display.y);
	GUI_Text(180,0,(uint8_t *)"       ", Red, Black);
	GUI_Text(180,0,(uint8_t *)coord, Red, Black);*/
	if(elevator_maintenance==0 && elevator_emergency==0 && elevator_reserved==0){
	if(display.x <= 230 && display.x>=180 && display.y>=20 && display.y<=70){
		elevator_maintenance=1;
		DrawManagementPanel();
	}
}
	if(elevator_maintenance==1 && elevator_emergency==0 && elevator_reserved==0){
	if(display.x <= 65 && display.x>=25 && display.y>=265 && display.y<=285){
		//button SAVE pressed
		nbutton=1; //bottone 1 premuto
		ButtonSelection(); //lo seleziono
		if(modTone==1){
			//se sono in modalità modifica del tono, esco 
			modTone=0;
			nbutton=nTone; //disabilito il bottone della selezione
			ButtonDeselection();
		}
		nbutton=1;
		disable_timer(1);
		init_timer(1,0x001312D0); //timer per la corretta visualizzazione della selezione del bottone --> nell'interrupt c'è la deselezione
		reset_timer(1);
		enable_timer(1);
		
	}
	if(display.x <= 210 && display.x>=165 && display.y>=255 && display.y<=285 && modTone==0){
		//button QUIT pressed
		nbutton=2;
		ButtonSelection();
		disable_timer(1);
		init_timer(1,0x001312D0);
		reset_timer(1);
		enable_timer(1);
		elevator_maintenance=0;
		TurnOnPanel();
		init_timer(1,0x59682F00);							// t=60s , f=25000000 --> cc=60*25000000=1500000000 -> 0x59682F00
	  reset_timer(1);
	}
	if(display.x <= 165 && display.x>=65 && display.y>=55 && display.y<=105 && modTone==0){
		//button SELECT 1 pressed
		nbutton=3;
		modTone=1;
		nTone=3;
		ButtonSelection();
		disable_timer(1);
		init_timer(1,0x001312D0);
		reset_timer(1);
		enable_timer(1);
	}
	if(display.x <= 165 && display.x>=65 && display.y>=155 && display.y<=205 && modTone==0){
		//button SELECT 2 pressed
		nbutton=4;
		modTone=1;
		nTone=4;
		ButtonSelection();
		disable_timer(1);
		init_timer(1,0x001312D0);
		reset_timer(1);
		enable_timer(1);
		
		
	}
}
}
void EmergencyModeOn(void){
/*activate emergency mode
						STOP moving
						blink + buzzer
						alarm leds on
				*/
	elevator_emergency=1;
	elevator_alarm=1;
	elevator_moving=0;
	//alarm leds on
	LED_On(3);
	LED_On(1);
	//stop moving -> implementato con flag negli if dei vari pulsanti joystick
	
	disable_timer(0); //timer per il movimento
	disable_timer(2); //timer per riprodurre su speaker
	disable_timer(1); //timer 60s
	//init timer 3 a 4Hz
	disable_timer(3); //timer per blink a 4hz+buzzer
	init_timer(3,0x002FAF08);												// t=0.125 , f=25000000 --> cc=0.125*25000000=3125000 -> 0x002FAF80 BLINK 4Hz
	reset_timer(3);
	enable_timer(3);
	
	
}
void EmergencyModeOff(void){
elevator_emergency=0;
	elevator_alarm=0;
	//elevator_moving=1;
	LED_Off(3);
	LED_Off(1);
	disable_timer(1);
	init_timer(1,0x59682F00);							// t=60s , f=25000000 --> cc=60*25000000=1500000000 -> 0x59682F00
	reset_timer(1);
	disable_timer(3);
	init_timer(3,0x002625A0);							// t=0.1s, f=25000000 --> cc=0.1*25000000=2500000 ->  0x002625A0	BLINK 5Hz
	reset_timer(3);
	disable_timer(2);
	init_timer(2,0x005F5E10);							// t=0.25s , f=25000000 --> cc=0.25*25000000=6250000 -> 0x005F5E10
	reset_timer(2);
}
/******************************************************************************
**                            End Of File

******************************************************************************/
