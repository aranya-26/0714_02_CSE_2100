
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define MAX_WORDS 500
#define MAX_LEN 128
typedef struct WordEntry{
    char t[MAX_WORDS];
    char w[MAX_LEN];
} WordEntry;
typedef struct {
    Rectangle r;
    char l;
    bool p;
    bool vl;
} KeyButton;
static const int WINDOW_W=1000;
static const int WINDOW_H=700;
static const int MAX_TRIES=6;
void DrawHangman(int tries) {
DrawRectangleLines(120, 120, 260, 380, Fade(BLACK, 0.6f)); 
DrawLine(200, 500, 420, 500, DARKGRAY); 
DrawLine(250, 500, 250, 160, DARKGRAY);
DrawLine(250, 160, 370, 160, DARKGRAY); 
DrawLine(370, 160, 370, 210, DARKGRAY); 

    if (tries >= 1) {
    DrawCircle(370, 235, 30, BLACK); 
    DrawCircleLines(370, 235, 30, GRAY);
    }
    if (tries >= 2) DrawLine(370, 265, 370, 360, BLACK); 
    if (tries >= 3) DrawLine(370, 290, 330, 330, BLACK); 
    if (tries >= 4) DrawLine(370, 290, 410, 330, BLACK); 
    if (tries >= 5) DrawLine(370, 360, 330, 410, BLACK); 
    if (tries >= 6) DrawLine(370, 360, 410, 410, BLACK); 
    if (tries > 0) DrawRectangle(120, 120, 260, 380, Fade(RAYWHITE, 0.02f));
}

// lowercase word copy and mark non-alpha as revealed
void InitGuessedFromWord(const char *word, char *guessed, bool *revealedMask, int *uniqueLetters) {
int n = strlen(word);
*uniqueLetters = 0;
bool present[26] = {0};
    for (int i = 0; i < n; i++) {
        char c = word[i];
    if (isalpha((unsigned char)c)) {
            guessed[i] = '_';
            revealedMask[i] = false;
            char lc = tolower(c);
            if (!present[lc - 'a']) {
                present[lc - 'a'] = true;
                (*uniqueLetters)++;
            }
        } else {
            // reveal punctuation/spaces
            guessed[i] = c;
            revealedMask[i] = true;
        }
    }
            guessed[n] = '\0';
}

void RandomlyReveal(char *word, char *guessed, bool *revealedMask, int revealCount, int *correctCount) {
int n = strlen(word);
int tries = 0;
while (revealCount > 0 && tries < 1000) {
        int pos = rand() % n;
if (!revealedMask[pos] && isalpha((unsigned char)word[pos])) {
            guessed[pos] = tolower(word[pos]);
            revealedMask[pos] = true;
            (*correctCount)++;
            revealCount--;
        }
             tries++;
    }
}

// Load words from words.txt format Topic:word
int LoadWords(const char *filename, WordEntry *list, int maxWords) {
                FILE *f = fopen(filename, "r");
                if (!f) return 0;
                char buf[300];
                int count = 0;
while (fgets(buf, sizeof(buf), f) && count < maxWords) {
        buf[strcspn(buf, "\r\n")] = 0;
        if (strlen(buf) == 0) continue;
        char *sep = strchr(buf, ':');
        if (sep) {
                *sep = '\0';
                strncpy(list[count].t, buf, MAX_LEN-1);
                list[count].t[MAX_LEN-1] = '\0';
                strncpy(list[count].w, sep+1, MAX_LEN-1);
                list[count].w[MAX_LEN-1] = '\0';
                count++;
        }
    }
    fclose(f);
    return count;
}

int CreateKeyboard(KeyButton *keys) {
    const char *row1 = "ABCDEFGHI";
    const char *row2 = "JKLMNOPQR";
    const char *row3 = "STUVWXYZ";
    int marginX = 40;
    int startY = 420;
    int keyW = 48, keyH = 48, gap = 12;
    int idx = 0;
    int x = marginX;
    for (int i = 0; row1[i]; i++) {
        keys[idx].r = (Rectangle){ (float)x, (float)startY, (float)keyW, (float)keyH };
        keys[idx].l = row1[i];
        keys[idx].p = false;
        keys[idx].vl = true;
        x += keyW + gap;
        idx++;
    }
    x = marginX;
    for (int i = 0; row2[i]; i++) {
                keys[idx].r = (Rectangle){ (float)x, (float)(startY + keyH + gap), (float)keyW, (float)keyH };
                keys[idx].l = row2[i];
                keys[idx].p = false;
                keys[idx].vl = true;
                x += keyW + gap;
                idx++;
    }
    
    x = marginX + 24; 
    for (int i = 0; row3[i]; i++) {
            keys[idx].r = (Rectangle){ (float)x, (float)(startY + 2*(keyH + gap)), (float)keyW, (float)keyH };
            keys[idx].l = row3[i];
            keys[idx].p = false;
            keys[idx].vl = true;
            x += keyW + gap;
            idx++;
    }
    return idx;
}

// Draw keyboard and return letter pressed by mouse (or 0)
char HandleKeyboardButtons(KeyButton *keys, int keyCount, Vector2 mousePoint, bool mouseClicked) {
    char pressed = 0;
    for (int i = 0; i < keyCount; i++) {
    if (!keys[i].vl) continue;
    Color bg = keys[i].p ? Fade(DARKGREEN, 0.9f) : LIGHTGRAY;
    if (CheckCollisionPointRec(mousePoint, keys[i].r)) {
    bg = Fade(SKYBLUE, keys[i].p ? 0.9f : 0.6f);
    if (mouseClicked && !keys[i].p) {
    keys[i].p = true;
    pressed = tolower(keys[i].l);
            }
        }
        DrawRectangleRec(keys[i].r, bg);
        DrawRectangleLinesEx(keys[i].r, 2, Fade(GRAY, 0.7f));
        DrawText(TextFormat("%c", keys[i].l), (int)(keys[i].r.x + 15), (int)(keys[i].r.y + 8), 22, BLACK);
    }
    return pressed;
}

int main() {
    InitWindow(WINDOW_W, WINDOW_H, "Hangman");
    SetTargetFPS(60);
    srand((unsigned)time(NULL));

    // Load word list
    WordEntry words[MAX_WORDS];
    int wordCount = LoadWords("words.txt", words, MAX_WORDS);
    if (wordCount == 0) {
        strcpy(words[0].t, "Fruits"); strcpy(words[0].w, "banana");
        strcpy(words[1].t, "Country"); strcpy(words[1].w, "bangladesh");
        wordCount = 2;
    }

    KeyButton keys[26];
    int keyCount = CreateKeyboard(keys);

   
    int idx = rand() % wordCount;
    char topic[MAX_LEN], word[MAX_LEN];
    strncpy(topic, words[idx].t, MAX_LEN-1); topic[MAX_LEN-1] = '\0';
    strncpy(word, words[idx].w, MAX_LEN-1); word[MAX_LEN-1] = '\0';
    for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);

    int len = strlen(word);
    char guessed[MAX_LEN];
    bool revealedMask[MAX_LEN];
    int uniqueLetters = 0;
    InitGuessedFromWord(word, guessed, revealedMask, &uniqueLetters);
    int revealCount = 0;
    if (len == 5) revealCount = 2;
    else if (len == 6) revealCount = 2;
    else if (len == 7) revealCount = 3;
    else if (len == 8) revealCount = 3;
    else if (len == 9) revealCount = 3;
    else if (len >= 10) revealCount = 3;
    else revealCount = 1;

    int correctCount = 0;
    RandomlyReveal(word, guessed, revealedMask, revealCount, &correctCount);

    int tries = 0;
    bool gameOver = false;
    bool win = false;

    bool guessedAlpha[26] = { false };

    int alphaPositionsTotal = 0;
    for (int i = 0; i < len; i++) if (isalpha((unsigned char)word[i])) alphaPositionsTotal++;

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        char inputLetter = 0;
        for (int k = 0; k < 26; k++) {
            if (IsKeyPressed(KEY_A + k)) {
                inputLetter = 'a' + k;
                break;
            }
        }

        char mouseLetter = HandleKeyboardButtons(keys, keyCount, mousePoint, mouseClicked);
        char letter = 0;
        if (mouseLetter) letter = mouseLetter;
        else if (inputLetter) letter = inputLetter;

        if (!gameOver && letter) {
            int li = letter - 'a';
            if (li >= 0 && li < 26 && !guessedAlpha[li]) {
                guessedAlpha[li] = true;
                for (int i = 0; i < keyCount; i++) {
                    if (tolower(keys[i].l) == letter) keys[i].p = true;
                }
                bool found = false;
                for (int i = 0; i < len; i++) {
                    if (tolower(word[i]) == letter && !revealedMask[i]) {
                        guessed[i] = letter;
                        revealedMask[i] = true;
                        correctCount++;
                        found = true;
                    }
                }
                if (!found) {
                    tries++;
                }
            }
        }

       
        int revealedAlphaCount = 0;
        for (int i = 0; i < len; i++) if (isalpha((unsigned char)word[i]) && revealedMask[i]) revealedAlphaCount++;
        if (!gameOver) {
            if (revealedAlphaCount == alphaPositionsTotal) {
                gameOver = true; win = true;
            } else if (tries >= MAX_TRIES) {
                gameOver = true; win = false;
            }
        }

        Rectangle restartBtn = (Rectangle){ 720, 40, 220, 42 };
        bool hoverRestart = CheckCollisionPointRec(mousePoint, restartBtn);
        if (hoverRestart) {
            if (mouseClicked) {
                idx = rand() % wordCount;
                strncpy(topic, words[idx].t, MAX_LEN-1); topic[MAX_LEN-1] = '\0';
                strncpy(word, words[idx].w, MAX_LEN-1); word[MAX_LEN-1] = '\0';
                for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
                len = strlen(word);
                InitGuessedFromWord(word, guessed, revealedMask, &uniqueLetters);
                if (len == 5) revealCount = 2;
                else if (len == 6) revealCount = 2;
                else if (len == 7) revealCount = 3;
                else if (len == 8) revealCount = 3;
                else if (len == 9) revealCount = 3;
                else if (len >= 10) revealCount = 3;
                else revealCount = 1;
                correctCount = 0;
                RandomlyReveal(word, guessed, revealedMask, revealCount, &correctCount);
                tries = 0;
                gameOver = false; win = false;
                memset(guessedAlpha, 0, sizeof(guessedAlpha));
                for (int i = 0; i < keyCount; i++) keys[i].p = false;
                alphaPositionsTotal = 0;
                for (int i = 0; i < len; i++) if (isalpha((unsigned char)word[i])) alphaPositionsTotal++;
            }
        }
        Rectangle quitBtn = (Rectangle){ 720, 100, 220, 42 };
        bool hoverQuit = CheckCollisionPointRec(mousePoint, quitBtn);
        if (hoverQuit && mouseClicked) break;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, WINDOW_W, 100, Fade(LIGHTGRAY, 0.08f));
        DrawText("HANGMAN", 350, 14, 52, DARKBLUE);
        DrawText(TextFormat("Topic: %s", topic), 30, 52, 20, DARKGRAY);

        DrawRectangle(700, 20, 280, 160, Fade(RAYWHITE, 0.6f));
        DrawText("Controls", 760, 10, 22, BLUE);

        DrawRectangleRec(restartBtn, hoverRestart ? SKYBLUE : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(restartBtn, 2, GRAY);
        DrawText("Restart (Click)", 760, 52, 20, BLACK);

        DrawRectangleRec(quitBtn, hoverQuit ? PINK : Fade(LIGHTGRAY, 0.9f));
        DrawRectangleLinesEx(quitBtn, 2, GRAY);
        DrawText("Quit (Click)", 760, 112, 20, BLACK);

        DrawText(TextFormat("Lives: %d / %d", MAX_TRIES - tries, MAX_TRIES), 740, 180, 22, RED);
        DrawText("Instructions:", 740, 220, 18, DARKGRAY);
        DrawText(" - Type a letter or click on keys", 740, 248, 16, DARKGRAY);
        DrawText(" - Press Restart to play again", 740, 270, 16, DARKGRAY);

        int px = 480;
        int py = 160;
        DrawText("Guess the word:", px-50, py-40, 20, DARKGRAY);
        int spacing = 40;
        int startX = px;
        for (int i = 0; i < len; i++) {
            char ch = guessed[i];
            Rectangle cell = (Rectangle){ (float)(startX + i*spacing), (float)py, 36, 48 };
            DrawRectangleLinesEx(cell, 2, Fade(GRAY, 0.6f));
            if (ch == '_') DrawText("_", (int)(cell.x + 10), (int)(cell.y + 6), 30, DARKGRAY);
            else {
                char s[2] = { ch, 0 };
                DrawText(s, (int)(cell.x + 6), (int)(cell.y + 6), 30, MAROON);
            }
        }

        DrawHangman(tries);

        DrawText("On-screen keyboard", 40, 380, 18, YELLOW);
        HandleKeyboardButtons(keys, keyCount, mousePoint, false); 
        if (gameOver) {
            Rectangle overlay = (Rectangle){ 0, 0, WINDOW_W, WINDOW_H };
            DrawRectangleRec(overlay, Fade(BLACK, 0.45f));
            if (win) {
                DrawText("CONGRATULATIONS! You Win !!", 250, 300, 40, LIME);
                DrawText(TextFormat("Word: %s", word), 320, 360, 28, LIGHTGRAY);
            } else {
                DrawText("GAME OVER!", 340, 300, 40, RED);
                DrawText(TextFormat("The word was: %s", word), 310, 360, 28, LIGHTGRAY);
            }
            DrawText("Click Restart to play again or press ESC to quit", 220, 420, 18, GRAY);
        }

        EndDrawing();

        // quick exit with ESC key
        if (IsKeyPressed(KEY_ESCAPE)) break;
    }

    CloseWindow();
    return 0;
}