#include "music_game.h"

// FIXME: Add in delays
// TODO: Add in the game logic itself. For tapping out the notes using the microphone.
// TODO: Add in the game logic for the user to select the notes using the keypad.

// Array of frequencies for do, re, mi, fa, so, la, ti, do
static const float noteFrequencies[NUM_NOTES] = {
    523.25, // do (C4)
    587.33, // re (D4)
    659.25, // mi (E4)
    698.46, // fa (F4)
    783.99, // so (G4)
    880.00, // la (A4)
    987.77, // ti (B4)
    1046.50 // do (C5)
};

// Array to store the indices of the selected notes
static int selectedNoteIndices[4];

// Initialize the Note Player
static void initNotePlayer()
{
    // Setup PWM functionality for ESP32
    ledc_set_pin(PWM_PIN, LEDC_SPEED_MODE_MAX, PWM_CHANNEL); // Set PWM pin

    ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 0);         // Start PWM with 0% duty cycle
    ledc_set_freq(LEDC_SPEED_MODE_MAX, LEDC_TIMER_0, PWM_FREQ); // Set PWM frequency

    uint32_t dutyCycle = 128;                                   // 50% duty cycle (128/255 for 8-bit resolution)
    ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, dutyCycle); // Start PWM with 50% duty cycle
}

// Function to play random notes and store their indices
static void playRandomNotes()
{
    for (int i = 0; i < 4; i++)
    {
        int randomIndex = rand() % NUM_NOTES;
        selectedNoteIndices[i] = randomIndex;
        float frequency = noteFrequencies[randomIndex];

        // Output the frequency as PWM signal
        ledc_set_freq(LEDC_SPEED_MODE_MAX, LEDC_TIMER_0, frequency);
        ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 128); // 50% duty cycle
        ledc_update_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL);

        // Play the note for a duration
        // delay(500); // Play the note for 500 ms

        // Stop the tone
        ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 0); // Stop PWM by setting duty cycle to 0%
        ledc_update_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL);
        // delay(200); // Pause between notes
    }
}

// Function to check player input against the selected notes
static bool checkPlayerInput(int playerInputIndices[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (playerInputIndices[i] != selectedNoteIndices[i])
        {
            return false; // Incorrect input
        }
    }
    return true; // Correct input
}

// Function to play a note by index
static void playNoteByIndex(int index)
{
    if (index >= 0 && index < NUM_NOTES)
    {
        float frequency = noteFrequencies[index];

        // Output the frequency as PWM signal
        ledc_set_freq(LEDC_SPEED_MODE_MAX, LEDC_TIMER_0, frequency);
        ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 128); // 50% duty cycle
        ledc_update_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL);

        // Play the note for a duration
        // delay(500); // Play the note for 500 ms

        // Stop the tone
        ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 0); // Stop PWM by setting duty cycle to 0%
        ledc_update_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL);
    }
    else
    {
        // Invalid index, do nothing or handle error
    }
}

static void haveFun(int playerMusic[10])
{
    for (int i = 0; i < 10; i++)
    {
        float frequency = playerMusic[i];
        ledc_set_freq(LEDC_SPEED_MODE_MAX, LEDC_TIMER_0, frequency);
        ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL, 128); // 50% duty cycle
        ledc_update_duty(LEDC_SPEED_MODE_MAX, PWM_CHANNEL);
        // delay(500);
    }
}

void music_game_instructions(lv_disp_t *disp)
{
    if (lvgl_port_lock(0))
    {
        // TODO: Write instructions for the math game
        lv_obj_t *scr = lv_disp_get_scr_act(disp);
        lv_obj_t *text = lv_textarea_create(scr);
        lv_textarea_set_text(text, "Welcome to the math game! Press the '#' key to submit your answer and the '*' key to delete a digit. Press any key to continue.");
        lv_obj_align(text, LV_ALIGN_TOP_MID, 0, 0);
        lvgl_port_unlock();
    }
}

// Function to start the game
game_mode_t music_game_loop(lv_disp_t *disp)
{
    // Start the game logic
    printf("Game started.\n");
    // Example game loop
    while (1)
    {
        char key = get_key();
        if (key != '\0')
        {
            printf("Key pressed: %c\n", key);
            // Add game logic based on key press
        }

        vTaskDelay(1);
    }

    return GAME_MODE_MENU;
}