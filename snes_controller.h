#ifndef SNES_CONTROLLER_H_FILE
#define SNES_CONTROLLER_H_FILE

#include "hardware/pio.h"

void snes_controller_init(PIO pio, uint pin_clock, uint pin_data);
uint16_t snes_controller_read(void);
void snes_controller_read_start(void);
uint16_t snes_controller_read_result(void);

#endif /* SNES_CONTROLLER_H_FILE */
