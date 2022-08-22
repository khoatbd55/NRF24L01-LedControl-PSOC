#ifndef _CONTROL_H_
#define _CONTROL_H_
    
#include "cytypes.h"
    
struct relay_value_s
{
    uint8_t relay1:1;  
    uint8_t relay2:1;  
    uint8_t relay3:1;  
    uint8_t relay4:1;  
    uint8_t relay5:1;  
    uint8_t relay6:1;  
    uint8_t relay7:1;  
    uint8_t relay8:1;  
}CY_PACKED_ATTR;

struct sw_value_s
{
    uint8_t sw_0:1;
    uint8_t sw_1:1;
    uint8_t sw_2:1;
    uint8_t sw_3:1;
    uint8_t reserver:4;
}CY_PACKED_ATTR;

typedef union sw_value_t sw_value_t;
union sw_value_t
{
    struct sw_value_s value;
    uint8_t value_int;
}CY_PACKED_ATTR;

typedef union relay_value_t relay_value_t;
union relay_value_t
{
    struct relay_value_s value;
    uint8_t value_int;
}CY_PACKED_ATTR;

void Control_Run(void);
    
#endif
