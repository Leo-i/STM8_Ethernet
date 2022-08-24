#include "stm8l15x.h"

#include "w5500.h"
#include "wizchip_conf.h"
#include "socket.h"

#include <parameters.h>
#include <delay.h>
#include <uart_connection.h>
#include <W5500_driver.h>
#include <sensor.h>

//send data about ready sensors to host
void eth_send();

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

uint8_t data[255];
uint8_t data_length;
int main( void )
{
  sysInit();
  uint8_t s_num;

  while(1){

    // by timer
    s_num = check_sensors();

    if (s_num != 255){
      data_length = s_get_data(s_num, data);
      eth_send();
      reset_sensor(s_num);
    }

    // listenning
  }
  
  
}

void eth_send(){
  
  uint8_t error;
  error = socket(SOCKET_0, Sn_MR_TCP, 80, 0);
  
  if(error != SOCKET_0){
    Usart_print("Socket failed");
    return;
  }else{ 
    Usart_print("Socket created, connecting...");
  }
      
  uint8_t addr[4] = {S1_IPADDR0, S1_IPADDR1, S1_IPADDR2, S1_IPADDR3};
  error = connect(HTTP_SOCKET,addr,DESTINATION_PORT);
  
  if(error != SOCK_OK){
    Usart_print("Connection failed");
    return;
  }else{ 
    Usart_print("Connection created");
  }

  error = send(0, data, data_length);
  if(error != data_length){
    Usart_print("Sending failed");
    return;
  }else{ 
    Usart_print("data sended");
  }
  
  disconnect(SOCKET_0);
  close(SOCKET_0);
  Usart_print("Close socket");
}