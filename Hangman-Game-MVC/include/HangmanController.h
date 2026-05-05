#ifndef HANGMAN_CONTROLLER_H
#define HANGMAN_CONTROLLER_H

#include "GameState.h"
#include "KeyboardManager.h"
#include "UIRenderer.h"
#include "WordLoader.h"
#include "raylib.h"
#include "HangmanAnimator.h"     // ← এই লাইনটা যোগ করো
#include <vector>

class HangmanController {
private:
    GameState gameState;
    KeyboardManager keyboardManager;
    std::vector<WordEntry> wordList;
    int wordCount = 0;

    HangmanAnimator hangmanAnim;     // এটা এখন ঠিক থাকবে

    // Sound Variables
    Sound correctSound;
    Sound wrongSound;
    Sound winSound;
    Sound loseSound;
    Music backgroundMusic;

    void LoadSounds();
    void PlayGuessSound(bool isCorrect);
    void PlayGameOverSound();

public:
    HangmanController();
    ~HangmanController();

    void Initialize();
    void Restart();
    void Run();

    const GameState& GetGameState() const { return gameState; }
    const KeyboardManager& GetKeyboardManager() const { return keyboardManager; }
};

#endif
