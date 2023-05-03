#include "pio_counter_program.pio.h"

static uint pio_counter_program_count = 0;

void pio_counter_set_count(uint c) {
	pio_counter_program_count = c;
}

int32_t pio_counter_get_count(PIO pio, uint sm) {
	return pio_counter_program_count;
}