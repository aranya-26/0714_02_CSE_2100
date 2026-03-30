#include "UIRenderer.h"

void UIRenderer::DrawHangmanFigure(int failedAttempts) {
    DrawRectangleLines(120, 120, 260, 380, Fade(BLACK, 0.6f));
    DrawLine(200, 500, 420, 500, DARKGRAY);
    DrawLine(250, 500, 250, 160, DARKGRAY);
    DrawLine(250, 160, 370, 160, DARKGRAY);
    DrawLine(370, 160, 370, 210, DARKGRAY);

    if (failedAttempts >= 1) {
        DrawCircle(370, 235, 30, BLACK);
        DrawCircleLines(370, 235, 30, GRAY);
    }
    if (failedAttempts >= 2) DrawLine(370, 265, 370, 360, BLACK);
    if (failedAttempts >= 3) DrawLine(370, 290, 330, 330, BLACK);
    if (failedAttempts >= 4) DrawLine(370, 290, 410, 330, BLACK);
    if (failedAttempts >= 5) DrawLine(370, 360, 330, 410, BLACK);
    if (failedAttempts >= 6) DrawLine(370, 360, 410, 410, BLACK);

    if (failedAttempts > 0) DrawRectangle(120, 120, 260, 380, Fade(RAYWHITE, 0.02f));
}

void UIRenderer::DrawGuessedWord(const std::string& guessedWord, int startX, int py) {
    int spacing = 40;
    int len = static_cast<int>(guessedWord.length());
    for (int i = 0; i < len; ++i) {
        Rectangle cell = {(float)(startX + i * spacing), (float)py, 36, 48};
        DrawRectangleLinesEx(cell, 2, Fade(GRAY, 0.6f));
        if (guessedWord[i] != '_') {
            char s[2] = {guessedWord[i], '\0'};
            DrawText(s, (int)(cell.x + 6), (int)(cell.y + 6), 30, MAROON);
        }
    }
}

void UIRenderer::DrawGameUI(const GameState& state, const KeyboardManager& keyboard) {
    // Header
    DrawRectangle(0, 0, WINDOW_WIDTH, 100, Fade(LIGHTGRAY, 0.08f));
    DrawText("HANGMAN", 350, 14, 52, DARKBLUE);
    DrawText(TextFormat("Topic: %s", state.GetTopic().c_str()), 30, 52, 20, DARKGRAY);

    // Controls
    DrawRectangle(700, 20, 280, 160, Fade(RAYWHITE, 0.6f));
    DrawText("Controls", 760, 10, 22, BLUE);

    // Lives
    DrawText(TextFormat("Lives: %d / %d", MAX_TRIES - state.GetFailedAttempts(), MAX_TRIES), 740, 180, 22, RED);

    // Guessed word
    DrawText("Guess the word:", 430, 120, 20, DARKGRAY);
    DrawGuessedWord(state.GetGuessedWord(), 480, 160);

    DrawHangmanFigure(state.GetFailedAttempts());

    DrawText("On-screen keyboard", 40, 380, 18, YELLOW);
    keyboard.Draw(true);   // only draw
}

void UIRenderer::DrawGameOverScreen(const GameState& state) {
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, 0.45f));
    if (state.IsWin()) {
        DrawText("CONGRATULATIONS! You Win !!", 250, 300, 40, LIME);
        DrawText(TextFormat("Word: %s", state.GetSecretWord().c_str()), 320, 360, 28, LIGHTGRAY);
    } else {
        DrawText("GAME OVER!", 340, 300, 40, RED);
        DrawText(TextFormat("The word was: %s", state.GetSecretWord().c_str()), 310, 360, 28, LIGHTGRAY);
    }
    DrawText("Click Restart or press ESC to quit", 220, 420, 18, GRAY);
}
