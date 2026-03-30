#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "hangman_types.h"
#include <stdbool.h>

typedef struct {
    char topic[MAX_WORD_LENGTH];
    char secretWord[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    bool revealedMask[MAX_WORD_LENGTH];
    int  uniqueLetterCount;
    int  correctGuessCount;
    int  failedAttempts;
    int  alphaPositionsTotal;
    bool isGameOver;
    bool isWin;
    bool guessedLetters[26];
    KeyboardKey keys[26];
    int  keyCount;
} Game;

#endif