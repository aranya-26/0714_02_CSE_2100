#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "hangman_types.h"
#include <vector>

class KeyboardManager {
private:
    std::vector<KeyboardKey> keys;

public:
    void Initialize();
    char HandleInput(Vector2 mousePos, bool clicked);
    void Draw(bool onlyDraw = false);
    void Reset();
    const std::vector<KeyboardKey>& GetKeys() const { return keys; }
};

#endif
