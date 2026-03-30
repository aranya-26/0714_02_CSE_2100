#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "hangman_types.h"
#include <string>
#include <array>

class GameState {
private:
    std::string secretWord;
    std::string guessedWord;
    std::string topic;
    std::array<bool, MAX_WORD_LENGTH> revealedMask{};
    std::array<bool, 26> guessedLetters{};
    int failedAttempts = 0;
    int correctGuessCount = 0;
    int alphaPositionsTotal = 0;
    bool isGameOver = false;
    bool isWin = false;

public:
    void Initialize(const WordEntry& selectedWord);
    void ProcessGuess(char letter);
    void CheckGameOver();

    const std::string& GetSecretWord() const { return secretWord; }
    const std::string& GetGuessedWord() const { return guessedWord; }
    const std::string& GetTopic() const { return topic; }
    int GetFailedAttempts() const { return failedAttempts; }
    bool IsGameOver() const { return isGameOver; }
    bool IsWin() const { return isWin; }
    const std::array<bool, MAX_WORD_LENGTH>& GetRevealedMask() const { return revealedMask; }
};

#endif
