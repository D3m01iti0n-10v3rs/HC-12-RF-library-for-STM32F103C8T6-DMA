#ifndef UART_DMA_HC12_H
#define UART_DMA_HC12_H

#include "main.h"

extern uint8_t uart_rxBuffer[128];
extern uint8_t uart_txBuffer[128];

void getRespond(char* msg);

void hc12_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint16_t baudRate, uint8_t channel, uint8_t mode);

void hc12_send(const char* data);
void hc12_send_raw(const uint8_t* data, uint16_t len);
void hc12_receive(void);
void hc12_clear_rx(void);

#endif /* UART_DMA_HC12_H_ */
