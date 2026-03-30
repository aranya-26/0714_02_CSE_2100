#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include "GameState.h"
#include "KeyboardManager.h"
#include "WordLoader.h"
#include "UIRenderer.h"

class HangmanGame {
private:
    std::vector<WordEntry> wordList;
    GameState gameState;
    KeyboardManager keyboardManager;
    int wordCount = 0;

public:
    HangmanGame();
    void Run();
    void Restart();
};

#endif
