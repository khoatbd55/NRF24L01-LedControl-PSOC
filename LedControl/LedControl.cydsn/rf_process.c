
#include "project.h"
#include "clock.h"
#include "rf_process.h"
//#include "led_indicator.h"
uint32_t i,j,k;

// Buffer to store a payload of maximum width
uint8_t nRF24_payload[MAX_PAYLOAD];
uint8_t payload_Rx[MAX_PAYLOAD]={};
uint8_t flag_have_receiver = 1;

#define nRF24_CE_L SPI_NRF_CE_Write(0);
#define nRF24_CE_H SPI_NRF_CE_Write(1);

// Pipe number
nRF24_RXResult pipe;

// Length of received payload
uint8_t payload_length;



// Result of packet transmission
//typedef enum {
//	nRF24_TX_ERROR  = (uint8_t)0x00, // Unknown error
//	nRF24_TX_SUCCESS,                // Packet has been transmitted successfully
//	nRF24_TX_TIMEOUT,                // It was timeout during packet transmit
//	nRF24_TX_MAXRT                   // Transmit failed with maximum auto retransmit count
//} nRF24_TXResult;

nRF24_TXResult tx_res;

// Function to transmit data packet
// input:
//   pBuf - pointer to the buffer with data to transmit
//   length - length of the data buffer in bytes
// return: one of nRF24_TX_xx values
nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length) {
	volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
	uint8_t status;

	// Deassert the CE pin (in case if it still high)
	nRF24_CE_L;

	// Transfer a data from the specified buffer to the TX FIFO
	nRF24_WritePayload(pBuf, length);

	// Start a transmission by asserting CE pin (must be held at least 10us)
	nRF24_CE_H;
	//HAL_Delay(1);

	// Poll the transceiver status register until one of the following flags will be set:
	//   TX_DS  - means the packet has been transmitted
	//   MAX_RT - means the maximum number of TX retransmits happened
	// note: this solution is far from perfect, better to use IRQ instead of polling the status
	do {
		status = nRF24_GetStatus();
		if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT)) {
			break;
		}
	} while (wait--);

	// Deassert the CE pin (Standby-II --> Standby-I)
	nRF24_CE_L;

	if (!wait) {
		// Timeout
		return nRF24_TX_TIMEOUT;
	}

	// Check the flags in STATUS register
//	UART_SendStr("[");
//	UART_SendHex8(status);
//	UART_SendStr("] ");

	// Clear pending IRQ flags
    nRF24_ClearIRQFlags();

	if (status & nRF24_FLAG_MAX_RT) {
		// Auto retransmit counter exceeds the programmed maximum limit (FIFO is not removed)
		return nRF24_TX_MAXRT;
	}

	if (status & nRF24_FLAG_TX_DS) {
		// Successful transmission
		return nRF24_TX_SUCCESS;
	}

	// Some banana happens, a payload remains in the TX FIFO, flush it
	nRF24_FlushTX();

	return nRF24_TX_ERROR;
}



void nRF24_TxRun(uint8_t timeout_tx)
{
	static uint32_t timeout_cur = 0;

	if(millis() - timeout_cur > timeout_tx )
	{
		//nRF24_TransmitPacket(payload_TX, sizeof(payload_Tx));
		timeout_cur = millis();
	}
}

//static uint8_t temp_led = 0;
static uint32_t tick_timeout = 0;

void nRF24_RxRun()
{
	if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
	    // Get a payload from the transceiver
		nRF24_ReadPayload(nRF24_payload, &payload_length);
		for(uint8_t i = 0; i <payload_length; i++)
		{
			payload_Rx[i] = nRF24_payload[i];
		}

//		temp_led = !temp_led;
//		if(temp_led)
//		{
//			led_status |= 1; // led dau tien
//		}
//		else
//		{
//			led_status = led_status &( ~0x01);
//		}

		tick_timeout = millis();
		flag_have_receiver = 1;
		nRF24_FlushRX();
	}

//	if(millis() - tick_timeout > 200) // 200ms have not payload
//	{
//		flag_have_receiver = 1;
//		//led_status = led_status &( ~0x01);
//	}
}