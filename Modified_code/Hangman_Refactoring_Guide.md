# 🎮 Hangman Game — Code Refactoring & Software Engineering Standards Guide

**Course:** Advanced Programming Laboratory  
**Project:** Hangman Game (C Language with raylib)  
**Purpose:** Improve code maintainability, readability, modularity, and scalability  

**Lecture Reference:** Program and Programming Style  

---

## 📑 Table of Contents

1. [Executive Summary](#executive-summary)
2. [Naming Conventions](#naming-conventions)
3. [Coding Style Guidelines](#coding-style-guidelines)
4. [Modular Design Principles](#modular-design-principles)
5. [Comments and Documentation Improvement](#comments-and-documentation-improvement)
6. [Error Handling and Robustness](#error-handling-and-robustness)
7. [Refactoring Roadmap](#refactoring-roadmap)
8. [Future Improvements](#future-improvements)

---

## Executive Summary

### Current Project Overview

The Hangman Game is a graphical word-guessing game built with **raylib**, featuring:

**Strengths:**
- Graphical UI with on-screen keyboard
- Mouse and keyboard input support
- Topic-based word loading from file
- Progressive hangman figure drawing
- Initial random letter hints
- Restart / Quit functionality

**Areas for Improvement (Original Code):**
- Cryptic / short variable names (`t`, `w`, `p`, `vl`, `tries`)
- Limited comments and documentation
- Monolithic `main()` function with duplicated logic
- Inconsistent formatting and spacing
- Magic numbers and hard-coded values
- Lack of clear separation between concerns

### Refactoring Philosophy

> "Refactor incrementally without breaking gameplay functionality."

**Goals (aligned with lecture):**
- Achieve simplicity and clarity (elegance)
- Easier debugging and maintenance
- Better scalability for new features
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
char t[MAX_LEN], w[MAX_LEN];
int tries;
bool p, vl;
```
**Issues:**
Abbreviations reduce clarity
Hard to understand intent

#### After Refactoring
```c
char topic[MAX_STRING_LENGTH];
char secretWord[MAX_STRING_LENGTH];
int attempts;
bool pressed;
bool visible;
```
**Benefits:**

Self-documenting variables
Easier debugging

### Function Naming Refactoring
#### Before
```c
void DrawHangman(int tries);
void InitGuessedFromWord(...);
```
#### After
```c
void DrawHangmanFigure(int attempts);
void InitializeGuessedWord(...);
void ResetGame(...);
```
**Why This Matters:**

Verb-based naming clarifies purpose
Supports modular development

### Constants Naming Refactoring
#### Before
```c
#define WINDOW_W 1000
#define MAX_TRIES 6
```
#### After
```c
#define WINDOW_WIDTH 1000
#define MAX_ATTEMPTS 6
```
**Improvement:**
Eliminates magic numbers

### Structure Naming Refactoring

#### Before
```c
typedef struct { char t[...]; char w[...]; } WordEntry;
```
#### After
```c
typedef struct {
    char topic[MAX_STRING_LENGTH];
    char word[MAX_STRING_LENGTH];
} WordEntry;
```
**Advantages:**


Clear abstraction


## Coding Style Guidelines

### Indentation

- **4 spaces** preferred
Avoid mixing tabs and spaces

**Example:**
```c
if (found) {
    correctCount++;
}
```
### Comment Quality Improvement


Principle: Comments should explain why, not just what.
#### Before
```c
// lowercase word copy...
```
### After
```c
/**
 * Initializes guessed word from secret word...
 */
```

## Modular Design Principle: 

❌ Before Modularization
```c
// All logic inside main()
```
**Problems:**

- Mixed responsibilities
- Difficult debugging
- Hard to extend features
---
### After Modularization


```c
void Input_Process();
bool ProcessGuess(...);
void CheckGameOver(...);
void DrawGuessedWord(...);
```
## Standard Game Loop Pattern

```c
while (!WindowShouldClose()) {
    Input_Process();
    Game_Update();
    Renderer_Draw();
}
```
**Advantages:**

- Clear responsibility separation
- Improved testability
- Easier scalability
---

## Folder Structure
### efore Refactoring

```c
hangman/
└── main.c
```
**Problems:**

- No separation of concerns
- Hard to scale
- Difficult to maintain

###  Structure (After Refactoring)

```c
HangmanGame/
├── src/
│   ├── hangman_main.c
│   ├── hangman_types.h
│   ├── hangman_game_logic.c
│   └── hangman_ui.c
├── words.txt
├── HangmanGame.cbp
└── REFACTORING_DOCUMENTATION.md
```
**Benefits:**

- Clear separation of responsibilities
- Easier maintenance
- Professional project layout
---


## Comments and Documentation Improvement

- Added Doxygen-style function headers
- Section comments for logical blocks
- Removed redundant inline comments

**Lecture Alignment:**

"Good code needs fewer comments than bad code"


## Error Handling and Robustness

- Safe string handling (strncpy + \0)
- Letter validation
- File load fallback

Example:
```c
if (!file) {
    // use default words
}
```
## Refactoring Roadmap

### Phase 1 — Cleanup (Done)

- Naming conventions
- Formatting & indentation
- Documentation

### Phase 2 — Modularization (Done)

- Extract functions
- Reduce main()

### Phase 3 — Optimization (Done)

- Remove duplication
- Improve readability

### Phase 4 — Feature Expansion (Planned)

- Difficulty modes
- Audio

---

## Future Improvements
### Gameplay Features

- Difficulty levels
- Sound effects
- High-score tracking

### Technical Enhancements

- Unit testing
- Cross-platform build
- Custom word validation

### Software Engineering Improvements

- .clang-format
- CI pipeline
---

## Prompts & Process Used
This documentation was created through an iterative conversation with Grok (xAI). Key prompts included:

- Sharing original code & requesting refactoring
- Asking for modular file split (types.h, game_logic.c, ui.c, main.c)
- Requesting documentation 
- Fixing copy-paste formatting issues
- Adding lecture reference 
- Including folder structure

The process followed incremental refinement – starting from raw code → modular code → clean documentation.
