# 🎮 Hangman Game — Code Refactoring Guide

**Project:** Hangman Game (C Language with Raylib)  
**Date:** February 2026

---

## 📑 Table of Contents
1. [Executive Summary](#executive-summary)
2. [Naming Conventions](#naming-conventions)
3. [Modular Design Principles](#modular-design-principles)

---

## Executive Summary

### Current Project Overview
The Hangman Game is a graphical word-guessing game built with **Raylib**.

**Areas for Improvement:**
* **Monolithic Structure:** All logic in one file.
* **Naming:** Short or unclear variables.

---

## Naming Conventions

### Variable Refactoring
| Before | After |
| :--- | :--- |
| `int tries;` | `int failedAttempts;` |
| `bool vl;` | `bool isVisible;` |

---

## Modular Design Principles

### The Standard Game Loop
```c
while (!WindowShouldClose()) {
    Input_Process();     // Capture keys
    Game_Update();       // Logical checks
    Renderer_Draw();     // Visual output
}
