#ifndef _PIO_COUNTER_PROGRAM_H_
#define _PIO_COUNTER_PROGRAM_H_

#include <stdint.h>

/* Mock PIO counter program for tests */

/* types */
typedef unsigned int uint;
typedef unsigned int PIO;

struct pio_program {
    int dummy;
};

struct pio_sm_config {
    int dummy;
};

/* data */
static const struct pio_program pio_counter_program = { 0 };

/* functions */
static inline pio_sm_config pio_counter_program_get_default_config(uint offset) {
    return pio_sm_config { 0 };
}

static inline void pio_counter_init(PIO pio, uint sm, uint offset, uint pin, float div) {
    // dummy
}

static inline void pio_counter_request_count(PIO pio, uint sm) {
    // dummy
}

static inline uint pio_add_program(PIO pio, const pio_program* program) {
    // dummy value
    return 0;
}

// sets number of aperatures passed
void pio_counter_set_count(uint c);

// gets number of aperatures passed
int32_t pio_counter_get_count(PIO pio, uint sm);

#endif