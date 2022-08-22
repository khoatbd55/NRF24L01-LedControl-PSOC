#ifndef _BUTTON_H_
#define _BUTTON_H_


void Button_Init(void);
void Button_Run(void);

#include "cytypes.h"

typedef struct INPUT_STATE
{
    uint8 on;
    uint8 rise;
    uint8 fall;
    uint16 cnt;
}INPUT_STATE; 
void Button_Scan(void);

struct btn_value_s
{
    uint8_t up:1;
    uint8_t down:1;
    uint8_t reserver:6;
}CY_PACKED_ATTR;

typedef union btn_value_t btn_value_t;
union btn_value_t
{
    struct btn_value_s value;
    uint16_t value_int;
}CY_PACKED_ATTR;

uint8_t BtnUp_IsRise(void);
uint8_t BtnDown_IsRise(void);

#endif
