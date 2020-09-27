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


extern int elevator_up,elevator_down,elevator_select,elevator_moving,elevator_reserved,elevator_alarm,floor_sorg,floor_dest,position,elevator_emergency,potential_alarm,elevator_maintenance,suono,modTone,nbutton;
extern int note1,note2;
uint16_t SinTable[45] =                                       
{
154,175,196,216,235,
252,248,281,291,299,
305,307,306,302,296,
286,275,260,244,226,
206,185,164,143,122,
101,81,63,47,32,
21,11,5,1,0,2,8,16,
26,39,55,72,91,111,132
}; //ridotta al 30.%

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
	
	if(elevator_alarm==0){
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
			disable_timer(3);
			init_timer(3,0x002625A0);							// t=0.1s, f=25000000 --> cc=0.1*25000000=2500000 ->  0x002625A0	BLINK 5Hz
			reset_timer(3);
			enable_timer(3);
			floor_sorg=position;
			floor_dest=80-position;
		}
		else if (elevator_reserved==1 && elevator_select==1 ){
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
			disable_timer(3);
			//init_timer(3,0x002625A0);							// t=0.1s, f=25000000 --> cc=0.1*25000000=2500000 ->  0x002625A0	BLINK 5Hz
			//reset_timer(3);
			enable_timer(3);
			disable_timer(1);
			reset_timer(1);
			//enable_timer(1);
		}
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
	static int j=0;
	
	if(elevator_maintenance==0 && elevator_alarm==0){
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
		EmergencyModeOn();
	}
}
	else{
	
		
		if(elevator_maintenance==1){
		j++;
		if(j==6){ //timer di 50 ms da far eseguire 6 volte
			j=0;
			if(modTone==0 && nbutton!=0 && elevator_maintenance==1){ //se non sono in modalità modifica del tono e se ho effettivamente premuto un tasto, lo disabilito
			ButtonDeselection();
			nbutton=0;
				}
			}
		}
	
	
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
	static int ticks=0;
	if(elevator_emergency==1){
		/* DAC management */	
	DAC_convert (SinTable[ticks]<<6);
	ticks++;
		if(ticks==45)
			ticks=0;
	}else{
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
	int vettK[13]={1062,1125,1192,1263,1339,1417,1502,1592,1684,1786,1890,2006,2120};
//vettore delle frequenze
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
	static int i3=0;
			
	if(i3%2==0){
		LED_On(7);
		if(elevator_emergency==1){
				init_timer(2,vettK[note1]);
				reset_timer(2);
				enable_timer(2);
		}
		
	}
	else{
		LED_Off(7); 
		if(elevator_emergency==1){
				init_timer(2,vettK[note2]);
				reset_timer(2);
				enable_timer(2);
		}
	}
	i3++;

	
if(elevator_emergency==1){
	if(i3==10){
		i3=0;
	}
	}
else{
		if(i3==30){ 
		disable_timer(3);
		reset_timer(3);
		elevator_moving=0; //elevator movement ends after the end of 5Hz 3second blinking
		if(elevator_reserved==0){
		LED_Out(0x00); //turn off all leds
		}
	i3=0;
		}
	}
	

  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
