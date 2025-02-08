#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "hardware/uart.h"

#define DEBOUNCE_MS 260
#define DEBOUNCE_US DEBOUNCE_MS * 1000

#define TEXT_AREA_WIDTH 120  // Adjust based on the maximum text width
#define TEXT_AREA_HEIGHT 10  // Adjust based on the text height

#define I2C_ID i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define SSD_1306_ADDR 0x3C

#define BTN_A 5
#define BTN_B 6
#define GREEN_LED 11
#define BLUE_LED 12

ssd1306_t ssd; // Inicializa a estrutura do display
static volatile absolute_time_t last_time_btn_press = {0};
static volatile char buffer = '\0';

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

void gpio_irq_handler(uint gpio, uint32_t events) {
    absolute_time_t current_time = get_absolute_time(); // captura o tempo atual

    if (current_time - last_time_btn_press > DEBOUNCE_US) { // verifica se a diff entre o tempo atual e a ultima vez que o botão foi pressionado é maior que o tempo de debounce em microssegundos (por isso 260 * 1000)
        last_time_btn_press = current_time; // atualiza o tempo da última pressão no botão

        if (gpio == BTN_A) { // verifica se o botão A foi pressionado
            gpio_put(GREEN_LED, !gpio_get(GREEN_LED)); // alterna o estado do LED verde

            if (gpio_get(GREEN_LED)) {
                printf("LED verde foi ligado.\n");
            } else {
                printf("LED verde foi desligado.\n");
            }
        } else if (gpio == BTN_B) { // verifica se o botão B foi pressionado
            gpio_put(BLUE_LED, !gpio_get(BLUE_LED)); // alterna o estado do LED azul

            if (gpio_get(BLUE_LED)) {
                printf("LED azul foi ligado.\n");
            } else {
                printf("LED azul foi desligado.\n");
            }
        }
    }
}

int main() {
    stdio_init_all(); 

    // setup do display oled
    i2c_setup();
    oled_setup();

    // inicializa o LED verde
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_put(GREEN_LED, 0);

    // inicializa o LED azul
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_put(BLUE_LED, 0);

    // inicializa os botões
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    // inicializa interrupção dos botões
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        ssd1306_draw_string(&ssd, "MONITORAMENTO", 15, 1);
        ssd1306_line(&ssd, 0, 12, 127, 12, true);
        ssd1306_draw_string(&ssd, "LEDs", 2, 14);
        ssd1306_line(&ssd, 0, 23, 127, 23, true);

        if (gpio_get(GREEN_LED)) {
            ssd1306_rect(&ssd, 26, 2, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, false, true);
            ssd1306_draw_string(&ssd, "VERDE ligado", 2, 26);
        } else {
            ssd1306_rect(&ssd, 26, 2, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, false, true);
            ssd1306_draw_string(&ssd, "VERDE desligado", 2, 26);
        }

        if (gpio_get(BLUE_LED)) {
            ssd1306_rect(&ssd, 35, 2, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, false, true); 
            ssd1306_draw_string(&ssd, "AZUL  ligado", 2, 35);
        } else {
            ssd1306_rect(&ssd, 35, 2, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, false, true); 
            ssd1306_draw_string(&ssd, "AZUL  desligado", 2, 35);
        }

        int input = getchar_timeout_us(0);

        if (input != PICO_ERROR_TIMEOUT) {
            buffer = (char)input;
            printf("Tecla pressionada: '%c'\n", buffer);
        }

        if (buffer != '\0') {
            ssd1306_rect(&ssd, 45, 2, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, false, true); 
            ssd1306_draw_char(&ssd, buffer, 2, 45);
        }

        ssd1306_send_data(&ssd);
    }

    return 0;
}
