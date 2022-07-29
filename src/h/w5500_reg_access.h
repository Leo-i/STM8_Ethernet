
//w5500_reg_access.h

#ifndef _W5500_REG_ACCESS_H
#define _W5500_REG_ACCESS_H

#define REG_TYPE   1
#define TX_TYPE    2
#define RX_TYPE    3

uint8_t CR_read_byte(uint16_t offset);
void CR_write_byte(uint16_t offset, uint8_t byte);
void W5500_conf_reg();

void W5500_conf_soket_reg();
uint8_t Sn_read_byte(uint8_t socket, uint8_t type, uint16_t offset);
void Sn_write_byte(uint8_t socket, uint8_t type, uint16_t offset, uint8_t byte);



//Socket Register Block

#define         Sn_MR           0x0000  //Socket n Mode
#define         Sn_CR           0x0001  //Socket n Command 
#define         Sn_IR           0x0002  //Socket n Interrupt
#define         Sn_SR           0x0003  //Socket n Status
#define         Sn_PORT0        0x0004  //Socket n Source Port
#define         Sn_PORT1        0x0005  //Socket n Source Port


#endif 
