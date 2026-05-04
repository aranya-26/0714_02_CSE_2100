
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

- Interactive Hangman Game with beautiful UI
- On-screen virtual keyboard + Physical keyboard support
- Random word selection from multiple categories
- Realistic hangman figure with progressive drawing
- Restart and Quit functionality
- Clean and maintainable code structure

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
| **View**       | `UIRenderer`, `KeyboardManager`   | All drawing and user interface |
| **Controller** | `HangmanController`               | Input handling, game flow, coordination between Model & View |

---

## ✅ Changes Made (MVC Refactoring)

### Major Changes:
1. **Created new Controller layer**
   - `HangmanController.h` & `HangmanController.cpp` (New)
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
Hangman-Game-MVC/
- ├── main.cpp
- ├── HangmanController.h
- ├── HangmanController.cpp
- ├── GameState.h
- ├── GameState.cpp
- ├── UIRenderer.h
- ├── UIRenderer.cpp
- ├── KeyboardManager.h
- ├── KeyboardManager.cpp
- ├── WordLoader.h
- ├── WordLoader.cpp
- ├── hangman_types.h
- ├── words.txt
- ├── sounds/ (folder)
- └── README.md
---


---

## 🛠️ Technologies Used

- **Language:** C++
- **Graphics Library:** Raylib
- **IDE:** Code::Blocks
- **Architecture:** MVC Pattern

---

## 🎮 How to Run

1. Open the project in Code::Blocks
2. Make sure `raylib` is properly linked
3. Place `words.txt` in the correct directory
4. Build and Run

---
## 🔄 MVC Refactoring Process

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

**Result:** Successfully transformed the project into a well-structured MVC architecture while maintaining identical gameplay behavior.
## 📌 Learning Outcome

Through this assignment, I have successfully:
- Understood and implemented **MVC Architecture**
- Learned how to separate concerns in game development
- Improved code organization and maintainability
- Applied Object-Oriented Programming principles effectively

---

**Submitted as part of Assignment 3**  
**Thank You!**

---

