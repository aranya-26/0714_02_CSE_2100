/**
 * @file main.c
 * @brief Main entry point with SOLID principles (SRP + DIP + OCP)
 */

#include "raylib.h"
#include "hangman_types.h"
#include "word_provider.h"
#include "game_state.h"
#include "game_logic.c"     // For now include (later make .h)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hangman Game - SOLID Refactored");
    SetTargetFPS(60);
    srand((unsigned)time(NULL));

    // WordProvider - DIP & OCP applied
    WordProvider wordProvider = createFileWordProvider("words.txt");

    WordEntry wordList[MAX_WORDS];
    int wordCount = wordProvider.loadWords(&wordProvider, wordList, MAX_WORDS);

    if (wordCount == 0) {
        strcpy(wordList[0].topic, "Fruits"); 
        strcpy(wordList[0].word, "banana");
        strcpy(wordList[1].topic, "Country"); 
        strcpy(wordList[1].word, "bangladesh");
        wordCount = 2;
    }

    Game game = {0};
    game.keyCount = InitializeKeyboard(game.keys);

    // Initialize game using abstraction
    InitializeGame(&game, &wordProvider, wordList, wordCount);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Input
        char letter = 0;
        for (int k = 0; k < 26; k++) {
            if (IsKeyPressed(KEY_A + k)) {
                letter = 'a' + k;
                break;
            }
        }
        if (letter == 0) {
            letter = HandleKeyboardInput(game.keys, game.keyCount, mouse, clicked);
        }

        if (!game.isGameOver && letter) {
            ProcessGuess(&game, letter);
        }

        CheckGameOver(&game);

        // Restart
        Rectangle restartBtn = {720, 40, 220, 42};
        if (CheckCollisionPointRec(mouse, restartBtn) && clicked) {
            InitializeGame(&game, &wordProvider, wordList, wordCount);
        }

        // Quit
        Rectangle quitBtn = {720, 100, 220, 42};
        if (CheckCollisionPointRec(mouse, quitBtn) && clicked) {
            break;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        DrawRectangle(0, 0, WINDOW_WIDTH, 100, Fade(LIGHTGRAY, 0.08f));
        DrawText("HANGMAN", 350, 14, 52, DARKBLUE);
        DrawText(TextFormat("Topic: %s", game.topic), 30, 52, 20, DARKGRAY);

        DrawText("Guess the word:", 430, 120, 20, DARKGRAY);
        DrawGuessedWord(game.guessedWord, 480, 160);

        DrawHangmanFigure(game.failedAttempts);

        DrawText("On-screen keyboard", 40, 380, 18, YELLOW);
        HandleKeyboardInput(game.keys, game.keyCount, mouse, false);  // Draw only

        DrawText(TextFormat("Lives: %d / %d", MAX_TRIES - game.failedAttempts, MAX_TRIES), 
                 740, 180, 22, RED);

        if (game.isGameOver) {
            DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, 0.45f));
            if (game.isWin) {
                DrawText("CONGRATULATIONS! You Win !!", 250, 300, 40, LIME);
                DrawText(TextFormat("Word: %s", game.secretWord), 320, 360, 28, LIGHTGRAY);
            } else {
                DrawText("GAME OVER!", 340, 300, 40, RED);
                DrawText(TextFormat("The word was: %s", game.secretWord), 310, 360, 28, LIGHTGRAY);
            }
        }

        // Controls Panel
        DrawRectangle(700, 20, 280, 160, Fade(RAYWHITE, 0.6f));
        DrawText("Controls", 760, 10, 22, BLUE);
        DrawRectangleRec(restartBtn, CheckCollisionPointRec(mouse, restartBtn) ? SKYBLUE : Fade(LIGHTGRAY, 0.9f));
        DrawText("Restart (Click)", 760, 52, 20, BLACK);
        DrawRectangleRec(quitBtn, CheckCollisionPointRec(mouse, quitBtn) ? PINK : Fade(LIGHTGRAY, 0.9f));
        DrawText("Quit (Click)", 760, 112, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}