/**
 * @file hangman_main.c
 * @brief Main entry point and game loop
 */

#include "raylib.h"
#include "hangman_types.h"
#include "hangman_game_logic.c"   // Note: In real project use .h if split further
#include "hangman_ui.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hangman Game");
    SetTargetFPS(60);
    srand((unsigned)time(NULL));

    WordEntry wordList[MAX_WORDS];
    int wordCount = LoadWordList("words.txt", wordList, MAX_WORDS);
    if (wordCount == 0) {
        strcpy(wordList[0].topic, "Fruits"); strcpy(wordList[0].word, "banana");
        strcpy(wordList[1].topic, "Country"); strcpy(wordList[1].word, "bangladesh");
        wordCount = 2;
    }

    KeyboardKey keys[26];
    int keyCount = InitializeKeyboard(keys);

    // Game state
    char topic[MAX_WORD_LENGTH];
    char secretWord[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    bool revealedMask[MAX_WORD_LENGTH];
    int uniqueLetterCount, correctGuessCount, failedAttempts, alphaPositionsTotal;
    bool isGameOver = false, isWin = false;
    bool guessedLetters[26] = {false};

    InitializeGame(wordList, wordCount, topic, secretWord, guessedWord, revealedMask,
                   &uniqueLetterCount, &correctGuessCount, &failedAttempts, &isGameOver,
                   &isWin, guessedLetters, keys, keyCount, &alphaPositionsTotal);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        char inputLetter = 0;
        for (int k = 0; k < 26; k++) {
            if (IsKeyPressed(KEY_A + k)) {
                inputLetter = 'a' + k;
                break;
            }
        }

        char mouseLetter = HandleKeyboardInput(keys, keyCount, mouse, clicked);
        char letter = mouseLetter ? mouseLetter : inputLetter;

        if (!isGameOver && letter) {
            ProcessGuess(letter, secretWord, guessedWord, revealedMask, guessedLetters,
                         &correctGuessCount, &failedAttempts, keys, keyCount);
        }

        CheckGameOver(revealedMask, strlen(secretWord), alphaPositionsTotal,
                      failedAttempts, &isGameOver, &isWin);

        // Restart / Quit buttons
        Rectangle restartBtn = {720, 40, 220, 42};
        bool hoverRestart = CheckCollisionPointRec(mouse, restartBtn);
        if (hoverRestart && clicked) {
            InitializeGame(wordList, wordCount, topic, secretWord, guessedWord, revealedMask,
                           &uniqueLetterCount, &correctGuessCount, &failedAttempts, &isGameOver,
                           &isWin, guessedLetters, keys, keyCount, &alphaPositionsTotal);
        }

        Rectangle quitBtn = {720, 100, 220, 42};
        bool hoverQuit = CheckCollisionPointRec(mouse, quitBtn);
        if (hoverQuit && clicked) break;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        DrawRectangle(0, 0, WINDOW_WIDTH, 100, Fade(LIGHTGRAY, 0.08f));
        DrawText("HANGMAN", 350, 14, 52, DARKBLUE);
        DrawText(TextFormat("Topic: %s", topic), 30, 52, 20, DARKGRAY);

        // Controls panel
        DrawRectangle(700, 20, 280, 160, Fade(RAYWHITE, 0.6f));
        DrawText("Controls", 760, 10, 22, BLUE);
        DrawRectangleRec(restartBtn, hoverRestart ? SKYBLUE : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(restartBtn, 2, GRAY);
        DrawText("Restart (Click)", 760, 52, 20, BLACK);
        DrawRectangleRec(quitBtn, hoverQuit ? PINK : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(quitBtn, 2, GRAY);
        DrawText("Quit (Click)", 760, 112, 20, BLACK);

        DrawText(TextFormat("Lives: %d / %d", MAX_TRIES - failedAttempts, MAX_TRIES), 740, 180, 22, RED);

        // Guessed word
        DrawText("Guess the word:", 430, 120, 20, DARKGRAY);
        DrawGuessedWord(guessedWord, 480, 160);

        DrawHangmanFigure(failedAttempts);

        DrawText("On-screen keyboard", 40, 380, 18, YELLOW);
        HandleKeyboardInput(keys, keyCount, mouse, false);  // Draw only

        if (isGameOver) {
            DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, 0.45f));
            if (isWin) {
                DrawText("CONGRATULATIONS! You Win !!", 250, 300, 40, LIME);
                DrawText(TextFormat("Word: %s", secretWord), 320, 360, 28, LIGHTGRAY);
            } else {
                DrawText("GAME OVER!", 340, 300, 40, RED);
                DrawText(TextFormat("The word was: %s", secretWord), 310, 360, 28, LIGHTGRAY);
            }
            DrawText("Click Restart or press ESC to quit", 220, 420, 18, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
