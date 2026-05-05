#ifndef HANGMAN_ANIMATOR_H
#define HANGMAN_ANIMATOR_H

#include "raylib.h"

struct HangmanAnimator {
    float swayAngle = 0.0f;
    float deathTimer = 0.0f;
    bool isDead = false;

    void Update(int failedAttempts, float deltaTime);
    void Draw(const Vector2& ropeHook, int failedAttempts);
    void Reset();
};

#endif
