🪓 Hangman Game — Code Refactoring & Software Engineering Standards Guide
Course: Advanced Programming Lab
Project: Hangman Game (C Language with Raylib)
Purpose: Improve code maintainability, readability, modularity, and scalability
Date: February 2026

📑 Table of Contents
Executive Summary
Naming Conventions
Coding Style Guidelines
Folder Structure
Modular Design Principles
Error Handling & Robustness
Testing Strategy
Refactoring Roadmap
Future Improvements
Executive Summary
Current Project Overview
The Hangman Game is a graphical word-guessing game implemented in C using Raylib.

✅ Strengths
Functional word loading from file
On-screen keyboard with physical keyboard input support
Progressive hangman figure drawing
Random letter hints
Win/lose detection with restart/quit options
⚠️ Areas for Improvement
Single-file implementation
Inconsistent or abbreviated variable names
Mixed concerns (logic + UI + input tightly coupled)
Limited inline documentation
Repeated or duplicated code blocks
Refactoring Philosophy
"Refactor incrementally without breaking gameplay functionality."

🎯 Goals
✅ Cleaner and more modular structure
✅ Easier debugging and extension
✅ Improved readability
✅ Adoption of professional coding standards
Naming Conventions
General Principles
Use descriptive names
Avoid cryptic abbreviations
Maintain consistent casing
Prefer domain-specific terminology
Variable Naming Refactoring
Before

After

int tries;

int failedAttempts;

char t[MAX_WORDS];

char topic[MAX_WORD_LENGTH];

char w[MAX_LEN];

char secretWord[MAX_WORD_LENGTH];

bool p, vl;

bool isPressed; bool isVisible;

Benefits:

Self-documenting variables
Easier debugging
Improved readability
Function Naming Refactoring
Before

After

void DrawHangman(int tries);

void DrawHangmanFigure(int failedAttempts);

char HandleKeyboardButtons(...);

char HandleKeyboardInput(...);

int LoadWords(...);

int LoadWordList(...);

Why This Matters:

Verb-based naming clarifies purpose
Supports modular development
Enhances maintainability
Constants Naming Refactoring
Before

After

#define MAX_WORDS 500

#define MAX_WORDS 500

#define MAX_LEN 128

#define MAX_WORD_LENGTH 128

—

#define KEYBOARD_KEY_WIDTH 48

Improvement:

Eliminates magic numbers
Makes configuration easier
Improves code clarity
Structure Naming Refactoring
Before

After

typedef struct { Rectangle r; char l; bool p; bool vl; } KeyButton;

typedef struct { Rectangle rectangle; char letter; bool isPressed; bool isVisible; } KeyboardKey;

Advantages:

Clear abstraction
Better data organization
Improved maintainability
Coding Style Guidelines
Indentation
Use 4 spaces
Avoid mixing tabs and spaces
c

Copy code
if (!revealedMask[position]) {
    guessedWord[position] = tolower(secretWord[position]);
}
Line Length
Recommended maximum: ~100 characters
Break long expressions logically
Comment Quality Improvement
Before

After

guessed[i] = '_'; // guess

/* Initialize unrevealed alphabetic positions with underscore. Non-alphabetic characters (spaces or punctuation) are revealed immediately. */ guessedWord[i] = '_';

Principle: Comments should explain why, not just what.

Folder Structure
❌ Before Refactoring

Copy code
hangman/
└── main.c
Problems:

No separation of concerns
Hard to scale
Difficult to maintain
✅ Recommended Structure (After Refactoring)

Copy code
HangmanGame/
├── src/
│   ├── hangman_main.c
│   ├── hangman_types.h
│   ├── hangman_game_logic.c
│   └── hangman_ui.c
├── words.txt
├── HangmanGame.cbp
└── REFACTORING_DOCUMENTATION.md
Benefits:

Clear separation of responsibilities
Easier maintenance
Professional project layout
Modular Design Principles
❌ Before Modularization
c

Copy code
// All logic inside main()
Problems:

Mixed responsibilities
Difficult debugging
Hard to extend features
✅ After Modularization
c

Copy code
void Input_Process();
bool ProcessGuess(...);
void CheckGameOver(...);
void DrawGuessedWord(...);
Standard Game Loop Pattern
c

Copy code
while (!WindowShouldClose()) {
    Input_Process();
    Game_Update();
    Renderer_Draw();
}
Advantages:

Clear responsibility separation
Improved testability
Easier scalability
Error Handling & Robustness
Safe File Loading
c

Copy code
FILE *file = fopen(filename, "r");
if (!file) {
    // Fallback to default words
}
Bounds Checking
c

Copy code
if (letterIndex >= 0 && letterIndex < 26 && !guessedLetters[letterIndex]) {
    // Valid letter
}
Assertions (Development-Time)
c

Copy code
assert(secretWord != NULL);
Used for validating assumptions during debugging.

Testing Strategy
Functional Tests
Word loading accuracy
Guess processing correctness
Win/lose detection
Boundary Tests
Empty words
Maximum word length
All letters guessed
Rapid repeated input
Regression Testing
Re-run the game after each refactoring stage to ensure no gameplay breakage.

Refactoring Roadmap
Phase

Focus Area

Phase 1

Cleanup — Fix naming conventions, replace magic numbers, improve documentation

Phase 2

Modularization — Separate types, logic, UI, and main, extract reusable functions, reduce global variables

Phase 3

Robustness — Improve error handling, add validation checks, refine documentation clarity

Phase 4

Extension Ready — Prepare architecture for future features

Future Improvements
🎮 Gameplay Features
Multiple rounds / levels
Timer mode
Sound effects
Custom themes and word packs
🔧 Technical Enhancements
High-score persistence
Improved UI layout
Multiplayer mode
Mobile-friendly UI
🛠️ Software Engineering Improvements
Unit testing framework
Version control best practices
Continuous integration
Automatic formatting (clang-format)
