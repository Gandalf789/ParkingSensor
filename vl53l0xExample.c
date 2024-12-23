/*
 * vl53l0xExample.c
 *
 *  Created on: July 3, 2017
 *      Author: michael
 *
 *  Demonstrate the VL53I0X distance sensor.
 * 
 */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2cmaster.h"
#include "millis.h"
#include "VL53L0X.h"

void init(void) {
	i2c_init();
	initMillis();
	sei();
}

int main(){
	statInfo_t xTraStats;
	init();

	DDRD |= (1<<7);
	PORTD |= (1<<7);
	initVL53L0X(1);
	// lower the return signal rate limit (default is 0.25 MCPS)
	// setSignalRateLimit(0.1);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	setMeasurementTimingBudget( 500 * 1000UL );		// integrate over 500 ms per measurement

	// Main loop	
	while(1){
		readRangeSingleMillimeters( &xTraStats );	// blocks until measurement is finished
		
		if(xTraStats.rawDistance < 100)
		{
			DDRD ^= (1<<7);
		}
		// debug_str(   "\n\nstatus  = ");
		// debug_hex( xTraStats.rangeStatus, 1 );
		// debug_str(     "\ndist    = ");
		// debug_dec( xTraStats.rawDistance );
	 	// debug_str(  " mm\nsignCnt = ");
		// debug_dec_fix( xTraStats.signalCnt,  7 );
		// debug_str(" MCPS\nambiCnt = ");
		// debug_dec_fix( xTraStats.ambientCnt, 7 );
		// debug_str(" MCPS\nspadCnt = ");
		// debug_dec_fix( xTraStats.spadCnt,    8 );
		if ( timeoutOccurred() ) {
		}
	}
	return 0;
}