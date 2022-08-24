
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H
// assign finctions to they sensors in srtuct
void set_sensor_funct();

//1
void init_gpio_sensor();
uint8_t gpio_sensor_get_data (uint8_t* buf);
s_state gpio_check_ready();
void gpio_reset();
void gpio_sensor_start();
void gpio_sensor_stop();


#endif