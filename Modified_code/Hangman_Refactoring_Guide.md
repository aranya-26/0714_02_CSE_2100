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

The Hangman Game is a graphical word-guessing game built with Raylib in C, featuring:

**Strengths:**
- Word loading from file (topic:word format)
- On-screen keyboard + physical keyboard input
- Progressive hangman figure drawing
- Random initial letter hints
- Win/lose detection with restart/quit

**Areas for Improvement (Original):**
- Single monolithic file
- Inconsistent/short variable names
- Mixed concerns (logic + UI + input)
- Minimal comments
- Repeated code blocks

### Refactoring Philosophy

> "Refactor incrementally without breaking gameplay functionality."

**Goals:**
- Cleaner code structure
- Easier debugging
- Better scalability
- Improved readability
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
void DrawHangman(int tries);
char HandleKeyboardButtons(...);
int LoadWords(...);

After
void DrawHangmanFigure(int failedAttempts);
char HandleKeyboardInput(...);
int LoadWordList(...);
