# 🐍 Hangman Game — Code Refactoring & Software Engineering Standards Guide
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
The Hangman Game project is a graphical word-guessing game implemented in C using Raylib, featuring:
**Strengths:**
- Functional word loading from file
- On-screen keyboard + physical input
- Progressive hangman figure drawing
- Random letter hints
- Win/lose detection with restart/quit
**Areas for Improvement:**
- Single-file implementation
- Inconsistent/short variable names
- Mixed concerns (logic + UI + input)
- Limited comments
- Repeated code blocks
### Refactoring Philosophy
> "Refactor incrementally without breaking gameplay functionality."
**Goals:**
- Cleaner, more modular structure
- Easier debugging & extension
- Better readability
- Professional coding standards
---
## Naming Conventions
### General Principles
- Use descriptive names
- Avoid cryptic abbreviations
- Maintain consistent casing
- Prefer domain-specific terminology
### Variable Naming Refactoring
#### Before Refactoring
```c
int tries;
char t[MAX_WORDS];
char w[MAX_LEN];
bool p, vl;
Issues:

Abbreviations reduce clarity
Hard to understand intent
Inconsistent naming

After Refactoring
Cint failedAttempts;
char topic[MAX_WORD_LENGTH];
char secretWord[MAX_WORD_LENGTH];
bool isPressed;
bool isVisible;
Benefits:

Self-documenting variables
Easier debugging
Improved readability

Function Naming Refactoring
Before
Cvoid DrawHangman(int tries);
char HandleKeyboardButtons(...);
int LoadWords(...);
After
Cvoid DrawHangmanFigure(int failedAttempts);
char HandleKeyboardInput(...);
int LoadWordList(...);
Why This Matters:

Verb-based naming clarifies purpose
Supports modular development
Enhances maintainability

Constants Naming Refactoring
Before
C#define MAX_WORDS 500
#define MAX_LEN 128
After
C#define MAX_WORDS           500
#define MAX_WORD_LENGTH     128
#define KEYBOARD_KEY_WIDTH  48
Improvement:

Eliminates magic numbers
Makes configuration easier

Structure Naming Refactoring
Before
Ctypedef struct {
    Rectangle r;
    char l;
    bool p;
    bool vl;
} KeyButton;
After
Ctypedef struct {
    Rectangle rectangle;
    char letter;
    bool isPressed;
    bool isVisible;
} KeyboardKey;
Advantages:

Clear abstraction
Better data organization


Coding Style Guidelines
Indentation

4 spaces preferred
Avoid mixing tabs and spaces
Example:

Cif (!revealedMask[pos]) {
    guessedWord[pos] = tolower(secretWord[pos]);
}
Line Length

Recommended maximum ≈ 100 characters
Break long expressions logically

Comment Quality Improvement
Before
Cguessed[i] = '_'; // guess
After
C/*
 * Initialize unrevealed alphabetic positions with underscore.
 * Non-alpha characters (spaces/punctuation) are shown immediately.
 */
guessedWord[i] = '_';
Principle:
Comments should explain why, not just what.
Folder Structure
Before Refactoring
texthangman/
└── main.c (all code)
Problems:

No separation
Hard to scale

Recommended Structure (After Refactoring)
textHangmanGame/
├── src/
│   ├── hangman_main.c
│   ├── hangman_types.h
│   ├── hangman_game_logic.c
│   └── hangman_ui.c
├── words.txt
├── HangmanGame.cbp
└── REFACTORING_DOCUMENTATION.md
Benefits:

Separation of concerns
Easier maintenance
Professional project layout


Modular Design Principles
Before Modularization
C// All logic in main(): input + guess + draw + check
Problems:

Mixed responsibilities
Difficult debugging

After Modularization
Cvoid Input_Process();
bool ProcessGuess(...);
void CheckGameOver(...);
void DrawGuessedWord(...);
Standard Game Loop
Cwhile (!WindowShouldClose()) {
    Input_Process();
    Game_Update();
    Renderer_Draw();
}
Advantages:

Clear responsibility separation
Better testability
Easier scaling


Error Handling & Robustness
Safe File Loading
CFILE *file = fopen(filename, "r");
if (!file) {
    // fallback to default words
}
Bounds Checking
Cif (letterIndex >= 0 && letterIndex < 26 && !guessedLetters[letterIndex])
Assertions (Development)
Cassert(secretWord != NULL);
Used for validation during debugging.
Testing Strategy
Functional Tests

Word loading accuracy
Guess processing correctness
Win/lose detection

Boundary Tests

Empty words
Maximum word length
All letters guessed

Regression Testing
Re-run game after each change to ensure no breakage.
Refactoring Roadmap
Phase 1 — Cleanup

Fix naming conventions
Add constants
Improve documentation

Phase 2 — Modularization

Split into files (types, logic, ui, main)
Extract functions

Phase 3 — Polish

Add robust error handling
Refine comments

Phase 4 — Extension Ready

Prepare for future features


Future Improvements
Gameplay Features

Multiple rounds / levels
Timer mode
Sound effects
Themes / custom words

Technical Enhancements

High-score saving
Mobile/responsive UI
Multiplayer mode

Software Engineering Improvements

Unit tests
Version control best practices
Automatic formatting (clang-format)


Final Note
This refactoring guide aims to:
✅ Improve code quality
✅ Enhance maintainability
✅ Support future expansion
✅ Promote professional coding practices
A well-structured Hangman Game project demonstrates not only functional gameplay but also strong software engineering discipline, clean architecture, and scalability for future enhancements.
Prepared following Kernighan & Pike style principles (simplicity, clarity, elegance, consistency) from The Practice of Programming and lecture materials.
