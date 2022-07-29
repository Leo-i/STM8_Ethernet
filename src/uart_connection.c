
#include "stm8l15x.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_usart.h"

#include <parameters.h>
#include <delay.h>

void Usart_Init(){  
  
  GPIO_Init( GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast );
    
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
  USART_Init(   USART1,USART_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No,
               (USART_Mode_Tx|USART_Mode_Rx));
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  USART_Cmd(USART1,ENABLE);
}


void Usart_print(char* buff){

  uint8_t i = 0;
  while(buff[i]!=0x00){
    USART_SendData8(USART1, buff[i]);
    i++;
    delay_us(100);
  }
  USART_SendData8(USART1, '\r');
  delay_us(100);
  USART_SendData8(USART1, '\n');

}


uint8_t uart_buff;
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQn, 28){
   uart_buff = USART_ReceiveData8(USART1);
   //USART_SendData8(USART1, buff);
}