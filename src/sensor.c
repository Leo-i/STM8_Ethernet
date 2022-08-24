
#include "stm8l15x.h"

#include <sensor.h>
#include <sensors_driver.h>
#include <parameters.h>

Sensor sensors [SENSOR_COUNT];

void init_sensors(){
  
  set_sensor_funct();

  for(uint8_t i = 0; i < SENSOR_COUNT; i++){
    sensors[i].num = i;
    sensors[i].driver._s_init();
  }

}

void set_drivers( uint8_t s_num, 
                void    (*_s_init)      (void),
                uint8_t (*_s_get_data)  (uint8_t* buf),
                s_state (*_check_ready) (void),
                void    (*_reset_sensor)(void),
                void    (*_start_sensor)(void),
                void    (*_stop_sensor) (void)
                ){    
  sensors[s_num].driver._s_init = _s_init;
  sensors[s_num].driver._s_get_data = _s_get_data;
  sensors[s_num].driver._check_ready = _check_ready;
  sensors[s_num].driver._reset_sensor = _reset_sensor;
  sensors[s_num].driver._start_sensor = _start_sensor;
  sensors[s_num].driver._stop_sensor = _stop_sensor;
}

// return the first ready sensor
uint8_t check_sensors(){
    for(uint8_t i = 0; i < SENSOR_COUNT; i++){
      if (sensors[i].driver._check_ready() == READY)
        return i;
  }
  return 255;
  
}

uint8_t s_get_data(uint8_t s_num, uint8_t *buf){
  return sensors[s_num].driver._s_get_data(buf);
}

void reset_sensor(uint8_t s_num){
  sensors[s_num].driver._reset_sensor();
}

void start_sensor(uint8_t s_num){
  sensors[s_num].driver._start_sensor();
}

void stop_sensor(uint8_t s_num){
  sensors[s_num].driver._stop_sensor();
}