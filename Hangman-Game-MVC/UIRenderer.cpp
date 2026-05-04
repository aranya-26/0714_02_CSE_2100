#include "UIRenderer.h"

void UIRenderer::DrawHangmanFigure(int failedAttempts) {
    // Base Gallows - Realistic Look
    DrawRectangle(180, 560, 280, 20, DARKGRAY);
    DrawLineEx({250, 560}, {250, 150}, 16, {40, 40, 40, 255});     // Main Pole
    DrawLineEx({250, 150}, {390, 150}, 16, {40, 40, 40, 255});     // Top Beam
    DrawLineEx({390, 150}, {390, 210}, 8, DARKBROWN);              // Rope Hook

    // Rope
    if (failedAttempts >= 1) {
        DrawLineEx({390, 210}, {390, 235}, 6, BROWN);
    }

    // ==================== REALISTIC HANGMAN FIGURE ====================
    Color bodyColor = {139, 69, 19, 255};      // Saddle Brown
    Color outlineColor = DARKGRAY;

    if (failedAttempts >= 1) { // Head
        DrawCircle(390, 255, 34, bodyColor);
        DrawCircleLines(390, 255, 34, outlineColor);

        // Eyes
        Color eyeColor = (failedAttempts >= 4) ? BLACK : MAROON;
        DrawCircle(378, 248, 6, eyeColor);
        DrawCircle(402, 248, 6, eyeColor);

        // Eye highlights
        DrawCircle(378, 248, 2, WHITE);
        DrawCircle(402, 248, 2, WHITE);
    }

    if (failedAttempts >= 2) { // Body
        DrawLineEx({390, 288}, {390, 400}, 22, bodyColor);
        DrawLineEx({390, 288}, {390, 400}, 22, Fade(BLACK, 0.15f));
    }

    if (failedAttempts >= 3) { // Left Arm
        DrawLineEx({390, 310}, {340, 360}, 18, bodyColor);
    }
    if (failedAttempts >= 4) { // Right Arm
        DrawLineEx({390, 310}, {440, 360}, 18, bodyColor);
    }

    if (failedAttempts >= 5) {
        DrawLineEx({390, 398}, {350, 560}, 18, bodyColor);
    }
    if (failedAttempts >= 6) {
        DrawLineEx({390, 398}, {430, 560}, 18, bodyColor);
    }

    // Despair effect on final stage
    if (failedAttempts >= 6) {
        DrawCircle(390, 255, 34, Fade(RED, 0.18f));
    }
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
    const char* title = "HANGMAN";
int textWidth = MeasureText(title, 52);

DrawText(title, (WINDOW_WIDTH - textWidth) / 2, 14, 52, DARKBLUE);
int rightStartX = WINDOW_WIDTH - 500;
    DrawText(TextFormat("Topic: %s", state.GetTopic().c_str()),
    rightStartX,
    400,
    30,
    PURPLE);

    // Controls
    int panelX = WINDOW_WIDTH - 300;

DrawRectangle(panelX, 20, 260, 160, Fade(RAYWHITE, 0.6f));
DrawText("Controls", panelX + 60, 10, 22, BLUE);

DrawText(TextFormat("Lives: %d / %d",
    MAX_TRIES - state.GetFailedAttempts(), MAX_TRIES),
    panelX + 20, 190, 22, RED);

    // Guessed word
    DrawText("Guess the word:",
    rightStartX,
    350,
    30,
    PURPLE);
    DrawGuessedWord(state.GetGuessedWord(),
    rightStartX,
    460);

    DrawHangmanFigure(state.GetFailedAttempts());

    DrawText("On-screen keyboard", 60, WINDOW_HEIGHT - 260, 18, BLUE);
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
    DrawText("Click Restart or press ESC to quit", 220, 420, 18, RED);
}
