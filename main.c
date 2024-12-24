#define __ATMEGA328P__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2cmaster.h"
#include "millis.h"
#include "VL53L0X.h"
#include "display.h"

statInfo_t xTraStats;



int main()
{
    DDRD |= 0b10111111;
    DDRB |= (1<<0) | (1<<4) | (1<<5);
    DDRC |= (1<<3) | (1<<2);
    i2c_init();
	initMillis();
	sei();

    initVL53L0X(1);
	// lower the return signal rate limit (default is 0.25 MCPS)
	// setSignalRateLimit(0.1);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	setMeasurementTimingBudget( 500 * 1000UL );		// integrate over 500 ms per measurement

	while(1){
		readRangeSingleMillimeters( &xTraStats );	// blocks until measurement is finished
		Display(1, xTraStats.rawDistance % 10, 0);
		Display(2, (xTraStats.rawDistance/10) % 10, 0);
		Display(3, (xTraStats.rawDistance/ 100) % 10, 0);
		Display(4, (xTraStats.rawDistance/1000) % 10, 0);


		if ( timeoutOccurred() ) {
		}
	}
	return 0;
}

