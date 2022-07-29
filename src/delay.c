
#include "delay.h"


void delay_us(unsigned int us)
{
  unsigned int tick = 0;
  
  while (us--)
  {
    while (tick < 6)
    {
      tick++;
    }
    tick = 0;
  }
}

void delay_ms(unsigned int ms)
{
  while (ms--)
  {
    delay_us(1000);
  }
}

