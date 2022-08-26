
#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#include <sensor.h>
#include <sensors_driver.h>

void set_sensor_funct(){

  set_drivers(0,
            init_gpio_sensor,
            gpio_sensor_get_data,
            gpio_check_ready,
            gpio_reset,
            gpio_sensor_start,
            gpio_sensor_stop
            );

}

// first sensor functions
void init_gpio_sensor(){
  GPIO_Init( GPIOG, GPIO_Pin_2, GPIO_Mode_In_FL_No_IT);
}

uint8_t gpio_sensor_get_data (uint8_t *buf){
  //*buf = (GPIO_ReadInputData(GPIOG) & 0x04) != 0 ? 0x27 : 0x24;
  char* message = "Hi, gpio sensor's ready";
  uint8_t length = 23;
  
  for(uint8_t i = 0; i < length; i++)
    buf[i] = (uint8_t)message[i];
    
  return length;
}

s_state gpio_check_ready(){
  return(GPIO_ReadInputData(GPIOG) & 0x04) != 0 ? READY : WORKING;
}

void gpio_reset(){
  
}

void gpio_sensor_start(){
  
}


void gpio_sensor_stop(){
  
}


// second sensor functions