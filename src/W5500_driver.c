
#include "stm8l15x.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_spi.h"

#include "w5500.h"
#include "wizchip_conf.h"
#include "socket.h"

#include <parameters.h>
#include <delay.h>
#include <W5500_driver.h>

// defenitions of all ports
Port reset = {GPIOC, GPIO_Pin_4 , GPIO_Mode_Out_PP_High_Fast};
Port CS = {GPIOB, GPIO_Pin_4 , GPIO_Mode_Out_PP_High_Fast};
Port intterupt = {GPIOC, GPIO_Pin_6 , GPIO_Mode_Out_PP_High_Fast};

void W5500_Reset(void)
{
  GPIO_WriteBit(reset.GPIOx, reset.pin, RESET);
  delay_us(500);
  GPIO_WriteBit(reset.GPIOx, reset.pin, SET);;
  delay_ms(1);
}

void SPI1_Init(){
  
  SPI_DeInit(SPI1);
  delay_ms(1);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI1,ENABLE);
  
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_Pin_5, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_Pin_6, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_Pin_7, ENABLE);
  
  SPI_Init(SPI1, 
           SPI_FirstBit_MSB,
           SPI_BaudRatePrescaler_8,
           SPI_Mode_Master, 
           SPI_CPOL_Low,
           SPI_CPHA_1Edge, 
           SPI_Direction_2Lines_FullDuplex,
           SPI_NSS_Soft, 
           0);
  
  SPI_NSSInternalSoftwareCmd(SPI1, ENABLE);
  SPI_Cmd(SPI1, ENABLE);
}

void W5500_Init(void)
{
  GPIO_Init( reset.GPIOx, reset.pin, reset.mode );
  GPIO_Init( CS.GPIOx, CS.pin, CS.mode );
  
  SPI1_Init();
  
  W5500DeSelect();
  
  /* spi function register */
  reg_wizchip_spi_cbfunc(W5500ReadByte, W5500WriteByte);

  /* CS function register */
  reg_wizchip_cs_cbfunc(W5500Select, W5500DeSelect);

  W5500_Reset();
  W5500DeSelect();

}

void W5500Select(void)
{
  GPIO_WriteBit(CS.GPIOx, CS.pin, RESET);
}

void W5500DeSelect(void)
{
  while(SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY)){;}
  GPIO_WriteBit(CS.GPIOx, CS.pin, SET);
}

void W5500WriteByte(uint8_t byte)
{
  SPI_SendData(SPI1, byte);
  while(SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY)){;}
}

uint8_t W5500ReadByte(void)
{   
    while(SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE))
      SPI_ReceiveData(SPI1);
  
    while(SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY)){;}
    SPI_SendData(SPI1, 0x00);
    
    while(SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY)){;} 
    return SPI_ReceiveData(SPI1);  
}


