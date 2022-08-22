#ifndef  __CLOCK_H_
#define  __CLOCK_H_  
    
#include "cytypes.h"   
void Init_Timer(void);    
uint8_t IsTickChange(void); 
unsigned char IsSecondChange(void);
void TimeRun(void);    
int32_t millis(void);    
    
    
    
    
#endif    
