#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

#define I2C_PORT i2c0
#define MPU_ADDR 0x68

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("Iniciando leitura do MPU6050 apenas com acelerômetro...\n");

    // Inicializar I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(0, GPIO_FUNC_I2C);  // SDA
    gpio_set_function(1, GPIO_FUNC_I2C);  // SCL
    gpio_pull_up(0);
    gpio_pull_up(1);

    // Inicializar sensor
    mpu6050_init(I2C_PORT, MPU_ADDR);

    accel_data_t accel;

    while (true) {
        if (mpu6050_read_accel(I2C_PORT, MPU_ADDR, &accel)) {
            float tilt_x = calculate_tilt_x(accel.ax, accel.ay, accel.az);
            float tilt_y = calculate_tilt_y(accel.ax, accel.ay, accel.az);

            printf("AX: %.2f  AY: %.2f  AZ: %.2f  | Tilt X: %.2f°  Y: %.2f°\n",
                   accel.ax, accel.ay, accel.az, tilt_x, tilt_y);
        } else {
            printf("Erro ao ler acelerômetro.\n");
        }
        sleep_ms(200);
    }
}
