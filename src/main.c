#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "systick.h"
#include "i2c_custom.h"
#include "uart.h"

#define UART_PORT   (GPIOA)
#define TX_PIN      (GPIO2)
#define RX_PIN      (GPIO3)

static void setup_gpio(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TX_PIN | RX_PIN);
    gpio_set_af(UART_PORT, GPIO_AF7, TX_PIN | RX_PIN);
}

int main(void) {
    setup_gpio();
    uart_setup();
    systickSetup(8);
    i2c_init();

    LED led;
    led.state = 1;
    led.pins[0] = 4;
    led.pins[1] = 7;
    led.pins[2] = 9;
    
    systickDelaySec(2);
    while(1) {
        i2c_write_string((uint8_t *)"Hello Arduino");
        systickDelaySec(2);
        i2c_write_byte('M');
        systickDelaySec(2);
        i2c_read_string();
        systickDelaySec(2);
        i2c_write_leds(&led);
    }
    return 0;
}