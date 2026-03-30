#include "HangmanGame.h"
#include <ctime>

HangmanGame::HangmanGame() {
    srand(static_cast<unsigned>(time(nullptr)));
    wordList = WordLoader::LoadWords("words.txt");

    if (wordList.empty()) {
        wordList.push_back({"Fruits", "banana"});
        wordList.push_back({"Country", "bangladesh"});
    }
    wordCount = static_cast<int>(wordList.size());

    keyboardManager.Initialize();
    Restart();
}

void HangmanGame::Restart() {
    if (wordCount > 0) {
        int idx = rand() % wordCount;
        gameState.Initialize(wordList[idx]);
    }
    keyboardManager.Reset();
}

void HangmanGame::Run() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hangman Game - SOLID Refactored");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Input
        char letter = 0;
        for (int k = 0; k < 26; ++k) {
            if (IsKeyPressed(KEY_A + k)) {
                letter = 'a' + k;
                break;
            }
        }
        if (!letter) {
            letter = keyboardManager.HandleInput(mouse, clicked);
        }

        if (!gameState.IsGameOver() && letter) {
            gameState.ProcessGuess(letter);
        }

        gameState.CheckGameOver();

        // Restart Button
        Rectangle restartBtn = {720, 40, 220, 42};
        if (CheckCollisionPointRec(mouse, restartBtn) && clicked) {
            Restart();
        }

        // Quit Button
        Rectangle quitBtn = {720, 100, 220, 42};
        if (CheckCollisionPointRec(mouse, quitBtn) && clicked) {
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        UIRenderer::DrawGameUI(gameState, keyboardManager);

        // Buttons drawing
        bool hoverRestart = CheckCollisionPointRec(mouse, restartBtn);
        bool hoverQuit = CheckCollisionPointRec(mouse, quitBtn);

        DrawRectangleRec(restartBtn, hoverRestart ? SKYBLUE : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(restartBtn, 2, GRAY);
        DrawText("Restart", 760, 52, 20, BLACK);

        DrawRectangleRec(quitBtn, hoverQuit ? PINK : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(quitBtn, 2, GRAY);
        DrawText("Quit", 760, 112, 20, BLACK);

        if (gameState.IsGameOver()) {
            UIRenderer::DrawGameOverScreen(gameState);
        }

        EndDrawing();
    }

    CloseWindow();
}
