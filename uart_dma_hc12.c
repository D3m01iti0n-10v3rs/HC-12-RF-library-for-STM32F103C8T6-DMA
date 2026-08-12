#include "uart_dma_hc12.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

uint8_t uart_rxBuffer[128];
uint8_t uart_txBuffer[128];

void hc12_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint16_t baudRate, uint8_t channel, uint8_t mode){
	char cmd[16];
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);

	sprintf(cmd,"AT+B%u", baudRate);
	hc12_send(cmd);
	HAL_Delay(100);

    if(channel < 100) {
        sprintf(cmd, "AT+C%03u", channel);
    } else {
        sprintf(cmd, "AT+C%u", channel);
    }
	hc12_send(cmd);
	HAL_Delay(100);

	sprintf(cmd,"AT+FU%u", mode);
	hc12_send(cmd);
	HAL_Delay(100);

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

void getRespond(char* msg){
    if (msg == NULL) return;
    strncpy(msg, (char*)uart_rxBuffer, 16);
}

void hc12_send(const char* data) {
    int len = strlen(data);
    strncpy((char*)uart_txBuffer, data, len);
    HAL_UART_Transmit_DMA(&huart2, uart_txBuffer, len);
}

void hc12_receive(void){
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, uart_rxBuffer, 128);
}

void hc12_send_raw(const uint8_t* data, uint16_t len) {
    for(int i = 0; i < len; i++) {
        uart_txBuffer[i] = data[i];
    }
    HAL_UART_Transmit_DMA(&huart2, uart_txBuffer, len);
}

void hc12_clear_rx(void) {
    memset(uart_rxBuffer,0,128);
}

