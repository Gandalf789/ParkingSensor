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
#include "debugPrint.h"
#include "i2cmaster.h"
#include "millis.h"
#include "VL53L0X.h"
#include "vl53l0xExample.h"

void init(void) {
	debugInit();
	//--------------------------------------------------
	// GPIOs
	//--------------------------------------------------
	CBI( UCSR0B, RXEN0 );		// Disable UART RX
	DDRD =  (1<<PIN_UART_TX);	// Set UART TX as output
	// Enable weak pullups on I2C lines
	PORTC = (1<<PIN_I2C_SCL) | (1<<PIN_I2C_SDA);
	//--------------------------------------------------
	// Init the other modules
	//--------------------------------------------------
	i2c_init();
	initMillis();
	sei();
}

int main(){
	init();

	debug_str("\n\n---------------------------------------\n");
	debug_str(" Hello world, this is vl53l0xExample ! \n");
	debug_str("---------------------------------------\nGit: ");
	debug_str( GIT_VERSION );
	debug_putc( '\n' );

	initVL53L0X(1);
	// lower the return signal rate limit (default is 0.25 MCPS)
	// setSignalRateLimit(0.1);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	// setMeasurementTimingBudget( 200 * 1000UL );	// 200 ms per measurement
	startContinuous(0);

	// Main loop
	while(1){
		debug_str("\r");
		debug_dec( readRangeContinuousMillimeters() );
		debug_str(" mm  ");
		if ( timeoutOccurred() ) {
			debug_str(" !!! Timeout !!! ");
		}
	}
	return 0;
}