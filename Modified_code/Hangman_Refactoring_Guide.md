# 🎮 Hangman Game — Code Refactoring & Software Engineering Standards Guide

**Course:** Advanced Programming Lab  
**Project:** Hangman Game (C Language with Raylib)  
**Purpose:** Improve code maintainability, readability, modularity, and scalability  
**Date:** February 2026

---

## 📑 Table of Contents

1. [Executive Summary](#executive-summary)
2. [Naming Conventions](#naming-conventions)
3. [Coding Style Guidelines](#coding-style-guidelines)
4. [Folder Structure](#folder-structure)
5. [Modular Design Principles](#modular-design-principles)
6. [Error Handling & Robustness](#error-handling--robustness)
7. [Testing Strategy](#testing-strategy)
8. [Refactoring Roadmap](#refactoring-roadmap)
9. [Future Improvements](#future-improvements)

---

## Executive Summary

### Current Project Overview
The Hangman Game is a graphical word-guessing game built with **Raylib** in C.

**Strengths:**
* Word loading from file (topic:word format)
* On-screen keyboard + physical keyboard input
* Progressive hangman figure drawing
* Random initial letter hints
* Win/lose detection with restart/quit functionality

**Areas for Improvement:**
* **Monolithic Structure:** All logic resides in a single file.
* **Naming Issues:** Inconsistent or overly short variable names.
* **Coupling:** Mixed concerns between game logic, UI, and input handling.
* **Documentation:** Minimal comments explaining the "why" behind the code.

### Refactoring Philosophy

> "Refactor incrementally without breaking gameplay functionality."

**Goals:**
* Cleaner code structure and easier debugging.
* Better scalability for adding new categories or levels.
* Improved readability for peer review.
* Adherence to professional coding standards.

---

## Naming Conventions

### Variable Naming Refactoring

| Before Refactoring | After Refactoring | Benefit |
| :--- | :--- | :--- |
| `int tries;` | `int failedAttempts;` | Descriptive intent |
| `char t[MAX_WORDS];` | `char topic[MAX_WORD_LENGTH];` | Avoids cryptic abbreviations |
| `bool p, vl;` | `bool isPressed, isVisible;` | Boolean clarity |

### Function Naming Refactoring

* **Before:** `void DrawHangman(int tries);`
* **After:** `void DrawHangmanFigure(int failedAttempts);`
* **Why:** Verb-based naming clarifies the specific action and supports modularity.

---

## Coding Style Guidelines

### Indentation & Layout
* **4 spaces** preferred (no tabs).
* Line length limited to **100 characters**.

### Comment Quality
**Before:**
```c
guessed[i] = '_'; // guess

After:
C

/* * Initialize unrevealed alphabetic positions with underscore.
 * Non-alpha characters are revealed immediately.
 */
guessedWord[i] = '_';

Folder Structure
Recommended Professional Layout
Plaintext

HangmanGame/
├── src/
│   ├── main.c                # Entry point
│   ├── hangman_logic.c       # Game rules & state
│   ├── hangman_ui.c          # Raylib rendering functions
│   └── hangman_types.h       # Shared structs and defines
├── assets/
│   └── words.txt             # Word database
├── docs/
│   └── REFACTORING_GUIDE.md  # Documentation
└── Makefile                  # Build configuration

Modular Design Principles
The Standard Game Loop

To separate concerns, the main loop should be kept clean:
C

while (!WindowShouldClose()) {
    Input_Process();     // Capture keys
    Game_Update();       // Logical checks (win/loss/guess)
    Renderer_Draw();     // Visual output
}

Error Handling & Robustness
Safe File Loading

Always check if the word file exists before attempting to read:
C

FILE *file = fopen(filename, "r");
if (!file) {
    TraceLog(LOG_ERROR, "Failed to load word list. Using defaults.");
    // fallback logic
}

Refactoring Roadmap

    Phase 1 (Cleanup): Rename variables, remove magic numbers using #define.

    Phase 2 (Modularization): Move Raylib drawing code into hangman_ui.c.

    Phase 3 (Robustness): Add bounds checking for array indices and string lengths.

    Phase 4 (Polishing): Finalize documentation and add "Future Improvements" hooks.

Future Improvements

    Gameplay: Multiple difficulty levels, timer mode, and sound effects.

    Technical: High-score saving to a local file, responsive UI for different window sizes.

    DevOps: Integration of unit tests for the word-picking logic
