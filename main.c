#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#define I2C_ID i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define SSD_1306_ADDR 0x3C

ssd1306_t ssd; // Inicializa a estrutura do display

void setup() {
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_ID, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
}
  
void oled_init() {
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, SSD_1306_ADDR, I2C_ID); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

int main() {
    stdio_init_all();
    
    setup();
    oled_init();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
