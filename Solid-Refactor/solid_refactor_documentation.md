# Hangman Game - SOLID Principles Refactoring

**Assignment 2 | Refactoring C Projects into SOLID OOD Models**  
**Project: Hangman Game**

**Lecture Reference: Program and Programming Style**

### Project Overview
This is a **Hangman Game** developed in **pure C** using the **Raylib** library. The main objective of this assignment was to refactor the original procedural-style code by applying **SOLID Principles** to improve code structure, maintainability, and extensibility.

---

### 🎯 Refactoring Goal

The goal was to transform the original procedural Hangman game into a more structured Object-Oriented Design (OOD) approach **within the constraints of the C language**, using structs and function pointers to simulate OOP concepts.

**What I Successfully Achieved:**
- Applied **three major SOLID principles**: SRP, OCP, and DIP
- Improved code modularity and separation of concerns
- Introduced abstraction for the word loading system
- Made the codebase cleaner, more organized, and easier to maintain

**Limitations:**
- Could not fully implement **LSP (Liskov Substitution Principle)** and **ISP (Interface Segregation Principle)**.
- Reason: Applying all 5 SOLID principles 100% perfectly in a medium-sized C project makes the code significantly larger, more complex, and over-engineered due to heavy use of function pointers.

---

### 🔄 Key Changes from Original Code

| Aspect                    | Original Version                          | Refactored Version                          |
|---------------------------|-------------------------------------------|---------------------------------------------|
| Number of Files           | 4 files                                   | 6 files                                     |
| Code Structure            | Mixed logic in few large files            | Clear separation of responsibilities        |
| Word Loading              | Direct `LoadWordList()` function          | Abstract `WordProvider` interface           |
| Game State Management     | Multiple scattered variables              | Single `Game` struct                        |
| Main Function             | Long and complex                          | Much cleaner and shorter                    |
| Extensibility             | Hard to add new word sources              | Easy to extend with new providers           |

---
### Core Class and Interface Design

Since the project is implemented in **pure C**, traditional C++ classes and interfaces are not directly possible. Instead, we simulate Object-Oriented Design using **structs and function pointers**.

#### Key Data Structures (Concrete)

1. **Game**  
   - Central structure that holds the complete game state (secret word, guessed word, revealed mask, attempts, status, etc.).
   - Replaces previously scattered global variables.

2. **WordProvider**  
   - Concrete implementation: `FileWordProvider`  
   - Responsible for loading words from file and selecting a random word.

3. **KeyboardKey**  
   - Represents individual on-screen keyboard keys (existing structure, lightly used).

#### Key Interfaces / Abstractions

1. **WordProvider** (Primary Interface)
   - **Purpose**: Abstracts word loading and random word selection.
   - **Enforces**: OCP and DIP.
   - **Function Pointers**:
     - `loadWords()` – Load words from source
     - `getRandomWord()` – Select random word from loaded list

2. **GameStateManager** (Conceptual)
   - **Purpose**: Manages game initialization, guess processing, and win/lose checking.
   - Implemented through functions that operate on the `Game` struct (`InitializeGame()`, `ProcessGuess()`, `CheckGameOver()`).

3. **Renderer** (Partial)
   - **Purpose**: Handles all drawing operations (hangman figure, guessed word grid, keyboard UI).
   - Currently implemented as separate functions. Can be further abstracted if needed.

4. **InputHandler** (Partial)
   - **Purpose**: Manages keyboard and mouse input.
   - Currently uses `HandleKeyboardInput()` function.

---

### 🛠 SOLID Implementation Plan

#### 1. **SRP (Single Responsibility Principle)**
- Created `game_state.h` to keep all game-related data in one `Game` struct.
- Moved all game logic into `game_logic.c` (initialization, processing guesses, checking win/lose conditions).
- Separated game logic from UI rendering and data loading.

#### 2. **OCP (Open-Closed Principle) & DIP (Dependency Inversion Principle)**
- Introduced `WordProvider` abstraction using function pointers.
- High-level modules (`main.c` and `game_logic.c`) now depend on the abstraction rather than concrete implementations.
- Created `file_word_provider.c` as the concrete implementation for loading words from a file.
- This allows adding new word sources (e.g., database or API) in the future without modifying existing code.

#### 3. **LSP & ISP**
- Partially considered but not fully implemented to keep the code simple and understandable.

---

### 📌 Important Note

> It is technically possible to apply all 5 SOLID principles 100% perfectly in C. However, in a medium-sized game like Hangman, doing so makes the code much larger, overly complex, and over-engineered.  
> For academic assignments, properly implementing **SRP + OCP + DIP** is usually sufficient and more practical. Full application of LSP and ISP significantly increases the number of function pointers and makes the code harder to read and maintain.

---

### 💡 What I Learned

- How to simulate Object-Oriented Design patterns in pure C using **structs and function pointers**.
- The importance of abstraction and dependency inversion for writing maintainable code.
- How to find the right balance between clean design and practicality.
- Real-world limitations of applying full OOP principles in the C language.
- Better modular programming and code organization techniques.

---

### AI Prompt Set for SOLID Refactoring - Hangman Game
Project: Hangman Game (Pure C + Raylib)
Goal: Refactor the existing procedural code by applying SOLID principles while keeping it in pure C.

#### Prompt 1 - Migration Inventory
"Analyze the entire Hangman codebase and list all the places where we are still using old procedural C-style code. For each file, clearly mention what is violating SOLID principles and suggest the C-style replacement using structs and function pointers. Also mention the risk level (Low / Medium / High) for each change. Finally, give us a safe order to start refactoring, beginning with the lowest risk files first."
#### Prompt 2 - Baseline Lock
"Create a complete baseline before we start refactoring. Include compile test, word loading test, full game play test (win condition, lose condition, restart), and keyboard input test. Record the expected behavior and output. This baseline will be used to verify that nothing breaks after each refactoring step."
#### Prompt 3 - Interface Scaffold
"Introduce the core abstraction WordProvider (using struct + function pointers) for loading and selecting words. Also create Game struct to hold all game state. Keep adapters so the old code can still work during the transition. Make sure there is zero behavior change at this stage."
#### Prompt 4 - Encapsulation Pass
"Refactor the game state so that all data is inside the Game struct. Gradually replace direct variable access with proper functions. After each batch, make sure the code still compiles and runs correctly."
#### Prompt 5 - SRP Decomposition
"Identify the files that are doing too many things. Split the logic into focused modules: game initialization & state management, guess processing, win/lose checking, and UI rendering. Each module should have only one clear responsibility. Keep the exact same behavior."
#### Prompt 6 - OCP & DIP Enforcement
"Refactor the code so that main.c and game logic depend only on the WordProvider abstraction instead of concrete file reading functions. Remove direct dependency on LoadWordList. This should make it easy to add new word sources later without changing existing code."
#### Prompt 7 - Gradual Cleanup
"Clean up the remaining procedural code step by step. Move UI drawing functions into a separate module if possible. Remove global variables and unnecessary includes. Keep changes small and test after every step."
#### Prompt 8 - Regression Gate
"After every refactoring batch, run these checks:

Compile successfully
- Load words correctly from file
- Complete game play (win and lose both)
- Restart functionality works
- Keyboard and mouse input works
- Compare with the baseline and clearly show PASS or FAIL. If anything fails, point to the exact change that caused it."

#### Prompt 9 - Final SOLID Audit
"Perform a final SOLID audit on the entire refactored code. For each SOLID principle (SRP, OCP, LSP, ISP, DIP), state how well it has been applied. Highlight any remaining violations and suggest practical improvements if needed."
#### Prompt 10 - Documentation & Summary
"Create a clean, professional summary of all the changes made, SOLID principles applied, what was improved, and what limitations we kept (especially why we didn’t apply LSP and ISP 100%). Also prepare a ready-to-use README.md section for GitHub."

---

### 🗂 Final Project Structure

- solid-refactor/
- ├── hangman_types.h
- ├── word_provider.h
- ├── file_word_provider.c
- ├── game_state.h
- ├── game_logic.c
- ├── main.c
- └── words.txt


---

### Conclusion

This assignment helped me understand that writing **clean and professional code** is not about blindly applying all design principles, but about choosing the **right principles** based on project size, language constraints, and practical needs.

The refactored version is significantly more modular and extensible than the original procedural code while remaining understandable and suitable for academic evaluation.

---

**Submitted by:** Aranya Bachar && Arif Awsaf  
**Course:** Advanced Programming Laboratory

---



