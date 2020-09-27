#include "lpc17xx.h"
#include "dac.h"

/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void DAC_init (void) {
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
}

void DAC_convert (int value) {
	LPC_DAC->DACR = value;
}				 
