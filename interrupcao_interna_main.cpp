/*************************************************************
author: <Yuri de Castro Costa>
description:
	Exemple of implementation of the Timer_Interruption_Provider class.
	In his exemple Timer2 is set to interrupt 8000 times per second, incrementing
		a counter. The Loop checks if the counter is more than 8000, making a led
		blink every 2 seconds (1 second off, 1 second on).
		
*************************************************************/
 
#include "interrupcao_interna_main.h"
#include "tip.h"
 #include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>


int flag = 0, cont = 0;
 
void setup() {
	 
	 pinMode( 8, OUTPUT);
	 pinMode( 6, OUTPUT);
	 digitalWrite(6, 0);
	
	Timer_Interruption_Provider *tip;
	tip = new Timer_Interruption_Provider();
	
	tip->set_timer(8000, 2);
	 
}
 
void loop() {
	if( cont >= 8000)
	{
		flag = !flag;
	digitalWrite(8, flag);
	cont = 0;
	}
}
 ISR(TIMER0_COMPA_vect)
{
	
	cont++;

}
 ISR(TIMER1_COMPA_vect)
{
	flag = !flag;
	digitalWrite(8, flag);
	cont = 0;

}
 ISR(TIMER2_COMPA_vect)
{
	
	cont++;

}

