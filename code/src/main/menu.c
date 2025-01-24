#include "menu.h"

void clear_input_buffer() {
    // Wait until all keys are released
    while (get_key() != '\0') {
        vTaskDelay(1);  // Small delay to allow the buffer to clear
    }
}


game_mode_t menu_game_loop(lv_disp_t *disp)
{
    if (lvgl_port_lock(0))
    {
        lv_obj_t *scr = lv_disp_get_scr_act(disp);
        lv_obj_clean(scr);

        lv_obj_t *text = lv_textarea_create(scr);
        lv_textarea_set_text(text, "1. Math Game\n2. Music Game");

        // Release the mutex
        lvgl_port_unlock();
    }

    char key = '\0';
    game_mode_t game_mode = GAME_MODE_MENU;

    // Wait for a key press to select a game
    while (key == '\0')
    {
        key = get_key();
        vTaskDelay(1);
    }

    switch (key)
    {
    case '1':
        game_mode = GAME_MODE_MATH;
        break;
    case '2':
        game_mode = GAME_MODE_MUSIC;
        break;
    case 'A':
        gpio_set_level(11, 1);
        gpio_set_level(10, 1);
        vTaskDelay(1000);
        gpio_set_level(11, 0);
        gpio_set_level(10, 0);
        break;
    default:
        break;
    }

    clear_input_buffer();
    vTaskDelay(1);
    

    return game_mode;
}