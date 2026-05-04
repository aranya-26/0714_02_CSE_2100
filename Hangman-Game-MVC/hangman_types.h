#ifndef HANGMAN_TYPES_H
#define HANGMAN_TYPES_H

#include "raylib.h"
#include <string>
#include <vector>
#include <array>

constexpr int MAX_WORDS = 500;
constexpr int MAX_WORD_LENGTH = 128;
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 900;
constexpr int MAX_TRIES = 6;
constexpr int KEYBOARD_KEY_WIDTH = 110;
constexpr int KEYBOARD_KEY_HEIGHT = 48;
constexpr int KEYBOARD_GAP = 12;
constexpr int KEYBOARD_MARGIN_X = 80;
constexpr int KEYBOARD_START_Y = 680;

struct WordEntry {
    std::string topic;
    std::string word;
};

struct MyKey {
    Rectangle rectangle{};
    char letter = '\0';
    bool isPressed = false;
    bool isVisible = true;
};

#endif
