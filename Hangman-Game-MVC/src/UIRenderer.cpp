#include "UIRenderer.h"
#include "HangmanAnimator.h"
// UIRenderer.cpp এর উপরে (global বা static)
static HangmanAnimator hangmanAnim;


void UIRenderer::DrawHangmanFigure(int failedAttempts) {
    hangmanAnim.Update(failedAttempts, GetFrameTime());

    Vector2 ropeHook = {390, 210};
    hangmanAnim.Draw(ropeHook, failedAttempts);

    // Gallows
    DrawRectangle(180, 560, 280, 20, DARKGRAY);
    DrawLineEx({250, 560}, {250, 150}, 18, {40, 40, 40, 255});
    DrawLineEx({250, 150}, {390, 150}, 18, {40, 40, 40, 255});
    DrawLineEx({390, 150}, {390, 210}, 8, DARKBROWN);
}

void UIRenderer::DrawGuessedWord(const std::string& guessedWord, int startX, int py) {
    int spacing = 42;
    int len = static_cast<int>(guessedWord.length());

    for (int i = 0; i < len; ++i) {
        Rectangle cell = {(float)(startX + i * spacing), (float)py, 38, 52};

        // Cell background & border
        DrawRectangleRec(cell, Fade(WHITE, 0.9f));
        DrawRectangleLinesEx(cell, 3, BLACK);

        // Letter (White color)
        if (guessedWord[i] != '_') {
            char s[2] = {guessedWord[i], '\0'};
            int textWidth = MeasureText(s, 34);
            int textX = (int)(cell.x + (cell.width - textWidth) / 2);
            int textY = (int)(cell.y + (cell.height - 34) / 2) - 2;

            DrawText(s, textX, textY, 34, BLACK);   // ← White করা হয়েছে
        }
    }
}

void UIRenderer::DrawGameUI(const GameState& state, const KeyboardManager& keyboard) {
    // Background
    ClearBackground({34, 120, 50, 255});
    DrawRectangleGradientV(0, 0, WINDOW_WIDTH, 420, SKYBLUE, Fade(LIGHTGRAY, 0.6f));
    DrawRectangle(0, 380, WINDOW_WIDTH, WINDOW_HEIGHT - 380, {40, 140, 60, 255});

    DrawCircle(200, 420, 180, Fade({30, 110, 45, 255}, 0.9f));
    DrawCircle(800, 450, 220, Fade({30, 110, 45, 255}, 0.9f));

    DrawTree(120, 320, 1.1f);
    DrawTree(650, 290, 0.9f);
    DrawTree(1050, 340, 1.2f);

    DrawHouse(180, 380, {180, 80, 40, 255}, {220, 50, 30, 255});
    DrawHouse(920, 410, {160, 70, 35, 255}, {200, 45, 25, 255});
    DrawAnimal(480, 460);

    DrawRectangle(0, 520, WINDOW_WIDTH, WINDOW_HEIGHT - 520, {25, 105, 45, 255});

    // ==================== FIXED UI LAYOUT ====================

    // Top Bar
    DrawRectangle(0, 0, WINDOW_WIDTH, 100, Fade(SKYBLUE, 0.92f));
   // DrawRectangleLinesEx({0, 0, (float)WINDOW_WIDTH, 100}, 6, GOLD);

        const char* title = "HANGMAN";
    int titleSize = 78;   // আরও বড়
    int titleX = (WINDOW_WIDTH - MeasureText(title, titleSize)) / 2;

    // Shadow
    //DrawText(title, titleX + 6, 26, titleSize, Fade(BLACK, 0.35f));

    // Bold layers
    DrawText(title, titleX - 3, 15, titleSize, DARKBLUE);
    DrawText(title, titleX + 3, 15, titleSize, DARKBLUE);
    DrawText(title, titleX,     15, titleSize, DARKBLUE);     // মেইন লেয়ার

    // Restart & Quit Buttons (Single & Lower)
    int btnY = 115;
    DrawRectangle(950, btnY, 140, 52, Fade(LIGHTGRAY, 0.95f));
    DrawRectangleLinesEx({950, (float)btnY, 140, 52}, 4, WHITE);
    DrawText("Restart", 980, btnY + 16, 22, BLACK);

    DrawRectangle(1100, btnY, 130, 52, Fade(LIGHTGRAY, 0.95f));
    DrawRectangleLinesEx({1100, (float)btnY, 130, 52}, 4, WHITE);
    DrawText("Quit", 1135, btnY + 16, 22, BLACK);

    // Topic (Lower)
    DrawRectangle(680, 205, 520, 55, Fade(WHITE, 0.95f));
    DrawRectangleLinesEx({680, 205, 520, 55}, 4, PURPLE);
    DrawText(TextFormat("Topic: %s", state.GetTopic().c_str()), 700, 218, 28, BLACK);

    // Lives
    int lives = MAX_TRIES - state.GetFailedAttempts();
    Color livesColor = (lives <= 2) ? RED : YELLOW;
    DrawText(TextFormat("Lives: %d / %d", lives, MAX_TRIES), 1050, 280, 26, livesColor);

    // Guess the word
    DrawText("Guess the word!!", 680, 295, 32, PINK);

    // Guessed Word Cells (Lower)
    DrawGuessedWord(state.GetGuessedWord(), 680, 340);

    // Hangman Area
    DrawRectangle(70, 140, 540, 490, Fade(WHITE, 0.88f));
    DrawRectangleLinesEx({70, 140, 540, 490}, 10, Fade(BROWN, 0.6f));

    DrawHangmanFigure(state.GetFailedAttempts());

    // Keyboard
    DrawText("On-screen Keyboard", 60, 645, 22, WHITE);
    keyboard.Draw();
}
void UIRenderer::DrawGameOverScreen(const GameState& state) {
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, 0.45f));
    if (state.IsWin()) {
        DrawText("CONGRATULATIONS! You Win !!", 250, 300, 40, LIME);
        DrawText(TextFormat("Word: %s", state.GetSecretWord().c_str()), 320, 360, 28, LIGHTGRAY);
    } else {
        DrawText("GAME OVER!", 340, 300, 40, RED);
        DrawText(TextFormat("The word was: %s", state.GetSecretWord().c_str()), 310, 360, 38, WHITE);
    }
    DrawText("Click Restart or press ESC to quit", 220, 420, 28, WHITE);
}
// ====================== RURAL BACKGROUND HELPERS ======================

void UIRenderer::DrawTree(int x, int y, float scale) {
    // Trunk
    DrawRectangle(x - 8, y + 20, 16, 70, BROWN);
    // Leaves
    DrawCircle(x, y, 38 * scale, DARKGREEN);
    DrawCircle(x - 22, y + 10, 32 * scale, GREEN);
    DrawCircle(x + 22, y + 8, 30 * scale, GREEN);
}

void UIRenderer::DrawHouse(int x, int y, Color wallColor, Color roofColor) {
    // Wall
    DrawRectangle(x, y, 85, 65, wallColor);
    // Roof
    DrawTriangle({(float)x - 5, (float)y}, {(float)x + 45, (float)y - 35}, {(float)x + 92, (float)y}, roofColor);
    // Door
    DrawRectangle(x + 30, y + 35, 20, 30, DARKBROWN);
    // Window
    DrawRectangle(x + 8, y + 12, 18, 18, SKYBLUE);
}

void UIRenderer::DrawAnimal(int x, int y) {
    // Body
    DrawRectangle(x, y, 55, 32, LIGHTGRAY);
    // Head
    DrawCircle(x + 55, y + 12, 14, LIGHTGRAY);
    // Ear
    DrawTriangle({(float)x + 60, (float)y + 5}, {(float)x + 68, (float)y}, {(float)x + 65, (float)y + 18}, GRAY);
    // Legs
    DrawRectangle(x + 8, y + 28, 8, 18, GRAY);
    DrawRectangle(x + 35, y + 28, 8, 18, GRAY);
    // Spot
    DrawCircle(x + 15, y + 12, 7, GRAY);
}
