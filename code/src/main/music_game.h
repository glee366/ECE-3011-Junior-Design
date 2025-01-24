#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "keypad.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "driver/ledc.h"
#include "game_def.h"

#ifndef MUSIC_GAME_H
#define MUSIC_GAME_H

// PWM Configuration
#define PWM_PIN 21       // PWM output on GPIO 21
#define PWM_CHANNEL 0    // PWM channel (0-15)
#define PWM_RESOLUTION 8 // PWM resolution (8 bits = 256 levels)
#define PWM_FREQ 1000    // Initial PWM frequency in Hz

// Number of notes
#define NUM_NOTES 8

// Function declarations
game_mode_t music_game_loop(lv_disp_t *disp);
void music_game_instructions(lv_disp_t *disp);

#endif // MUSIC_GAME_H