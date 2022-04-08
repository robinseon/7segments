/*
 * adc.c
 *
 * Created: 08/04/2022 12:57:02
 *  Author: robin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

float sample;
float degree;
int16_t temp;

void adc_init()
{
	// Select input:PK7 is ADC15
	DDRK &= ~_BV(PK7);
	
	//Select Output
	DDRG |= _BV(PG0);

	// And select channel 15 and Set AVCC with external capacitor at AREF pin
	ADMUX |= _BV(REFS0) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
	ADCSRB |= _BV(MUX5);

	//auto trigger source
	ADCSRB |= _BV(ADTS2) | _BV(ADTS0);
	
	//enable auto trigger, choose prescaler : 128, enable ADC and enable interrupt
	ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	
	
	PORTG |= _BV(PG0);
	
}

void adc_read()
{
	ADCSRA |= _BV(ADSC);  /* Start the ADC conversion by setting ADSC bit */
	
	/* Wait till the conversion is over */
	while(ADCSRA&(1<<ADSC))
	{

	}
}

int16_t temp_convertToCelcius()
{
	degree=((((float)ADC*50/1024)*100)-500)/10;//ADC on 2^10 bits so a resolution of 1024. Vref=5V and use the formula : (Vin-500)/10 with Vin=ADC*5/1024
	int16_t temp = (int16_t)degree;//force to INT
	return(temp);
}

//Interrupt ADC --> result of the conversion
ISR(ADC_vect){
	sample=ADC;
}