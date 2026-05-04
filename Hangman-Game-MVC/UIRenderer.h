#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include "hangman_types.h"
#include "GameState.h"
#include "KeyboardManager.h"

class UIRenderer {
public:
    static void DrawHangmanFigure(int failedAttempts);
    static void DrawGuessedWord(const std::string& guessedWord, int startX, int py);
    static void DrawGameUI(const GameState& state, const KeyboardManager& keyboard);
    static void DrawGameOverScreen(const GameState& state);
};

#endif
