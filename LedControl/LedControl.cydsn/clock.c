#include "project.h"
#include "button.h"

unsigned int giay,ticktac;
unsigned char timeChange=0;
unsigned char secondChange;
CY_ISR_PROTO(interrupt_timer);
int32_t milisec;
int32_t millis(void)
{
    return milisec;
}
void MiliSec_Run(void)
{
//    static uint8_t i=0;
//    if(++i>=4)
//    {
//        milisec++;
//        i=0;
//    }
    milisec++;
    
}


void Init_Timer(void)
{
    Timer_Start();
    isr_timer_StartEx(interrupt_timer);
}
void ClockTimer(void)
{
	static unsigned int cnt=0;
	if(++cnt>=100)// 
	{
		cnt=0;
		if(++ticktac>=10)
		{
			ticktac=0;
			if(++giay>=60)
				giay=0;
		}
			
	}
}
uint8_t IsTickChange(void)
{
    return timeChange;
}
unsigned char IsSecondChange(void)
{
    return secondChange;
}
void TimeRun(void)
{
	static unsigned char old_tick,new_tick;
    static unsigned char old_sec,new_sec;
	old_tick=new_tick;
	new_tick=ticktac;
	if(old_tick!=new_tick)
	{
		timeChange=1;
	}
	else
		timeChange=0;
    // clock 1s 
    old_sec=new_sec;
    new_sec=giay;
    if(old_sec!=new_sec)
    {
        secondChange=1;
    }
    else
        secondChange=0;
	
}
CY_ISR(interrupt_timer)
{
    Timer_ClearInterrupt(Timer_INTR_MASK_TC);
    ClockTimer();
    MiliSec_Run();
    Button_Scan();
}
