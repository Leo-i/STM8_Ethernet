
#include "stm8l15x.h"

#include <sensor.h>
#include <sensors_driver.h>
#include <parameters.h>

Sensor sensors [SENSOR_COUNT];

void init_sensors(){
  
  set_sensor_funct();

  for(uint8_t i = 0; i < SENSOR_COUNT; i++){
    sensors[i].num = i;
    sensors[i].func._s_init();
  }

}

void set_funct( uint8_t s_num, 
                void (*_s_init)(void),
                void (*_s_get_data) (uint8_t* buf) 
                ){    
  sensors[s_num].func._s_init = _s_init;
  sensors[s_num].func._s_get_data = _s_get_data;               
}

void s_get_data( uint8_t s_num, uint8_t *buf){
  sensors[s_num].func._s_get_data(buf);
}

// return the first ready sensor
// void check_sensors(){

// }
