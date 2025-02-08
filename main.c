#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "hardware/uart.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#define I2C_ID i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define SSD_1306_ADDR 0x3C
#define BTN_A 5
#define BTN_B 6
#define GREEN_LED 12
#define BLUE_LED 11

ssd1306_t ssd; // Inicializa a estrutura do display
static volatile absolute_time_t last_time_btn_press = {0};

void i2c_setup() {
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_ID, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
}

void oled_setup() {
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, SSD_1306_ADDR, I2C_ID); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

int main() {
    stdio_init_all();

    // inicializa o LED verde
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_put(GREEN_LED, 0);

    // inicializa o LED azul
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_put(BLUE_LED, 0);

    // inicializa o botão A
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    // inicializa o botão B
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    // setup do display oled
    i2c_setup();
    oled_setup();

    

    while (true) {
        sleep_ms(1000);
    }
}
