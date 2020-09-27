#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

void EINT0_IRQHandler (void)	  
{
	//reset
	set_led_value(0);
	LED_Off(0);
	LED_Off(1);
	LED_Off(2);
	LED_Off(3);
	LED_Off(4);
	LED_Off(5);
	LED_Off(6);
	LED_Off(7);
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	//incremento
	char cont=get_led_value();
	cont++;
	set_led_value(cont);
	showLed(cont);
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	//decremento
	char cont=get_led_value();
	cont--;
	set_led_value(cont);
	showLed(cont);

  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


void showLed(char num){
	//funzione che accende il contatore
int i,mask=1,r;
	for(i=0;i<8;i++){
		r=num&mask;
		if(r==0){
			LED_Off(i);
		}
		else{
			LED_On(i);
		}
		mask=mask<<1;
	}
}
