
#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#include <sensor.h>
#include <sensors_driver.h>

void set_sensor_funct(){

  set_funct(0,init_gpio_sensor,gpio_sensor_get_data);

}

// first sensor functions
void init_gpio_sensor(){
  GPIO_Init( GPIOB, GPIO_Pin_2, GPIO_Mode_In_FL_No_IT);
}

void  gpio_sensor_get_data (uint8_t* buf){
  *buf = (GPIO_ReadInputData(GPIOB) & 0x04) != 0 ? 0x27 : 0x24;
}


// second sensor functions