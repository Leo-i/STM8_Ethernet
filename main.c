#include "stm8l15x.h"

#include "w5500.h"
#include "wizchip_conf.h"
#include "socket.h"

#include <parameters.h>
#include <delay.h>
#include <uart_connection.h>
#include <W5500_driver.h>

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
  W5500_Init();
  
  //Set network information
  wizchip_setnetinfo(&gWIZNETINFO);
  ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);
  uint8_t W5500_buff_size[8] = {2, 2, 2, 2, 2, 2, 2, 2, };
  wizchip_init(W5500_buff_size, W5500_buff_size);
  
  Usart_print("Initialization complete");
}

uint8_t gDATABUF[DATA_BUF_SIZE];

uint8_t error;
char Message[128] = "Hello world, It's a Lev";
int main( void )
{
  sysInit();
  
  while(1){
      
    error = socket(HTTP_SOCKET, Sn_MR_TCP, 80, 0);
    if(error != HTTP_SOCKET){
      Usart_print("socket failed");
    }else{ 
      Usart_print("Socket created, connecting...");
    }
      
    error = listen(HTTP_SOCKET);
    if(error != SOCK_OK){
      Usart_print("listen failed");
    }else{ 
      Usart_print("listen OK");
    }
		
    while(getSn_SR(HTTP_SOCKET) == SOCK_LISTEN){
      delay_ms(200);
    }
    
    Usart_print("Input connection");
    if(getSn_SR(HTTP_SOCKET) != SOCK_ESTABLISHED) Usart_print("Error socket status");
    
    uint8_t rIP[4];
    getsockopt(HTTP_SOCKET, SO_DESTIP, rIP);
    Usart_print(rIP);
		
    send(0, (uint8_t*)Message, 23);
    
    disconnect(HTTP_SOCKET);
    
    Usart_print("Closing socket");
    close(HTTP_SOCKET);
				
    delay_ms(1000);    
  }
  
  
}