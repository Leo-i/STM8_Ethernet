
#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#include <parameters.h>
#include <delay.h>
#include <W5500_driver.h>
#include <uart_connection.h>

#include <w5500_reg_access.h>



wiz_NetInfo net_info = 
{
  .mac = {ETHADDR0, ETHADDR1, ETHADDR2, ETHADDR3, ETHADDR4, ETHADDR5},
  .ip = {IPADDR0, IPADDR1, IPADDR2, IPADDR3},
  .sn = {NETMASK0, NETMASK1, NETMASK2, NETMASK3},
  .gw = {DRIPADDR0, DRIPADDR1, DRIPADDR2, DRIPADDR3},
};

uint8_t CR_read_byte(uint16_t offset){
  uint8_t data;
  W5500ReadByte((uint16_t)offset, 0x01, &data, 1);
  return data;
}

void CR_write_byte(uint16_t offset, uint8_t byte){
  W5500WriteByte((uint16_t)offset, 0x05, &byte, 1);
}

void W5500_conf_reg(){
  
  CR_write_byte(0x0001, net_info.gw[0]); //GAR0
  CR_write_byte(0x0002, net_info.gw[1]); //GAR1
  CR_write_byte(0x0003, net_info.gw[2]); //GAR2
  CR_write_byte(0x0004, net_info.gw[3]); //GAR3
  
  CR_write_byte(0x0005, net_info.sn[0]); //SUBR0
  CR_write_byte(0x0006, net_info.sn[1]); //SUBR1
  CR_write_byte(0x0007, net_info.sn[2]); //SUBR2
  CR_write_byte(0x0008, net_info.sn[3]); //SUBR3
  
  CR_write_byte(0x0009, net_info.mac[0]); //SHAR0
  CR_write_byte(0x000A, net_info.mac[1]); //SHAR1
  CR_write_byte(0x000B, net_info.mac[2]); //SHAR2
  CR_write_byte(0x000C, net_info.mac[3]); //SHAR3
  CR_write_byte(0x000D, net_info.mac[4]); //SHAR4
  CR_write_byte(0x000E, net_info.mac[5]); //SHAR5
  
  CR_write_byte(0x000F, net_info.ip[0]); //SIPR0
  CR_write_byte(0x0010, net_info.ip[1]); //SIPR1
  CR_write_byte(0x0011, net_info.ip[2]); //SIPR2
  CR_write_byte(0x0012, net_info.ip[3]); //SIPR3
  
}

//////////////////////////////////////////////////////////////////////////
////////////////// WORK WITH SOCKET REGISTER /////////////////////////////
//////////////////////////////////////////////////////////////////////////

uint8_t Sn_read_byte(uint8_t socket, uint8_t type, uint16_t offset){
  uint8_t data;
  W5500ReadByte(offset, (uint8_t) ((type+4*socket) << 3) | 0x01  , &data, 1);
  return data;
}

void Sn_write_byte(uint8_t socket, uint8_t type, uint16_t offset, uint8_t byte){
  W5500WriteByte(offset, (uint8_t) ((type+4*socket) << 3) | 0x05  , &byte, 1);
}

void W5500_conf_soket_reg(){
  
  Sn_write_byte(0, REG_TYPE, Sn_MR, 0x01); //TCP
  Sn_write_byte(0, REG_TYPE, Sn_PORT1, 0x35); //port number
  
  Sn_write_byte(0, REG_TYPE, 0x0006, S1_ETHADDR0); //SnDHAR0
  Sn_write_byte(0, REG_TYPE, 0x0007, S1_ETHADDR1); //SnDHAR1
  Sn_write_byte(0, REG_TYPE, 0x0008, S1_ETHADDR2); //SnDHAR2
  Sn_write_byte(0, REG_TYPE, 0x0009, S1_ETHADDR3); //SnDHAR3
  Sn_write_byte(0, REG_TYPE, 0x000A, S1_ETHADDR4); //SnDHAR4
  Sn_write_byte(0, REG_TYPE, 0x000B, S1_ETHADDR5); //SnDHAR5
  
  Sn_write_byte(0, REG_TYPE, 0x000C, S1_IPADDR0); //Sn_DIPR0
  Sn_write_byte(0, REG_TYPE, 0x000D, S1_IPADDR1); //Sn_DIPR1
  Sn_write_byte(0, REG_TYPE, 0x000E, S1_IPADDR2); //Sn_DIPR2
  Sn_write_byte(0, REG_TYPE, 0x000F, S1_IPADDR3); //Sn_DIPR3
  
  Sn_write_byte(0, REG_TYPE, 0x001E, 2); //Sn_RXBUF_SIZE 2kb
  Sn_write_byte(0, REG_TYPE, 0x001F, 2); //Sn_TXBUF_SIZE 2kb
  
  Sn_write_byte(0, REG_TYPE, Sn_CR, 0x02); //LISTEN mode
}
