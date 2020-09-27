/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */
extern int note; //indice per accedere al vettore delle frequenze, inizializzato ad A (indice 3)
extern int modTone; //flag che indica se sono in modalità di modifica del tono di allarme
extern int nTone; //indica quale pulsante select ho premuto (3-->1, 4-->2)
static char NameNote[14][12]={
	"523 Hz - C",
	"494 Hz - B",
	"466 Hz - Bb",
	"440 Hz - A",
	"415 Hz - Ab",
	"392 Hz - G",
	"370 Hz - Gb",
	"349 Hz - F",
	"330 Hz - E",
	"311 Hz - Eb",
	"294 Hz - D",
	"277 Hz - Db",
	"262 Hz - C",
	"           "}; //matrice di messaggi da stampare

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(modTone==1){
		//se sono nella modifica di un tono --> devo stampare sul display e devo modificare la nota
		//NB capire come funziona la selezione delle due note
	if(AD_current != AD_last){
		note=AD_current*12/0xFFF; //scelta della nota attraverso scelta dell'indice "note"
		if(nTone==3){
				GUI_Text(77,100, (uint8_t *) NameNote[13],Blue,White);
				GUI_Text(77,100, (uint8_t *) NameNote[note],Blue,White);
		}
		if(nTone==4){
				GUI_Text(75,200, (uint8_t *) NameNote[13],Blue,White);
				GUI_Text(75,200, (uint8_t *) NameNote[note],Blue,White);
		}
		AD_last = AD_current;
  }
}
}
