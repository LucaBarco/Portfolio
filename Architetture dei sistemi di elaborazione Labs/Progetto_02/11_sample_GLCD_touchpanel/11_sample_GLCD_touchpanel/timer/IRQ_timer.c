/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int nbutton=0; /*indica quale pulsante è premuto: 
													1: SAVE
													2: QUIT
													3: SELECT 1
													4: SELECT 2*/
													
volatile int modTone=0; //flag -> se 1 sono in modalità modifica tono
void TIMER0_IRQHandler (void)
{
	//static int clear = 0;
	//static int draw = 0;
	//char time_in_char[5] = "";
	//char coord[10];
	static int nTone=0; //indica il numero della selezione del tono coinvolta nella modifica
	
  getDisplayPoint(&display, Read_Ads7846(), &matrix ) ; //legge punto
	/*sprintf(coord,"%d,%d",display.x,display.y);
	GUI_Text(180,0,(uint8_t *)"       ", Red, Black);
	GUI_Text(180,0,(uint8_t *)coord, Red, Black);*/
	
	if(display.x <= 65 && display.x>=25 && display.y>=265 && display.y<=285){
		//button SAVE pressed
		nbutton=1; //bottone 1 premuto
		ButtonSelection(); //lo seleziono
		if(modTone==1){
			//se sono in moddalità modifica del tono, esco 
			modTone=0;
			nbutton=nTone; //disabilito il bottone della selezione
			ButtonDeselection();
		}
		nbutton=1;
		init_timer(1,0x1312D0); //timer per la corretta visualizzazione della selezione del bottone --> nell'interrupt c'è la deselezione
		reset_timer(1);
		enable_timer(1);
		
	}
	if(display.x <= 210 && display.x>=165 && display.y>=255 && display.y<=285 && modTone==0){
		//button QUIT pressed
		nbutton=2;
		ButtonSelection();
		init_timer(1,0x1312D0);
		reset_timer(1);
		enable_timer(1);
		
	}
	if(display.x <= 165 && display.x>=65 && display.y>=55 && display.y<=105 && modTone==0){
		//button SELECT 1 pressed
		nbutton=3;
		modTone=1;
		nTone=3;
		ButtonSelection();
		init_timer(1,0x1312D0);
		reset_timer(1);
		enable_timer(1);
		
		
	}
	if(display.x <= 165 && display.x>=65 && display.y>=155 && display.y<=205 && modTone==0){
		//button SELECT 2 pressed
		nbutton=4;
		modTone=1;
		nTone=4;
		ButtonSelection();
		init_timer(1,0x1312D0);
		reset_timer(1);
		enable_timer(1);
		
		
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
	static int j=0;
	j++;
	if(j==6){ //timer di 50 ms da far eseguire 6 volte
		j=0;
		if(modTone==0 && nbutton!=0){ //se non sono in modalità modifica del tono e se ho effettivamente premuto un tasto, lo disabilito
		ButtonDeselection();
		nbutton=0;
	}
}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
