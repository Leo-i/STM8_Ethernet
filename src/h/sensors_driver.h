
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H
// assign finctions to they sensors in srtuct
void set_sensor_funct();

//1
void init_gpio_sensor();
void gpio_sensor_get_data (uint8_t* buf);

#endif