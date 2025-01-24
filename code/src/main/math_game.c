#include "math_game.h"

static lv_obj_t *answer_label; // Define a static label object for the answer

// Function to display question and answer on the same screen
static void display_question_with_answer(lv_disp_t *disp, const char *question, const char *initial_answer) {
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    lv_obj_clean(scr); // Clear previous elements

    // Display the question
    lv_obj_t *question_label = lv_label_create(scr);
    lv_label_set_text(question_label, question);
    lv_obj_align(question_label, LV_ALIGN_TOP_MID, 0, 10);

    // Display the answer placeholder
    answer_label = lv_label_create(scr);
    lv_label_set_text_fmt(answer_label, "Answer: %s", initial_answer);
    lv_obj_align(answer_label, LV_ALIGN_TOP_MID, 0, 50);
}

// Update only the answer label with the current answer string
static void update_answer_label(const char *answer) {
    lv_label_set_text_fmt(answer_label, "Answer: %s", answer);
}

// Convert answer with placeholders to an integer
static int sanitize_answer_to_int(char *answer) {
    int result = 0;
    for (int i = 0; i < 4 && answer[i] != '\0'; i++) {
        if (answer[i] >= '0' && answer[i] <= '9') {
            result = result * 10 + (answer[i] - '0');
        }
    }
    return result;
}

static char *get_answer(lv_disp_t *disp) {
    char *answer = (char *)malloc(5 * sizeof(char));
    if (answer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(answer, "####"); // Initialize with placeholders

    int i = 0;
    char key;
    while (1) { // Keep looping until `#` is pressed
        key = get_key();
        if (key == 'B') {
            return NULL;
        }
        if (key == '#') {  // Submit the answer
            answer[i] = '\0'; // Null-terminate the answer
            break;
        } else if (key == '*') {  // Backspace functionality
            if (i > 0) {
                i--;
                answer[i] = '#'; // Replace the last entered digit with placeholder
            }
        } else if (key >= '0' && key <= '9' && i < 4) {  // Valid number key pressed and space available
            answer[i] = key; // Replace placeholder with the digit
            i++;
            while (get_key() != '\0');  // Wait until key is released to prevent repeats
        }

        if (lvgl_port_lock(0)) {
            update_answer_label(answer); // Update display with current answer
            lvgl_port_unlock();
        }

        vTaskDelay(1);  // Small delay for smooth display refresh
    }

    return answer;
}


void math_game_instructions(lv_disp_t *disp) {
    printf("Math game instructions\n");

    if (lvgl_port_lock(0)) {
        lv_obj_t *scr = lv_disp_get_scr_act(disp);
        lv_obj_clean(scr);

        // Define the instructions label with explicit width and wrapping
        lv_obj_t *text = lv_label_create(scr);
        lv_obj_set_width(text, lv_pct(90)); // Set width to 90% of the screen
        lv_label_set_long_mode(text, LV_LABEL_LONG_WRAP); // Enable text wrapping
        lv_label_set_text(text, "'#' to submit your answer\n'*' to delete a digit.");

        // Center the label
        lv_obj_align(text, LV_ALIGN_CENTER, 0, 0); // Adjust vertical offset as needed

        lvgl_port_unlock();
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay to allow reading instructions
}

void display_result(lv_disp_t *disp, const char *result) {
    printf("Displaying result\n");

    if (lvgl_port_lock(0)) {
        lv_obj_t *scr = lv_disp_get_scr_act(disp);
        lv_obj_clean(scr);

        // Define the result label with fixed width and center alignment
        lv_obj_t *label = lv_label_create(scr);
        lv_obj_set_width(label, lv_pct(90)); // Set width to 90% to ensure text fits within the screen
        lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP); // Enable text wrapping
        lv_label_set_text(label, result);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // Center align the result text

        lvgl_port_unlock();
    }

    if (strcmp(result, "Correct!") == 0) {
        gpio_set_level(11, 1);
        gpio_set_level(10, 1);
    } 

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Display result for 2 seconds
    gpio_set_level(11, 0);
    gpio_set_level(10, 0);
}

// Main loop for math game with question generation and answer checking
game_mode_t math_game_loop(lv_disp_t *disp) {
    printf("Math game loop\n");

    srand((unsigned int)time(0));

    int multiple1 = rand() % (99 - 10 + 1) + 10; // Generate two-digit number
    int multiple2 = rand() % (99 - 10 + 1) + 10; // Generate another two-digit number
    char question[100];
    sprintf(question, "What is %d * %d?", multiple1, multiple2);

    int correct_answer = multiple1 * multiple2;
    
    display_question_with_answer(disp, question, "####"); // Show question with placeholders

    char *player_answer_str = get_answer(disp);  // Get player input as a string
    
    if (player_answer_str == NULL) {
        return GAME_MODE_MENU;  // Return to main menu if B button was pressed
    }
    int player_answer = sanitize_answer_to_int(player_answer_str); // Convert answer to integer
    free(player_answer_str); // Free allocated memory for the answer

    // Compare and display the result
    if (player_answer == correct_answer) {
        display_result(disp, "Correct!");
    } else {
        char result[100];
        sprintf(result, "Incorrect. Correct answer: %d", correct_answer);
        display_result(disp, result);
    }

    return GAME_MODE_MATH;
}
