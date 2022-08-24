#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#define SOCKET_0        0
#define SOCKET_1        1

#define DESTINATION_PORT 2000

#define SENSOR_COUNT    1

#define USART_BAUDRATE 115200

#define HTTP_SOCKET     0
#define PORT_TCPS	5000
#define DATA_BUF_SIZE   2048

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
#define IPADDR0         169   // The first octet of the IP address of this uIP node
#define IPADDR1         254    // The second octet of the IP address of this uIP node
#define IPADDR2         62   // The third octet of the IP address of this uIP node
#define IPADDR3         235   // The fourth octet of the IP address of this uIP node
// Mask of subnet
#define NETMASK0        255  // The first octet of the netmask of this uIP node
#define NETMASK1        255  // The second octet of the netmask of this uIP node
#define NETMASK2        0    // The third octet of the netmask of this uIP node
#define NETMASK3        0    // The fourth octet of the netmask of this uIP node
// Default gate
#define DRIPADDR0       169  // The first octet of the IP address of the default router
#define DRIPADDR1       254  // The second octet of the IP address of the default router
#define DRIPADDR2       62    // The third octet of the IP address of the default router
#define DRIPADDR3       235    // The fourth octet of the IP address of the default router

// destanation MAC-addr
#define S1_ETHADDR0        0xF8 // The first octet of the Ethernet address 
#define S1_ETHADDR1        0x75 // The second octet of the Ethernet address
#define S1_ETHADDR2        0xA4 // The third octet of the Ethernet address 
#define S1_ETHADDR3        0xFC // The fourth octet of the Ethernet address
#define S1_ETHADDR4        0xB2 // The fifth octet of the Ethernet address 
#define S1_ETHADDR5        0x8A // The sixth octet of the Ethernet address 
// destanation IP-addr
#define S1_IPADDR0         169   // The first octet of the IP address of this uIP node
#define S1_IPADDR1         254    // The second octet of the IP address of this uIP node
#define S1_IPADDR2         62   // The third octet of the IP address of this uIP node
#define S1_IPADDR3         234   // The fourth octet of the IP address of this uIP node



#endif