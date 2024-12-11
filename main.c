#include <stdio.h>
#include "pico/stdlib.h"

#include "snes_controller.h"

#define PIN_SNES_DATA   11
#define PIN_SNES_CLOCK  12
#define PIN_SNES_LATCH  13

#define PIN_LED 25

static void led_init(void)
{
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);
    gpio_put(PIN_LED, 1);
}

static void led_update(void)
{
    static uint32_t last_change_ms = 0;
    static uint8_t led_state = 1;

    uint32_t cur_ms = to_ms_since_boot(get_absolute_time());
    if (cur_ms - last_change_ms > 500) {
        last_change_ms = cur_ms;
        led_state = ! led_state;
        gpio_put(PIN_LED, led_state);
    }
}

int main(void)
{
    stdio_init_all();
    led_init();
    snes_controller_init(pio0, PIN_SNES_CLOCK, PIN_SNES_DATA);

    sleep_ms(3000);
    printf("starting\n");

    while (1) {
        led_update();
        sleep_ms(500);
        uint32_t data = snes_controller_read();
        printf("%08x\n", data);
    }
}
