
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
  setSHAR(gWIZNETINFO.mac);
  
  Usart_print("Initialization complete");
}
uint8_t data_buf[20] = "Hello world. I'm Lev";
int main( void )
{
  sysInit();
  
  
    while(1){
    socket(SOCKET_0, MACRAW_protocol, 0x0138, 2);
    delay_ms(200);
    send(SOCKET_0,data_buf,20);
    delay_ms(200);
    close(SOCKET_0);
  }
  
  
}



