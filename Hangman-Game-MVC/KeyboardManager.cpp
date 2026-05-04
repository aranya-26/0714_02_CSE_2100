#include "KeyboardManager.h"
#include <cctype>

void KeyboardManager::Initialize() {
   const char* rows[] = {
    "QWERTYUIOP",
    "ASDFGHJKL",
    "ZXCVBNM"
};
    keys.clear();
    int y = KEYBOARD_START_Y;

    for (int r = 0; r < 3; ++r) {
        int x = KEYBOARD_MARGIN_X;
        if (r == 2) x += 24;
        for (int i = 0; rows[r][i]; ++i) {
            MyKey k;
            k.rectangle = {(float)x, (float)y, (float)KEYBOARD_KEY_WIDTH, (float)KEYBOARD_KEY_HEIGHT};
            k.letter = rows[r][i];
            k.isPressed = false;
            k.isVisible = true;
            keys.push_back(k);
            x += KEYBOARD_KEY_WIDTH + KEYBOARD_GAP;
        }
        y += KEYBOARD_KEY_HEIGHT + KEYBOARD_GAP;
    }
}

char KeyboardManager::HandleInput(Vector2 mousePos, bool clicked) {
    char pressed = 0;
    for (auto& key : keys) {
        if (!key.isVisible) continue;

        if (CheckCollisionPointRec(mousePos, key.rectangle)) {
            if (clicked && !key.isPressed) {
                key.isPressed = true;
                pressed = std::tolower(key.letter);
            }
        }
    }
    return pressed;
}

void KeyboardManager::Draw(bool onlyDraw) const {
    for (const auto& key : keys) {
        if (!key.isVisible) continue;
        Color bg = key.isPressed ? Fade(DARKGREEN, 0.9f) : LIGHTGRAY;
        DrawRectangleRec(key.rectangle, bg);
        DrawRectangleLinesEx(key.rectangle, 2, Fade(GRAY, 0.7f));
        DrawText(TextFormat("%c", key.letter), (int)(key.rectangle.x + 15), (int)(key.rectangle.y + 8), 22, BLACK);
    }
}

void KeyboardManager::Reset() {
    for (auto& key : keys) key.isPressed = false;
}
