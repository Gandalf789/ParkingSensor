#define __AVR_ATmega328P__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2cmaster.h"
#include "millis.h"
#include "VL53L0X.h"
#include "display.h"
#include "timers.h"


statInfo_t xTraStats;

volatile uint16_t ms = 0, s = 0, m = 0;
volatile uint16_t val = 0;
volatile int digit = 0;

ISR(TIMER1_COMPA_vect)
{

   if (ms == 1000){
      s++;
      ms = 0;
	  startContinuous(0);
      if(s == 60){
         s = 0;
         m++;
   		}
   	}

	if( ms == 20)
	{
		stopContinuous();
		ms++;
	}

	else 
	{
		ms++;	
	}


	
}

// ISR(TIMER1_COMPB_vect)
// {

// }


int main()
{

	init_PWM2A();
    i2c_init();
	initMillis();
	sei();
	init_timer1();

	DDRD |= 0b11111111;
    DDRB |= 0b00110011;

//	DDRB |= (1<<3); //OCR2A 

   	initVL53L0X(1); 
	
	// lower the return signal rate limit (default is 0.25 MCPS)
	//setSignalRateLimit(0.25);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	//setMeasurementTimingBudget( 500 * 1000UL );		// integrate over 500 ms per measurement

	//startContinuous(0);

	while(1){

		val = readRangeContinuousMillimeters(&xTraStats);
		Display(1,s%10, 0); 
		Display(2,(s/10)%10, 1); 
      	Display(3, val%10, 0); 
      	Display(4,(val/10)%10, 0); 
  
		//TODO
		// // put the measurement in a ISR
		// Display(1, xTraStats.rawDistance % 10, 0);
		// Display(2, (xTraStats.rawDistance/10) % 10, 0);
		// Display(3, (xTraStats.rawDistance/ 100) % 10, 0);
		// Display(4, (xTraStats.rawDistance/1000) % 10, 0);
		//readRangeSingleMillimeters( &xTraStats );	// blocks until measurement is finished

		// if(xTraStats.rawDistance < 100)
		// {
		// 	DDRB |= (1<<3);
		// }
		// else
		// {
		// 	DDRB &= ~(1<<3);
		// }
		
		// if ( timeoutOccurred() ) {
		// }
	}
	return 0;
}
