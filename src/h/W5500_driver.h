


#ifndef __W5500HARDWAREDRIVER_H_
#define __W5500HARDWAREDRIVER_H_

void W5500_Reset(void);
void SPI1_Init(void);
void W5500_Init(void);

void W5500WriteByte(uint8_t byte);
uint8_t W5500ReadByte();
void W5500Select(void);
void W5500DeSelect(void);


#endif
