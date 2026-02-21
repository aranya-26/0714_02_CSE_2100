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
