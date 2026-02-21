/**
 * @file hangman_game_logic.c
 * @brief Core game logic: initialization, guessing, state checks
 */

#include "hangman_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Loads word entries from file in "topic:word" format
 */
int LoadWordList(const char *filename, WordEntry *wordList, int maxWords) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char buffer[300];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) && count < maxWords) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strlen(buffer) == 0) continue;
        char *sep = strchr(buffer, ':');
        if (sep) {
            *sep = '\0';
            strncpy(wordList[count].topic, buffer, MAX_WORD_LENGTH - 1);
            wordList[count].topic[MAX_WORD_LENGTH - 1] = '\0';
            strncpy(wordList[count].word, sep + 1, MAX_WORD_LENGTH - 1);
            wordList[count].word[MAX_WORD_LENGTH - 1] = '\0';
            count++;
        }
    }
    fclose(file);
    return count;
}

/**
 * @brief Initializes guessed word and mask from secret word
 */
void InitializeGuessedWord(const char *secretWord, char *guessedWord, bool *revealedMask, int *uniqueLetterCount) {
    int length = strlen(secretWord);
    *uniqueLetterCount = 0;
    bool letterPresent[26] = {false};

    for (int i = 0; i < length; i++) {
        char c = secretWord[i];
        if (isalpha((unsigned char)c)) {
            guessedWord[i] = '_';
            revealedMask[i] = false;
            char lc = tolower(c);
            if (!letterPresent[lc - 'a']) {
                letterPresent[lc - 'a'] = true;
                (*uniqueLetterCount)++;
            }
        } else {
            guessedWord[i] = c;
            revealedMask[i] = true;
        }
    }
    guessedWord[length] = '\0';
}

/**
 * @brief Randomly reveals some letters
 */
void RandomlyRevealLetters(const char *secretWord, char *guessedWord, bool *revealedMask, int revealCount, int *correctGuessCount) {
    int length = strlen(secretWord);
    int attempts = 0;
    while (revealCount > 0 && attempts < 1000) {
        int pos = rand() % length;
        if (!revealedMask[pos] && isalpha((unsigned char)secretWord[pos])) {
            guessedWord[pos] = tolower(secretWord[pos]);
            revealedMask[pos] = true;
            (*correctGuessCount)++;
            revealCount--;
        }
        attempts++;
    }
}

/**
 * @brief Initializes full game state with random word
 */
void InitializeGame(const WordEntry *wordList, int wordCount, char *topic, char *secretWord,
                    char *guessedWord, bool *revealedMask, int *uniqueLetterCount,
                    int *correctGuessCount, int *failedAttempts, bool *isGameOver,
                    bool *isWin, bool *guessedLetters, KeyboardKey *keys, int keyCount,
                    int *alphaPositionsTotal) {
    int idx = rand() % wordCount;
    strncpy(topic, wordList[idx].topic, MAX_WORD_LENGTH - 1);
    topic[MAX_WORD_LENGTH - 1] = '\0';
    strncpy(secretWord, wordList[idx].word, MAX_WORD_LENGTH - 1);
    secretWord[MAX_WORD_LENGTH - 1] = '\0';

    int len = strlen(secretWord);
    for (int i = 0; i < len; i++) secretWord[i] = tolower(secretWord[i]);

    InitializeGuessedWord(secretWord, guessedWord, revealedMask, uniqueLetterCount);

    int revealCount = (len <= 6) ? 2 : 3;
    if (len < 5) revealCount = 1;

    *correctGuessCount = 0;
    RandomlyRevealLetters(secretWord, guessedWord, revealedMask, revealCount, correctGuessCount);

    *failedAttempts = 0;
    *isGameOver = false;
    *isWin = false;
    memset(guessedLetters, 0, 26 * sizeof(bool));

    for (int i = 0; i < keyCount; i++) keys[i].isPressed = false;

    *alphaPositionsTotal = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha((unsigned char)secretWord[i])) (*alphaPositionsTotal)++;
    }
}

/**
 * @brief Processes a single letter guess
 * @return true if correct guess
 */
bool ProcessGuess(char letter, const char *secretWord, char *guessedWord, bool *revealedMask,
                  bool *guessedLetters, int *correctGuessCount, int *failedAttempts,
                  KeyboardKey *keys, int keyCount) {
    int li = letter - 'a';
    if (li < 0 || li >= 26 || guessedLetters[li]) return false;

    guessedLetters[li] = true;

    for (int i = 0; i < keyCount; i++) {
        if (tolower(keys[i].letter) == letter) {
            keys[i].isPressed = true;
            break;
        }
    }

    bool found = false;
    int len = strlen(secretWord);
    for (int i = 0; i < len; i++) {
        if (tolower(secretWord[i]) == letter && !revealedMask[i]) {
            guessedWord[i] = letter;
            revealedMask[i] = true;
            (*correctGuessCount)++;
            found = true;
        }
    }

    if (!found) (*failedAttempts)++;

    return found;
}

/**
 * @brief Checks win/lose condition
 */
void CheckGameOver(const bool *revealedMask, int wordLength, int alphaTotal,
                   int failedAttempts, bool *isGameOver, bool *isWin) {
    int revealedAlpha = 0;
    for (int i = 0; i < wordLength; i++) {
        if (revealedMask[i] && isalpha((unsigned char)revealedMask[i])) revealedAlpha++;
    }

    if (revealedAlpha == alphaTotal) {
        *isGameOver = true;
        *isWin = true;
    } else if (failedAttempts >= MAX_TRIES) {
        *isGameOver = true;
        *isWin = false;
    }
}
