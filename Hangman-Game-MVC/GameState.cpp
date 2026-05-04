#include "GameState.h"
#include <cctype>
#include <cstdlib>   // for rand()

void GameState::Initialize(const WordEntry& selectedWord) {
    topic = selectedWord.topic;
    secretWord = selectedWord.word;

    for (char& c : secretWord) c = std::tolower(static_cast<unsigned char>(c));

    int len = static_cast<int>(secretWord.length());
    guessedWord = std::string(len, '_');
    revealedMask.fill(false);
    guessedLetters.fill(false);

    alphaPositionsTotal = 0;
    for (int i = 0; i < len; ++i) {
        if (std::isalpha(static_cast<unsigned char>(secretWord[i]))) {
            alphaPositionsTotal++;
        } else {
            guessedWord[i] = secretWord[i];
            revealedMask[i] = true;
        }
    }

    int revealCount = (len <= 6) ? 2 : 3;
    if (len < 5) revealCount = 1;

    failedAttempts = 0;
    correctGuessCount = 0;
    isGameOver = false;
    isWin = false;

    // Random reveal some letters
    for (int i = 0; i < revealCount; ++i) {
        int pos = rand() % len;
        if (!revealedMask[pos] && std::isalpha(static_cast<unsigned char>(secretWord[pos]))) {
            guessedWord[pos] = secretWord[pos];
            revealedMask[pos] = true;
            correctGuessCount++;
        }
    }
}

void GameState::ProcessGuess(char letter) {
    letter = std::tolower(static_cast<unsigned char>(letter));
    int li = letter - 'a';
    if (li < 0 || li >= 26 || guessedLetters[li]) return;

    guessedLetters[li] = true;

    bool found = false;
    int len = static_cast<int>(secretWord.length());

    for (int i = 0; i < len; ++i) {
        if (secretWord[i] == letter && !revealedMask[i]) {
            guessedWord[i] = letter;
            revealedMask[i] = true;
            correctGuessCount++;
            found = true;
        }
    }

    if (!found) failedAttempts++;
}

void GameState::CheckGameOver() {
    int revealedAlpha = 0;
    int len = static_cast<int>(secretWord.length());

    for (int i = 0; i < len; ++i) {
        if (revealedMask[i] && std::isalpha(static_cast<unsigned char>(secretWord[i])))
            revealedAlpha++;
    }

    if (revealedAlpha == alphaPositionsTotal) {
        isGameOver = true;
        isWin = true;
    } else if (failedAttempts >= MAX_TRIES) {
        isGameOver = true;
        isWin = false;
    }
}
