/*************************************************************
author: <Yuri Costa (yurioor@hotmail.com)>
description:
	Provides internal interruptions at desired frequency
	
	Use like this:
		
		Timer_Interruption_Provider *mTimer_Interruption_Provider;
		mTimer_Interruption_Provider = new Timer_Interruption_Provider();
		mTimer_Interruption_Provider->set_timer( double frequency, int timer );
		
		Where 0.23828125 < frequency  < 8000000 if you are using timer1 [set_timer( frequency, 1 );]
			  61.275390625 < frequency  < 8000000 if you are using timer0 or 2 [set_timer( frequency, 1//2 );]
		
		Check out the exemple to see how implement this class.
*************************************************************/
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

class Timer_Interruption_Provider
{
	 
	protected:
	unsigned int  p, num;
	int calc_p(double hz, int type)
	{
		 
		if(type == 1){
			num = 244;
		}else if((type == 0) |( type ==2)){
			num = 62746;
		} else {
			return 0;
		}
		 
		if( hz > 8000000){ return 0;}//Hz<8000000
		else if( hz > num/1){ return 1; }
		else if( hz > num/8){ return 8;}
		else if ((hz > num/32)& (type == 2)) {return 32;}
		else if (hz > num/64) {return 64;}
		else if ((hz > num/256)& (type != 2)) {return 256;}
		else if ((hz > num/1024)& (type != 2)) {return 1024;}
		else if ((hz <= num/1024)& (type == 2)) {return 0;}//Hz > 0.23828125 | Hz > 61.275390625
		else return 0;
	}

	void set_timer0( double hz)
	{
		 
		p = calc_p(hz, 0);
		 
		TCCR0A = 0;
		TCCR0B = 0;
		TCNT0  = 0;
		OCR0A =(int)(round((16000000.0) / (hz*p))) - 1 ;//(must be <256)
		TCCR0A |= (1 << WGM01);
		switch(p)
		{
			case 1: TCCR0B |=  (1 << CS00);
			break;
			case 8: TCCR0B |= (1 << CS01);
			break;
			case 64: TCCR0B |= (1 << CS01) | (1 << CS00);
			break;
			case 256: TCCR0B |= (1 << CS02);
			break;
			case 1024: TCCR0B |= (1 << CS02) | (1 << CS00);
			break;
			default:;
		}
		 
		TIMSK0 |= (1 << OCIE0A);
	}
	 
	void set_timer1(double hz)
	{
		p = calc_p(hz, 1);
		 
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;
		OCR1A  = (int)(round((16000000.0) / (hz*p))) - 1 ;//(must be <65536)
		TCCR1B |= (1 << WGM12);
		switch(p)
		{
			case 1: TCCR1B |=  (1 << CS10);
			break;
			case 8: TCCR1B |= (1 << CS11);
			break;
			case 64: TCCR1B |= (1 << CS11) | (1 << CS10);
			break;
			case 256: TCCR1B |= (1 << CS12);
			break;
			case 1024: TCCR1B |= (1 << CS12) | (1 << CS10);
			break;
			default:;
		}
		 
		TIMSK1 |= (1 << OCIE1A);
		 
	}
	void set_timer2(double hz)
	{
		 
		p = calc_p(hz, 2);
		 
		 
		 
		TCCR2A = 0;
		TCCR2B = 0;
		TCNT2  = 0;
		OCR2A  = (int)(round((16000000.0) / (hz*p))) - 1 ; //(must be <256)
		TCCR2A |= (1 << WGM21);
		 
		switch(p)
		{
			case 1: TCCR2B |=  (1 << CS20);
			break;
			case 8: TCCR2B |= (1 << CS21);
			break;
			case 32: TCCR2B |= (1 << CS21) | (1 << CS20);
			break;
			case 64: TCCR2B |= (1 << CS22);
			break;
			default:;
		}
		TIMSK2 |= (1 << OCIE2A);
		 
	}
	 
	 public:
		
		Timer_Interruption_Provider()
		{
			
		}
		void set_timer(double hz, int timer)
		{
		cli();
			switch(timer)
			{
				case 0: set_timer0(hz);
				break;
				case 1: set_timer1(hz);
				break;
				case 2: set_timer2(hz);
				break;
		}
		sei();
		}
	 
};