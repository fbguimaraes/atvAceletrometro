#ifndef MPU6050_H
#define MPU6050_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef struct {
    float ax, ay, az;
} accel_data_t;

void mpu6050_init(i2c_inst_t *i2c, uint8_t addr);
bool mpu6050_read_accel(i2c_inst_t *i2c, uint8_t addr, accel_data_t *data);
float calculate_tilt_x(float ax, float ay, float az);
float calculate_tilt_y(float ax, float ay, float az);

#endif
