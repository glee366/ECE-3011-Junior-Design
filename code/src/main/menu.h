#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "keypad.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "driver/ledc.h"
#include "game_def.h"

#ifndef MATH_GAME_H
#define MATH_GAME_H

// Function prototypes
game_mode_t menu_game_loop(lv_disp_t *disp);
void clear_input_buffer();


#endif // MUSIC_GAME_H