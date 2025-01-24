#include <stdio.h>
#include <driver/gpio.h>

// #include "lvgl.h"
// #include "esp_lvgl_port.h"

#ifndef KEYPAD_H
#define KEYPAD_H

#define ROWS 4
#define COLS 4

#ifdef __cplusplus
extern "C"
{
#endif

    // Function prototypes
    char get_key();

#ifdef __cplusplus
}
#endif

#endif // KEYPAD_H