
# 0714_02_CSE_2100

Course Code: 0714 02 CSE 2100 || 
Course Title: Advanced Programming Laboratory ||
Student Id: 240226 && 240231

# Hangman Game - MVC Pattern Implementation

## 📋 Assignment Information
- **Assignment 3**
- **Course:** Advanced Programming Laboratory
- **Submitted By:** Aranya Bachar && Arif Awsaf
- **Student Id:** 240226 && 240231
- **Date:** 04 May, 2026

---

## 🚀 Project Overview

This is a **Hangman Game** developed using **Raylib** library in C++. The project demonstrates the implementation of **MVC (Model-View-Controller)** architectural pattern.

---

### 🔨 Refactoring Goals

- Successfully implement **MVC (Model-View-Controller)** architectural pattern
- Separate concerns between data/logic, presentation, and control flow
- Improve code readability and maintainability
- Follow SOLID principles (especially SRP)
- Make the codebase more scalable and easier to extend
- Maintain 100% identical gameplay and user experience
- Prepare the project for future enhancements

## 📌 Features

- Beautiful raylib-based UI with animations
- Physical keyboard + on-screen virtual keyboard
- Sound effects (correct, wrong, win, lose, background)
- Progressive hangman drawing
- Random word selection from large dictionary
- Restart and Quit functionality
- Clean, professional code structure

---

## 🏗️ Architecture: MVC Pattern

### Before MVC (Old Structure)
- All game logic, UI rendering, and input handling were mixed together.
- `HangmanGame` class handled everything (Monolithic design).
- Hard to maintain and extend.

### After MVC Implementation (Current Structure)

| Layer          | Components                        | Responsibility |
|----------------|-----------------------------------|--------------|
| **Model**      | `GameState`, `WordLoader`         | Game data and core logic |
| **View**       | `UIRenderer`, `KeyboardManager`, `HangmanAnimator`   | All drawing and user interface |
| **Controller** | `HangmanController`               | Input handling, game flow, coordination between Model & View |

---

## ✅ Changes Made (MVC Refactoring)

### Major Changes:
1. **Created new Controller layer**
   - `HangmanController.h` & `HangmanController.cpp` `HangmanAnimator.h` & `HangmanAnimator.cpp`(New)
   - Moved game loop, input handling, sound management, and restart logic here.

2. **Separated responsibilities clearly:**
   - `GameState` → Pure Model (only data & game logic)
   - `UIRenderer` → Pure View (only drawing)
   - `HangmanGame` class removed and replaced with `HangmanController`

3. **Improved Code Quality:**
   - Better separation of concerns
   - Easier to read and maintain
   - More professional and scalable structure

4. **Minor Improvements:**
   - Cleaner `KeyboardManager`
   - Better sound handling
   - Updated `main.cpp`

---

## 📁 Project Structure
```
Hangman-Game-MVC/
- │
- ├── assets/
- │   └── sounds/
- │       ├── correct.mp3
- │       ├── lose.mp3
- │       ├── win.mp3
- │       └── wrong.mp3
- │
- ├── include/
- │   ├── GameState.h           # [Model]      Core game state & data definitions
- │   ├── HangmanAnimator.h     # [View]       Hangman figure drawing & animation
- │   ├── HangmanController.h   # [Controller] Input handling & game flow control
- │   ├── KeyboardManager.h     # [Controller] Keyboard input management
- │   ├── UIRenderer.h          # [View]       UI rendering (letters, scoreboard, UI)
- │   ├── WordLoader.h          # [Model]      Word loading from file
- │   └── hangman_types.h       # [Model]      Shared types & enums
- │
├── src/
- │   ├── GameState.cpp
- │   ├── HangmanAnimator.cpp
- │   ├── HangmanController.cpp
- │   ├── KeyboardManager.cpp
- │   ├── UIRenderer.cpp
- │   ├── WordLoader.cpp
- │   └── main.cpp
- │
- ├── words_1000.txt            # Word bank (1000 words)
- ├── Hangman.exe               # Prebuilt Windows executable
- └── Hangman_Executable.zip    # Zipped executable package
```

---


---

## 🛠️ Technologies Used

- **Language:** C++
- **Graphics & Audio:** raylib
- **Architecture:** MVC Pattern
- **IDE:** Code::Blocks
- **Build System:** MinGW

---

---

## 🎮 How to Play (Executable)

1. Go to `Hangman_Executable/` folder
2. Download or extract `Hangman_Final.zip`
3. Run `Hangman.exe`
4. Enjoy the game with sound, keyboard support, and smooth UI

---

## 🛠️ How to Build from Source

1. Open the project in **Code::Blocks**
2. Make sure **raylib** is properly linked
3. Set include and library paths correctly
4. Build in **Release** mode (`Ctrl + F11`)
5. Run the executable

---
## 🔄 AI prompt used

We refactored the entire Hangman Game codebase from a monolithic structure into a clean **MVC (Model-View-Controller)** architecture using the following structured prompts:

### Prompt 1 - Current State Analysis
"Analyze the entire Hangman Game codebase and provide a detailed assessment of its current architecture. Identify all places where logic, UI rendering, input handling, and data management are mixed together. List the main classes/files and their current responsibilities. Highlight why the current structure violates Separation of Concerns."

### Prompt 2 - MVC Architecture Planning
"Design a clean MVC (Model-View-Controller) architecture for the Hangman Game. Define exactly what should go into Model, View, and Controller layers. Propose the final file structure with all .h and .cpp files. Ensure the design follows SOLID principles as much as possible."

### Prompt 3 - Baseline Creation
"Before starting refactoring, create a complete baseline of the current working project. Include compilation test, word loading verification, full gameplay test (win condition and lose condition), keyboard input test and restart functionality. Document the expected behavior for future regression testing."

### Prompt 4 - Core MVC Scaffold
"Introduce the MVC structure by creating the following classes while maintaining 100% identical behavior:  
- Model: GameState and WordLoader  
- View: UIRenderer and KeyboardManager  
- Controller: HangmanController  
Keep the existing main.cpp and other files working during transition."

### Prompt 5 - Model Layer Implementation
"Refactor the data and business logic into the Model layer. Move all game state management, word processing, guessing logic, win/lose conditions into the GameState class. Ensure Model has no UI or input dependencies. Keep exact same external behavior."

### Prompt 6 - View Layer Implementation
"Move all rendering and display logic into the View layer. Refactor UIRenderer and KeyboardManager so they are responsible only for drawing and visual feedback. Remove any business logic from View classes. Ensure View depends only on data provided by Controller/Model."

### Prompt 7 - Controller Layer Implementation
"Create the HangmanController class that acts as the mediator between Model and View. Move game loop, input handling, sound management, button logic, and coordination between Model and View into the Controller. Remove the old HangmanGame class and update main.cpp accordingly."

### Prompt 8 - Final Integration & Cleanup
"Integrate all MVC components. Remove any remaining direct dependencies between layers. Eliminate global variables, unnecessary includes, and duplicate code. Ensure the game runs exactly as before but with clean MVC structure."

---

## 🔄 MVC Refactoring Summary

This project was refactored using systematic steps to convert the previous mixed codebase into a well-structured MVC design while keeping the original gameplay completely unchanged.

**Key Improvements:**
- Model is now independent of UI and input
- View only handles rendering
- Controller manages all coordination and game flow
- Reduced coupling between components

---

## 📝 Learning Outcomes

- Deep understanding of **MVC Architecture**
- Practical application of **Separation of Concerns**
- Improved Object-Oriented Design skills
- Better code organization and documentation practices


---

**Submitted as part of Assignment 3 - Advanced Programming Laboratory**

---

**Thank You!**  
Feel free to explore the code and run the executable.
