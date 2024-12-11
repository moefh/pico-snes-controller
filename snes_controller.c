
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "snes_controller.h"
#include "snes_controller.pio.h"

#define SNES_CONTROLLER_FREQ  (1000000.f/6)  // each PIO cycle will take 6 microseconds

static PIO snes_controller_pio;
static uint snes_controller_sm;

void snes_controller_init(PIO pio, uint pin_clock, uint pin_data)
{
    snes_controller_pio = pio;
    snes_controller_sm = pio_claim_unused_sm(pio, true);

    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    float clock_div = ((float)f_clk_sys * 1000.f) / SNES_CONTROLLER_FREQ;

    uint offset = pio_add_program(pio, &snes_controller_program);
    snes_controller_program_init(pio, snes_controller_sm, offset, clock_div, pin_clock, pin_data);
}

uint16_t snes_controller_read(void)
{
    snes_controller_read_start();
    return snes_controller_read_result();
}

void snes_controller_read_start(void)
{
    // we need to send 1 less than the number of bits we want
    pio_sm_put_blocking(snes_controller_pio, snes_controller_sm, 12-1);
}

uint16_t snes_controller_read_result(void)
{
    return pio_sm_get_blocking(snes_controller_pio, snes_controller_sm);
}
