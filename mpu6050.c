#include "mpu6050.h"
#include <math.h>

#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

void mpu6050_init(i2c_inst_t *i2c, uint8_t addr) {
    uint8_t buf[] = {MPU6050_PWR_MGMT_1, 0x00};
    i2c_write_blocking(i2c, addr, buf, 2, false);
}

static int16_t read_word(uint8_t msb, uint8_t lsb) {
    int16_t val = (msb << 8) | lsb;
    return val > 32767 ? val - 65536 : val;
}

bool mpu6050_read_accel(i2c_inst_t *i2c, uint8_t addr, accel_data_t *data) {
    uint8_t buf[6];
    uint8_t reg = MPU6050_ACCEL_XOUT_H;

    if (i2c_write_blocking(i2c, addr, &reg, 1, true) < 0) return false;
    if (i2c_read_blocking(i2c, addr, buf, 6, false) < 0) return false;

    data->ax = read_word(buf[0], buf[1]) / 16384.0f;
    data->ay = read_word(buf[2], buf[3]) / 16384.0f;
    data->az = read_word(buf[4], buf[5]) / 16384.0f;

    return true;
}

float calculate_tilt_x(float ax, float ay, float az) {
    return atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;
}

float calculate_tilt_y(float ax, float ay, float az) {
    return atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / M_PI;
}
