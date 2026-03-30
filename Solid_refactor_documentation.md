# 0714_02_CSE_2100

Course Code: 0714 02 CSE 2100 || 
Course Title: Advanced Programming Laboratory ||
Student Id: 240226 && 240231
---
---
# Hangman Game - SOLID Refactoring

**Assignment 2: Refactoring C Projects into SOLID OOD Models**   
**Project: Hangman Game**

**Lecture Reference: Object Oriented Design**
**Lecturer: Professor Dr Kazi Masudul Alam**


---

## 1. Project Overview

This is a fully functional **Hangman Game** built using **Raylib** library. The game allows players to guess a hidden word letter by letter with a visual hangman figure, on-screen keyboard, and mouse/keyboard support.

**Original Code:** Pure procedural C style (monolithic and hard to maintain).  
**Refactored Code:** Modern C++ with proper Object-Oriented Design following **SOLID Principles**.

---

## 2. Refactoring Goals

- Convert entire procedural C codebase into clean, maintainable **C++**.
- Apply all **five SOLID principles** effectively.
- Improve code modularity, readability, and extensibility.
- Keep **100% original gameplay and user experience** unchanged.
- Prepare the project for future enhancements (new word sources, different themes, etc.).

---
## 3. Why C++ Instead of Java or Other Languages?

The decision to refactor the project into **C++** (instead of Java, Python, or other languages) was made for the following important reasons:

- **Native Raylib Compatibility**: Raylib is a C/C++ library. Using C++ allows direct and seamless integration with Raylib without any bindings, wrappers, or performance overhead.

- **Performance Critical for Games**: Games require high performance with hundreds of updates per frame. C++ provides low-level control over memory management and hardware, resulting in faster execution compared to Java (which has Garbage Collection overhead).

- **Industry Standard in Game Development**: C++ is the most widely used language in professional game development (AAA games, engines like Unreal). Refactoring to C++ gave valuable experience relevant to the gaming industry.

- **Smooth Transition from Original C Code**: Since the original project was in C, moving to C++ was a natural evolution. It allowed us to keep most of the existing logic while introducing classes, RAII, and modern C++ features with minimal disruption.

- **Better Learning Opportunity**: C++ helped deepen understanding of memory management, encapsulation, and object-oriented design — skills that are harder to practice properly in languages like Java that hide many low-level details.

Java or other high-level languages would have introduced unnecessary complexity (bindings for Raylib) and reduced performance, which goes against the spirit of a lightweight game library like Raylib.

---
## 4. UML Class Diagram

```

class WordLoader {
  + {static} LoadWords(filename: string): vector<WordEntry>
}

class GameState {
  - secretWord: string
  - guessedWord: string
  - topic: string
  - revealedMask: array<bool>
  - guessedLetters: array<bool>
  - failedAttempts: int
  - alphaPositionsTotal: int
  - isGameOver: bool
  - isWin: bool
  ..
  + Initialize(selectedWord: WordEntry)
  + ProcessGuess(letter: char)
  + CheckGameOver()
  + GetSecretWord(): string
  + GetGuessedWord(): string
  + GetTopic(): string
  + GetFailedAttempts(): int
  + IsGameOver(): bool
  + IsWin(): bool
}

class KeyboardManager {
  - keys: vector<KeyboardKey>
  ..
  + Initialize()
  + HandleInput(mousePos: Vector2, clicked: bool): char
  + Draw(onlyDraw: bool)
  + Reset()
}

class UIRenderer {
  + {static} DrawHangmanFigure(failedAttempts: int)
  + {static} DrawGuessedWord(guessedWord: string, startX: int, py: int)
  + {static} DrawGameUI(state: GameState, keyboard: KeyboardManager)
  + {static} DrawGameOverScreen(state: GameState)
}

class HangmanGame {
  - wordList: vector<WordEntry>
  - gameState: GameState
  - keyboardManager: KeyboardManager
  ..
  + HangmanGame()
  + Run()
  + Restart()
}

' Relationships
HangmanGame "1" *--> "1" GameState
HangmanGame "1" *--> "1" KeyboardManager
HangmanGame ..> WordLoader : <<uses>>
HangmanGame ..> UIRenderer : <<uses>>
UIRenderer ..> GameState : <<uses>>
UIRenderer ..> KeyboardManager : <<uses>>
GameState ..> WordEntry : <<uses>>
KeyboardManager ..> KeyboardKey : <<uses>>

note right of HangmanGame
  **Main Orchestrator**
  Coordinates all other components

```

## 5. What I Successfully Achieved

- Complete migration from C to C++.
- Successfully applied **SRP, OCP, LSP, ISP, and DIP**.
- Broke down the project from 4 large files into **12 well-organized, focused files**.
- Encapsulated game state and separated concerns (logic, UI, input, data loading).
- Maintained full functionality: word loading, guessing, win/lose conditions, restart, keyboard & mouse input.
- Created clean, professional documentation.

---

## 6. Key Changes from Original Code

| Feature                    | Original (Procedural C)               | Refactored (C++ + SOLID)                     | Improvement |
|---------------------------|---------------------------------------|---------------------------------------------|-----------|
| Code Style                | Global variables & loose functions    | Classes with proper encapsulation           | Maintainability |
| File Organization         | 4 mixed files                         | 12 focused files                            | Clarity |
| Word Loading              | `LoadWordList()` function             | `WordLoader` class                          | SRP + OCP |
| Game State Management     | Scattered variables                   | `GameState` class                           | SRP + DIP |
| UI Rendering              | Mixed with logic                      | Dedicated `UIRenderer` class                | SRP |
| Input Handling            | Inside main loop                      | `KeyboardManager` class                     | SRP |
| Main Controller           | Everything in `main()`                | `HangmanGame` orchestrator class            | OCP + DIP |

---

## 7. Core Classes & Design

- **`WordLoader`** – Loads words from `words.txt`
- **`GameState`** – Manages secret word, guessed word, attempts, win/lose status
- **`KeyboardManager`** – Handles on-screen keyboard and input
- **`UIRenderer`** – Responsible for all drawing (hangman, guessed word, UI)
- **`HangmanGame`** – Main game orchestrator

Each class has a **single, clear responsibility**.

---

## 8. SOLID Principles Implementation

- **SRP (Single Responsibility)**: Each class performs only one job.
- **OCP (Open/Closed)**: New features (e.g., database word loader, new UI) can be added without modifying existing classes.
- **LSP (Liskov Substitution)**: Classes are designed to support future inheritance safely.
- **ISP (Interface Segregation)**: Small, focused classes instead of large interfaces.
- **DIP (Dependency Inversion)**: High-level modules depend on abstractions, not concrete implementations.

---

## 9. Final Project Structure
- Hangman_Solid_Refactor/
- ├── hangman_types.h
- ├── WordLoader.h
- ├── WordLoader.cpp
- ├── GameState.h
- ├── GameState.cpp
- ├── KeyboardManager.h
- ├── KeyboardManager.cpp
- ├── UIRenderer.h
- ├── UIRenderer.cpp
- ├── HangmanGame.h
- ├── HangmanGame.cpp
- ├── main.cpp
- ├── words.txt
- └── README.md
---

## 10. What I Learned

- Practical application of SOLID principles in a real game project.
- Importance of separating concerns (data, logic, and presentation).
- How modern C++ features improve code quality over procedural C.
- Incremental refactoring technique with proper testing.
- Professional software design and documentation practices.

---

## 11. How to Run

1. Open the project in **Code::Blocks** (or any C++ IDE with Raylib support).
2. Make sure **Raylib** is properly configured.
3. Build and Run the project.
4. Ensure `words.txt` is in the same directory as the executable.

---
## 12. AI Prompt Set for SOLID Refactoring - Hangman Game
I collaborated with Grok (xAI) using the following structured prompts to guide the refactoring:
#### Prompt 1 - Migration Inventory
"Analyze the entire Hangman codebase and list all procedural C-style code. For each file, identify SOLID violations and suggest C++ class replacements. Provide risk level (Low/Medium/High) and a safe refactoring order starting with lowest risk files."
#### Prompt 2 - Baseline Lock
"Create a complete baseline before refactoring. Include compile test, word loading test, full game play (win & lose), restart, and keyboard input test. Record expected behavior to verify nothing breaks later."
#### Prompt 3 - Core Abstraction Scaffold
"Introduce core classes: WordLoader, GameState, KeyboardManager, UIRenderer, and HangmanGame. Keep adapters so old code still works during transition with zero behavior change."
#### Prompt 4 - Encapsulation & SRP Decomposition
"Move game state into GameState class and split large files into focused modules. Each class should have only one clear responsibility. Keep exact same behavior."
#### Prompt 5 - OCP & DIP Enforcement
"Refactor so that HangmanGame depends only on abstractions (not concrete functions). Remove direct dependency on LoadWordList to make future word sources easy to add."
#### Prompt 6 - UI & Gradual Cleanup
"Move all drawing and input logic into UIRenderer and KeyboardManager. Remove global variables and unnecessary includes. Keep changes small and test after every step."
#### Prompt 7 - Final SOLID Audit & Documentation
"Perform final SOLID audit on the complete code. For each principle, explain how it was applied. Create professional documentation and README.md for GitHub."

---
## 13. Conclusion

This project demonstrates a successful transformation from a procedural C codebase to a clean, SOLID-compliant C++ application. The refactored code is now highly maintainable, extensible, and follows industry best practices while preserving all original features.

**Branch:** `solid-refactor`

---

