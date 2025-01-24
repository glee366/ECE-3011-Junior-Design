#include "keypad.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// static bool initialized = false;
static bool initialized = false;

static const int rowPins[(int)ROWS] = {9, 18, 19, 20};
static const int colPins[(int)COLS] = {21, 22, 23, 15};

// static const int rowPins[ROWS] = {20, 20, 20, 20};
// static const int colPins[COLS] = {21, 21, 21, 21};

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void keypad_init()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_config(&((gpio_config_t){
            .pin_bit_mask = 1ULL << rowPins[i],
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = 1,
            .pull_down_en = 0,
            .intr_type = GPIO_INTR_DISABLE}));
    }

    for (int i = 0; i < COLS; i++)
    {
        gpio_config(&((gpio_config_t){
            .pin_bit_mask = 1ULL << colPins[i],
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = 1,
            .pull_down_en = 0,
            .intr_type = GPIO_INTR_DISABLE}));
    }
}

char get_key()
{
    if (!initialized)
    {
        keypad_init();
        initialized = true;
    }

    char pressedKey = '\0';

    int rowIndex = -1;
    int colIndex = -1;

    for (int i = 0; i < ROWS; i++)
    {
        gpio_set_level(rowPins[i], 0);

        for (int j = 0; j < COLS; j++)
        {
            if (gpio_get_level(colPins[j]) == 0)
            {
                rowIndex = i;
                colIndex = j;
                break;
            }
        }

        gpio_set_level(rowPins[i], 1);

        if (rowIndex != -1)
        {
            break;
        }
    }

    // printf("Row: %d, Col: %d\n", rowIndex, colIndex);

    if (rowIndex != -1 && colIndex != -1)
    {
        pressedKey = keys[rowIndex][colIndex];
    }

    return pressedKey;
}