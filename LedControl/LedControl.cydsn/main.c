/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "nrf24.h"
#include "clock.h"
#include "rf_process.h"
#include "control.h"
#include "main.h"

int main(void)
{
    
    SPI_NRF_Start();
    Init_Timer();
    CyGlobalIntEnable; /* Enable global interrupts. */
//    nRF24_SetPowerMode(nRF24_PWR_DOWN);
//    nRF24_Check();
#ifdef  MASTER
    nRF24_MasterInit();
#endif
#ifdef  SLAVE
    nRF24_SlaveInit();
#endif
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        TimeRun();
    #ifdef SLAVE
        nRF24_RxRun();
    #endif
        Control_Run();
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
