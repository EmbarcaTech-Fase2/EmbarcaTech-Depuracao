#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 28  // GPIO onde o servo está conectado

// Usar a UART do DEBUG (uart0 nos GPIOs 16 e 17)
#include "hardware/uart.h"
#define UART_TX_PIN 16
#define UART_RX_PIN 17
#define BAUD_RATE 115200

// Função para configurar o PWM
void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);

    // Configura PWM para 50Hz (período de 20 milissegundos)
    pwm_set_clkdiv(slice, 125.0f);  // Divide clock para facilitar cálculo
    pwm_set_wrap(slice, 20000);     // 20ms período total (20000 "counts")
    pwm_set_enabled(slice, true);
}

// Define o pulso em microsegundos (us)
void set_servo_pulse(uint pin, uint pulse_width_us) {
    pwm_set_gpio_level(pin, pulse_width_us);
}

int main() {
    stdio_uart_init_full(uart0, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
    setup_pwm(SERVO_PIN);

    while (1) {
        // Posição 0° (~500 a 600us dependendo do servo)
        printf("Garra fechando (0 graus)...\n");
        set_servo_pulse(SERVO_PIN, 500);  // 0 graus
        sleep_ms(1000);  // Espera 1 segundo

        // Posição 180° (~2400us máximo)
        printf("Garra abrindo (180 graus)...\n");
        set_servo_pulse(SERVO_PIN, 2400);  // 180 graus
        sleep_ms(1000);  // Espera 1 segundo
    }
}
