/**
 * @file hangman_types.h
 * @brief Type definitions and constants for Hangman game
 *
 * Follows modular coding standards from program_style.pdf
 *
 * @author Aranya
 * @date February 2026
 */

#ifndef HANGMAN_TYPES_H
#define HANGMAN_TYPES_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_WORDS           500
#define MAX_WORD_LENGTH     128
#define WINDOW_WIDTH        1000
#define WINDOW_HEIGHT       700
#define MAX_TRIES           6
#define KEYBOARD_KEY_WIDTH  48
#define KEYBOARD_KEY_HEIGHT 48
#define KEYBOARD_GAP        12
#define KEYBOARD_MARGIN_X   40
#define KEYBOARD_START_Y    420

typedef struct {
    char topic[MAX_WORD_LENGTH];
    char word[MAX_WORD_LENGTH];
} WordEntry;

typedef struct {
    Rectangle rectangle;
    char letter;
    bool isPressed;
    bool isVisible;
} KeyboardKey;

#endif // HANGMAN_TYPES_H
