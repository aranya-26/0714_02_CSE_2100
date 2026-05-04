#include "HangmanController.h"
#include <ctime>

HangmanController::HangmanController() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Debug information
    TraceLog(LOG_INFO, "Current Working Directory: %s", GetWorkingDirectory());

    wordList = WordLoader::LoadWords("words_1000.txt");

    if (wordList.empty()) {
        TraceLog(LOG_WARNING, "words.txt not found or empty!");

        // Try with full relative path
        wordList = WordLoader::LoadWords("../../../words.txt");  // যদি bin/Debug এ চলে

        if (wordList.empty()) {
            TraceLog(LOG_WARNING, "Still not found. Using minimal defaults.");
            wordList.push_back({"Fruits", "mango"});
            wordList.push_back({"Country", "bangladesh"});
            wordList.push_back({"Animal", "tiger"});
        }
    }

    wordCount = static_cast<int>(wordList.size());

    TraceLog(LOG_INFO, "Total words loaded: %d", wordCount);

    keyboardManager.Initialize();
    LoadSounds();
    Restart();
}

HangmanController::~HangmanController() {
    UnloadSound(correctSound);
    UnloadSound(wrongSound);
    UnloadSound(winSound);
    UnloadSound(loseSound);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

void HangmanController::LoadSounds() {
    InitAudioDevice();
    correctSound = LoadSound("sounds/correct.mp3");
    wrongSound   = LoadSound("sounds/wrong.mp3");
    winSound     = LoadSound("sounds/win.mp3");
    loseSound    = LoadSound("sounds/lose.mp3");
    backgroundMusic = LoadMusicStream("sounds/background.mp3");

    PlayMusicStream(backgroundMusic);
}

void HangmanController::Restart() {
    if (wordCount > 0) {
        int idx = rand() % wordCount;
        gameState.Initialize(wordList[idx]);
    }
    keyboardManager.Reset();
}

void HangmanController::PlayGuessSound(bool isCorrect) {
    if (isCorrect) PlaySound(correctSound);
    else PlaySound(wrongSound);
}

void HangmanController::PlayGameOverSound() {
    if (gameState.IsWin()) PlaySound(winSound);
    else PlaySound(loseSound);
}

void HangmanController::Run() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hangman Game - MVC Version");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMusicStream(backgroundMusic);

        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Input Handling
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

        bool isCorrectGuess = false;
        if (!gameState.IsGameOver() && letter) {
            int prevFailed = gameState.GetFailedAttempts();
            gameState.ProcessGuess(letter);
            isCorrectGuess = (gameState.GetFailedAttempts() == prevFailed);
        }

        gameState.CheckGameOver();

        // Sound
        if (letter && !gameState.IsGameOver()) {
            PlayGuessSound(isCorrectGuess);
        }
        if (gameState.IsGameOver() && letter) {   // শুধু একবার প্লে করার জন্য
            PlayGameOverSound();
        }

        // Buttons
        int panelX = WINDOW_WIDTH - 300;
        Rectangle restartBtn = { (float)panelX + 20, 50, 220, 42 };
        if (CheckCollisionPointRec(mouse, restartBtn) && clicked) {
            Restart();
        }

        Rectangle quitBtn = { (float)panelX + 20, 110, 220, 42 };
        if (CheckCollisionPointRec(mouse, quitBtn) && clicked) {
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // View Layer
        UIRenderer::DrawGameUI(gameState, keyboardManager);

        // Draw Buttons
        bool hoverRestart = CheckCollisionPointRec(mouse, restartBtn);
        bool hoverQuit = CheckCollisionPointRec(mouse, quitBtn);

        DrawRectangleRec(restartBtn, hoverRestart ? SKYBLUE : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(restartBtn, 2, GRAY);
        DrawText("Restart", 1070, 60, 20, BLACK);

        DrawRectangleRec(quitBtn, hoverQuit ? PINK : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(quitBtn, 2, GRAY);
        DrawText("Quit", 1090, 120, 20, BLACK);

        if (gameState.IsGameOver()) {
            UIRenderer::DrawGameOverScreen(gameState);
        }

        EndDrawing();
    }

    CloseWindow();
}
