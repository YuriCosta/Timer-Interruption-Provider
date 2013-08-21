author: <Yuri Costa (yurioor@hotmail.com)>
description:
Provides internal interruptions at desired frequency
	
Use like this:
		
	Timer_Interruption_Provider *mTimer_Interruption_Provider;
	mTimer_Interruption_Provider = new Timer_Interruption_Provider();
	mTimer_Interruption_Provider->set_timer( double frequency, int timer );
		
	Where	 0.23828125 < frequency  < 8000000 if you are using timer1 [set_timer( frequency, 1 );]
               61.275390625 < frequency  < 8000000 if you are using timer0 or 2 [set_timer( frequency, 1//2 );]
		
Check out the exemple to see how implement this class.