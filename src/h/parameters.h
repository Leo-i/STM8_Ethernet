
#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#define SOCKET_0        0
#define SOCKET_1        1

#define TCP_protocol    0x01
#define UDP_protocol    0x02
#define MACRAW_protocol 0x04

#define USART_BAUDRATE 115200

typedef struct{
  GPIO_TypeDef* GPIOx;
  GPIO_Pin_TypeDef pin;
  GPIO_Mode_TypeDef mode;
} Port;

// MAC-addr
#define ETHADDR0        0x00 // The first octet of the Ethernet address 
#define ETHADDR1        0x08 // The second octet of the Ethernet address
#define ETHADDR2        0xDC // The third octet of the Ethernet address 
#define ETHADDR3        0x47 // The fourth octet of the Ethernet address
#define ETHADDR4        0x47 // The fifth octet of the Ethernet address 
#define ETHADDR5        0x54 // The sixth octet of the Ethernet address 
// IP-addr
#define IPADDR0         10   // The first octet of the IP address of this uIP node
#define IPADDR1         0    // The second octet of the IP address of this uIP node
#define IPADDR2         38   // The third octet of the IP address of this uIP node
#define IPADDR3         15   // The fourth octet of the IP address of this uIP node
// Mask of subnet
#define NETMASK0        255  // The first octet of the netmask of this uIP node
#define NETMASK1        255  // The second octet of the netmask of this uIP node
#define NETMASK2        0    // The third octet of the netmask of this uIP node
#define NETMASK3        0    // The fourth octet of the netmask of this uIP node
// Default gate
#define DRIPADDR0       10  // The first octet of the IP address of the default router
#define DRIPADDR1       0  // The second octet of the IP address of the default router
#define DRIPADDR2       0    // The third octet of the IP address of the default router
#define DRIPADDR3       1    // The fourth octet of the IP address of the default router

// destanation MAC-addr
#define S1_ETHADDR0        0x40 // The first octet of the Ethernet address 
#define S1_ETHADDR1        0x8D // The second octet of the Ethernet address
#define S1_ETHADDR2        0x5C // The third octet of the Ethernet address 
#define S1_ETHADDR3        0xE4 // The fourth octet of the Ethernet address
#define S1_ETHADDR4        0xAC // The fifth octet of the Ethernet address 
#define S1_ETHADDR5        0xC3 // The sixth octet of the Ethernet address 
// destanation IP-addr
#define S1_IPADDR0         10   // The first octet of the IP address of this uIP node
#define S1_IPADDR1         0    // The second octet of the IP address of this uIP node
#define S1_IPADDR2         38   // The third octet of the IP address of this uIP node
#define S1_IPADDR3         13   // The fourth octet of the IP address of this uIP node



#endif

