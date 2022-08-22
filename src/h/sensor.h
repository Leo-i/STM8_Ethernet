
#ifndef _SENSOR_H
#define _SENSOR_H

typedef enum 
{ 
  IDLE, 
  WORKING, 
  READY
} s_state;

typedef struct{
  uint8_t num;
  struct{
    void   (*_s_init)     (void);
    void   (*_s_get_data) (uint8_t* buf);
  }func;

} Sensor;

void init_sensors();
void set_funct( uint8_t s_num, 
                void (*_s_init)(void),
                void (*_s_get_data) (uint8_t* buf) 
                );
void s_get_data( uint8_t s_num, uint8_t *buf);

// return the first ready sensor
// void check_sensors(){

// }

#endif