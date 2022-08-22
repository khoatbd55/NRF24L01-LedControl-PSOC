#include "project.h"
#include "clock.h"
#include "button.h"


#define BTN_STATE_OFF 0
#define BTN_STATE_ON 1
#define MAX_INPUT 2
INPUT_STATE input_state[MAX_INPUT];
int32_t lastTimeBtnHoldDown[MAX_INPUT];
#define TIME_HOLD_DOWN 1200 // thời gian giữ phím
#define BUTTON_UP 0
#define BUTTON_DOWN 1
//#define BUTTON_ENTER 8
//#define BUTTON_DISABLE 9
#define MAX_INT 320000
#define MIN_INT -320000



#define MAX_LOOP 40
#define SW_LOW 12
#define SW_HIGH 24

void Button_Init(void)
{
    
}
uint16_t Button_GetData(void)
{
    btn_value_t btn;
    btn.value.up=BTN_UP_Read();
    btn.value.down=BTN_DOWN_Read();
    
    btn.value.reserver=0;
    
    return btn.value_int;
    
}
void Button_Scan(void)
{
    static uint16_t loop=0;
    // scan
    uint16_t databtn=Button_GetData();
    for(uint8_t i=0;i<MAX_INPUT;i++)
    {
        if((databtn &(1<<i))==0x00)
        {
            input_state[i].cnt++;
        }
    }
    if(++loop>=MAX_LOOP)
    {
        for(uint8_t i=0;i<MAX_INPUT;i++)
        {
            if(input_state[i].on)
            {
                if(input_state[i].cnt<SW_LOW)
                {
                    input_state[i].on=0;
                    input_state[i].fall=1;
                    input_state[i].rise=0;
                }
            }
            else
            {
                if(input_state[i].cnt>SW_HIGH)
                {
                    input_state[i].on=1;
                    input_state[i].rise=1;
                    input_state[i].fall=0;
                    
                }
            }
            input_state[i].cnt=0;
            loop=0;
        }
    }
}
//============================= Giữ phim ====================================//

uint8_t BtnUp_HoldDown(void)
{
    if(input_state[BUTTON_UP].on)
    {
        if(millis()-lastTimeBtnHoldDown[BUTTON_UP]>=TIME_HOLD_DOWN)
        {
            return 1;// nhấn giữ 
        }
    }
    else
    {
        lastTimeBtnHoldDown[BUTTON_UP]=millis();
        
    }
    return 0;
}
uint8_t BtnDown_HoldDown(void)
{
    if(input_state[BUTTON_DOWN].on)
    {
        if(millis()-lastTimeBtnHoldDown[BUTTON_DOWN]>=TIME_HOLD_DOWN)
        {
            return 1;// nhấn giữ 
        }
    }
    else
    {
        lastTimeBtnHoldDown[BUTTON_DOWN]=millis();
        
    }
    return 0;
}


// ======================================== Nhấn nhả ================================//

uint8_t BtnUp_IsRise(void)
{
    if(input_state[BUTTON_UP].rise)
    {
        input_state[BUTTON_UP].rise=0;
        return 1;
    }
    return 0;
}



uint8_t BtnDown_IsRise(void)
{
    if(input_state[BUTTON_DOWN].rise)
    {
        input_state[BUTTON_DOWN].rise=0;
        return 1;
    }
    return 0;
}

