/**
 * @file hangman_ui.c
 * @brief UI rendering and input handling with Raylib
 */

#include "hangman_types.h"

/**
 * @brief Draws hangman figure
 */
void DrawHangmanFigure(int failedAttempts) {
    DrawRectangleLines(120, 120, 260, 380, Fade(BLACK, 0.6f));
    DrawLine(200, 500, 420, 500, DARKGRAY);
    DrawLine(250, 500, 250, 160, DARKGRAY);
    DrawLine(250, 160, 370, 160, DARKGRAY);
    DrawLine(370, 160, 370, 210, DARKGRAY);

    if (failedAttempts >= 1) {
        DrawCircle(370, 235, 30, BLACK);
        DrawCircleLines(370, 235, 30, GRAY);
    }
    if (failedAttempts >= 2) DrawLine(370, 265, 370, 360, BLACK);
    if (failedAttempts >= 3) DrawLine(370, 290, 330, 330, BLACK);
    if (failedAttempts >= 4) DrawLine(370, 290, 410, 330, BLACK);
    if (failedAttempts >= 5) DrawLine(370, 360, 330, 410, BLACK);
    if (failedAttempts >= 6) DrawLine(370, 360, 410, 410, BLACK);

    if (failedAttempts > 0) DrawRectangle(120, 120, 260, 380, Fade(RAYWHITE, 0.02f));
}

/**
 * @brief Initializes on-screen keyboard
 */
int InitializeKeyboard(KeyboardKey *keys) {
    const char *rows[] = {"ABCDEFGHI", "JKLMNOPQR", "STUVWXYZ"};
    int index = 0;
    int x, y = KEYBOARD_START_Y;

    for (int r = 0; r < 3; r++) {
        x = KEYBOARD_MARGIN_X;
        if (r == 2) x += 24;
        for (int i = 0; rows[r][i]; i++) {
            keys[index].rectangle = (Rectangle){(float)x, (float)y, (float)KEYBOARD_KEY_WIDTH, (float)KEYBOARD_KEY_HEIGHT};
            keys[index].letter = rows[r][i];
            keys[index].isPressed = false;
            keys[index].isVisible = true;
            x += KEYBOARD_KEY_WIDTH + KEYBOARD_GAP;
            index++;
        }
        y += KEYBOARD_KEY_HEIGHT + KEYBOARD_GAP;
    }
    return index;
}

/**
 * @brief Handles keyboard drawing and mouse input
 * @return pressed letter or 0
 */
char HandleKeyboardInput(KeyboardKey *keys, int keyCount, Vector2 mousePos, bool clicked) {
    char pressed = 0;
    for (int i = 0; i < keyCount; i++) {
        if (!keys[i].isVisible) continue;
        Color bg = keys[i].isPressed ? Fade(DARKGREEN, 0.9f) : LIGHTGRAY;
        if (CheckCollisionPointRec(mousePos, keys[i].rectangle)) {
            bg = Fade(SKYBLUE, keys[i].isPressed ? 0.9f : 0.6f);
            if (clicked && !keys[i].isPressed) {
                keys[i].isPressed = true;
                pressed = tolower(keys[i].letter);
            }
        }
        DrawRectangleRec(keys[i].rectangle, bg);
        DrawRectangleLinesEx(keys[i].rectangle, 2, Fade(GRAY, 0.7f));
        DrawText(TextFormat("%c", keys[i].letter), (int)(keys[i].rectangle.x + 15), (int)(keys[i].rectangle.y + 8), 22, BLACK);
    }
    return pressed;
}

/**
 * @brief Draws the guessed word grid
 */
void DrawGuessedWord(const char *guessedWord, int startX, int py) {
    int spacing = 40;
    int len = strlen(guessedWord);
    for (int i = 0; i < len; i++) {
        Rectangle cell = {(float)(startX + i * spacing), (float)py, 36, 48};
        DrawRectangleLinesEx(cell, 2, Fade(GRAY, 0.6f));
        if (guessedWord[i] != '_') {
            char s[2] = {guessedWord[i], '\0'};
            DrawText(s, (int)(cell.x + 6), (int)(cell.y + 6), 30, MAROON);
        }
    }
}
