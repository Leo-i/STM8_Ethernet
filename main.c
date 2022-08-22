#include "stm8l15x.h"

#include "w5500.h"
#include "wizchip_conf.h"
#include "socket.h"

#include <parameters.h>
#include <delay.h>
#include <uart_connection.h>
#include <W5500_driver.h>
#include <sensor.h>

wiz_NetInfo gWIZNETINFO = 
{
  .mac = {ETHADDR0, ETHADDR1, ETHADDR2, ETHADDR3, ETHADDR4, ETHADDR5},
  .ip = {IPADDR0, IPADDR1, IPADDR2, IPADDR3},
  .sn = {NETMASK0, NETMASK1, NETMASK2, NETMASK3},
  .gw = {DRIPADDR0, DRIPADDR1, DRIPADDR2, DRIPADDR3},
  .dns = {DRIPADDR0, DRIPADDR1, DRIPADDR2, DRIPADDR3},
  .dhcp = NETINFO_STATIC  // NETINFO_STATIC
};

void sysInit(){
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  Usart_Init();
  //W5500_Init();
  init_sensors();
  
  //Set network information
 // wizchip_setnetinfo(&gWIZNETINFO);
  //ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);
  //uint8_t W5500_buff_size[8] = {2, 2, 2, 2, 2, 2, 2, 2, };
  //wizchip_init(W5500_buff_size, W5500_buff_size);
  
  //Usart_print("Initialization complete");
}

uint8_t gDATABUF[DATA_BUF_SIZE];

uint8_t error;
char Message[128] = "Hello world, It's a Lev";
int main( void )
{
  sysInit();

  uint8_t s_num = 12;
  USART_SendData8(USART1,s_num);
  s_get_data(0,&s_num);
  USART_SendData8(USART1,s_num);

  while(1){


    // by timer
    //s_num = check_sensors();

    if (s_num != 0){
      //data = s_get_data(s_num);
      //send();
      //s_reset(s_num);
    }

    // listenning


  }
  
  
}