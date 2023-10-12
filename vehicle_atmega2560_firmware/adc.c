/**
 * \file adc.c
 *
 * \date Created: 26.09.2018 12:31:36
 * \author maczijewski
 * 
 * \brief Provides an interface for measuring battery voltage and motor current.
 * 
 * \ingroup low_level_controller
 */ 

#include "adc.h"
#include "util.h"
#include <util/delay.h>
#include <avr/io.h>


// The ADC is used to measure the battery voltage and the motor current sense.
// Battery: ADC9, use 1.1V reference, battery voltage is scaled appropriately with a voltage divider.
// Current Sense: ADC8, range: 0 mV to about 500 mV => use 1.1V reference


void adc_measure(uint16_t* battery_voltage, uint16_t* current_sense) {
	
	
	// battery measurement	
	SET_BIT(ADMUX, MUX0); // mux 100001 for ADC9
	_delay_us(125);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC) );
	*battery_voltage = ADC;	
	

	_delay_us(125);
	
	
	// current sense measurement	
	CLEAR_BIT(ADMUX, MUX0); // mux 100000 for ADC8
	_delay_us(125);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC) );
	*current_sense = ADC;
}


void adc_setup() {
	SET_BIT(ADCSRA, ADEN); // enable ADC
	SET_BIT(ADMUX, REFS1); // 1.1V reference
	SET_BIT(ADCSRB, MUX5); // mux[5:0] = 10000X for ADC8 or ADC9
	
	// set prescaler 128
	SET_BIT(ADCSRA, ADPS2);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS0);
}