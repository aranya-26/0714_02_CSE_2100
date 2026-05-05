#include "HangmanAnimator.h"
#include <cmath>

void HangmanAnimator::Reset() {
    swayAngle = 0.0f;
    deathTimer = 0.0f;
    isDead = false;
}

void HangmanAnimator::Update(int failedAttempts, float deltaTime) {
    if (failedAttempts >= 6) {
        isDead = true;
        deathTimer += deltaTime;
        swayAngle = sin(deathTimer * 7.0f) * 11.0f;   // দুলানো
    } else {
        isDead = false;
        swayAngle = 0.0f;
    }
}

void HangmanAnimator::Draw(const Vector2& ropeHook, int failedAttempts) {
    Color bodyColor = {139, 69, 19, 255};      // Saddle Brown
    Color outlineColor = DARKGRAY;

    Vector2 headPos = {ropeHook.x, ropeHook.y + 28};

    // Rope
    DrawLineEx(ropeHook, {headPos.x, headPos.y - 34}, 7, BROWN);

    // ==================== STEP BY STEP DRAWING ====================

    // 1. Head
    if (failedAttempts >= 1) {
        DrawCircle(headPos.x, headPos.y, 34, bodyColor);
        DrawCircleLines(headPos.x, headPos.y, 34, outlineColor);

        if (failedAttempts >= 6) { // Dead face
            // Closed eyes
            DrawLine(headPos.x - 12, headPos.y - 5, headPos.x - 4, headPos.y + 2, BLACK);
            DrawLine(headPos.x + 4, headPos.y - 5, headPos.x + 12, headPos.y + 2, BLACK);
            // Tongue
            DrawLine(headPos.x - 9, headPos.y + 13, headPos.x + 9, headPos.y + 18, RED);
        } else {
            // Normal eyes
            DrawCircle(headPos.x - 10, headPos.y - 6, 6, WHITE);
            DrawCircle(headPos.x + 10, headPos.y - 6, 6, WHITE);
            DrawCircle(headPos.x - 10, headPos.y - 6, 3, BLACK);
            DrawCircle(headPos.x + 10, headPos.y - 6, 3, BLACK);
        }
    }

    // 2. Body
    Vector2 bodyTop = {headPos.x, headPos.y + 34};
    Vector2 bodyBot = {headPos.x, headPos.y + 148};
    if (failedAttempts >= 2) {
        DrawLineEx(bodyTop, bodyBot, 24, bodyColor);
    }

    // 3. Left Arm
    if (failedAttempts >= 3) {
        DrawLineEx(bodyTop, {bodyTop.x - 48, bodyTop.y + 55}, 19, bodyColor);
    }
    // 4. Right Arm
    if (failedAttempts >= 4) {
        DrawLineEx(bodyTop, {bodyTop.x + 48, bodyTop.y + 55}, 19, bodyColor);
    }
    // 5. Left Leg
    if (failedAttempts >= 5) {
        DrawLineEx(bodyBot, {bodyBot.x - 30, bodyBot.y + 75}, 19, bodyColor);
    }
    // 6. Right Leg
    if (failedAttempts >= 6) {
        DrawLineEx(bodyBot, {bodyBot.x + 30, bodyBot.y + 75}, 19, bodyColor);
    }

    // ==================== ONLY WHEN DEAD - FULL BODY ANIMATION ====================
    if (failedAttempts >= 6 && isDead) {
        float sway = swayAngle;

        // Redraw head with sway
        Vector2 swayHead = {headPos.x + sway * 0.7f, headPos.y};
        DrawCircle(swayHead.x, swayHead.y, 34, bodyColor);
        DrawCircleLines(swayHead.x, swayHead.y, 34, outlineColor);
        DrawLine(swayHead.x - 12, swayHead.y - 5, swayHead.x - 4, swayHead.y + 2, BLACK);
        DrawLine(swayHead.x + 4, swayHead.y - 5, swayHead.x + 12, swayHead.y + 2, BLACK);
        DrawLine(swayHead.x - 9, swayHead.y + 13, swayHead.x + 9, swayHead.y + 18, RED);

        // Redraw body parts with sway
        DrawLineEx(bodyTop, {bodyBot.x + sway * 0.4f, bodyBot.y}, 24, bodyColor);
        DrawLineEx(bodyTop, {bodyTop.x - 48 + sway, bodyTop.y + 55}, 19, bodyColor);
        DrawLineEx(bodyTop, {bodyTop.x + 48 + sway, bodyTop.y + 55}, 19, bodyColor);
        DrawLineEx(bodyBot, {bodyBot.x - 30 + sway * 0.6f, bodyBot.y + 75}, 19, bodyColor);
        DrawLineEx(bodyBot, {bodyBot.x + 30 + sway * 0.6f, bodyBot.y + 75}, 19, bodyColor);
    }
}
