#include "project.h"
#include "button.h"
#include "rf_process.h"
#include "control.h"
#include "clock.h"

#include "main.h"

int32_t lastTimeTest=0;
#define POS_ADR 0
#define POS_RELAY 1

#ifdef MASTER
    void ControlMaster_Run(void);
#endif

#ifdef SLAVE    
    void ControlSlave_Run(void);
#endif

uint8_t Control_GetAddress(void)
{
    sw_value_t sw;
    sw.value.sw_0=SW1_Read();
    sw.value.sw_1=SW2_Read();
    sw.value.sw_2=SW3_Read();
    sw.value.sw_3=SW4_Read();
    return sw.value_int+1;
    //return 1;
}

void Control_Run(void)
{
    #ifdef MASTER
        ControlMaster_Run();
    #endif
    #ifdef SLAVE
        ControlSlave_Run();
    #endif
}

#ifdef SLAVE
void ControlSlave_Run(void)
{
    if(flag_have_receiver)
    {
        flag_have_receiver=0;
        if(payload_Rx[POS_ADR]==Control_GetAddress())
        {
            relay_value_t relay;
            relay.value_int=payload_Rx[POS_RELAY];
            // cập nhật giá trị relay ra số
            Out1_Write(relay.value.relay1);
            Out2_Write(relay.value.relay2);
            Out3_Write(relay.value.relay3);
            Out4_Write(relay.value.relay4);
            Out5_Write(relay.value.relay5);
            Out6_Write(relay.value.relay6);
            Out7_Write(relay.value.relay7);
            Out8_Write(relay.value.relay8);
        }
    }
}
    
#endif

#ifdef MASTER
void Master_SendCommand(uint8_t adr, uint8_t data)
{
    uint8_t buf[10];
    buf[POS_ADR]=adr;
    buf[POS_RELAY]=data;
    nRF24_TransmitPacket(buf,6);
    nRF24_TransmitPacket(buf,6);
}

uint8_t testValue=0;
uint8_t testIdx=0;
void ControlMaster_Run(void)
{
    if(BtnUp_IsRise())
    {
        Master_SendCommand(Control_GetAddress(),0xFF);//gửi slave 1 ,bật toàn bộ relay
    }
    else if(BtnDown_IsRise())
    {
        Master_SendCommand(Control_GetAddress(),0x00);//gửi slave 1 ,tắt toàn bộ relay
    }
    if(millis()-lastTimeTest>100)
    {
        lastTimeTest=millis();
        if(++testIdx>=8)
            testIdx=0;
        testValue=1<<testIdx;
        Master_SendCommand(Control_GetAddress(),testValue);//gửi slave 1 ,tắt toàn bộ relay
    }
}
#endif


