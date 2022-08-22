/*
 * _tProcessRf.h
 *
 *  Created on: Dec 14, 2020
 *      Author: kirin
 */

#ifndef INC__TPROCESSRF_H_
#define INC__TPROCESSRF_H_

#include "nrf24.h"

// Result of packet transmission
typedef enum {
	nRF24_TX_ERROR  = (uint8_t)0x00, // Unknown error
	nRF24_TX_SUCCESS,                // Packet has been transmitted successfully
	nRF24_TX_TIMEOUT,                // It was timeout during packet transmit
	nRF24_TX_MAXRT                   // Transmit failed with maximum auto retransmit count
} nRF24_TXResult;
//#define nRF24_WAIT_TIMEOUT         (uint32_t)0x000FFFFF
#define nRF24_WAIT_TIMEOUT         		1000

#define MAX_PAYLOAD						10


nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length);

void nRF24_TxRun(uint8_t timeout_tx);
void nRF24_RxRun();
extern uint8_t payload_Rx[MAX_PAYLOAD];
extern uint8_t flag_have_receiver;

#endif /* INC__TPROCESSRF_H_ */
