#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "hangman_types.h"
#include <vector>

class KeyboardManager {
private:
    std::vector<MyKey> keys;

public:
    void Initialize();
    char HandleInput(Vector2 mousePos, bool clicked);
    void Draw(bool onlyDraw = false)const;
    void Reset();
    const std::vector<MyKey>& GetKeys() const { return keys; }
};

#endif
