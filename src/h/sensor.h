
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
    void    (*_s_init)        (void);
    // return data length and data as buffer
    uint8_t (*_s_get_data)    (uint8_t* buf);
    s_state (*_check_ready)   (void);
    void    (*_reset_sensor)  (void);
    void    (*_start_sensor)  (void);
    void    (*_stop_sensor)   (void);
  }driver;

} Sensor;

void init_sensors();
void set_drivers( uint8_t s_num, 
                void    (*_s_init)      (void),
                uint8_t (*_s_get_data)  (uint8_t* buf) ,
                s_state (*_check_ready) (void),
                void    (*_reset_sensor)(void),
                void    (*_start_sensor)(void),
                void    (*_stop_sensor) (void)
                );
uint8_t s_get_data( uint8_t s_num, uint8_t *buf);

// return the first ready sensor
uint8_t check_sensors();
void reset_sensor(uint8_t s_num);
void start_sensor(uint8_t s_num);
void stop_sensor(uint8_t s_num);

#endif