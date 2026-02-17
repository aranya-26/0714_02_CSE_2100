#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/* -------------------- Constants -------------------- */

#define MAX_WORDS 500
#define MAX_LEN 128

static const int WINDOW_WIDTH  = 1000;
static const int WINDOW_HEIGHT = 700;
static const int MAX_TRIES     = 6;


/* -------------------- Structures -------------------- */

/* Store topic and word */
typedef struct
{
    char topic[MAX_LEN];
    char word[MAX_LEN];

} WordEntry;


/* Keyboard button structure */
typedef struct
{
    Rectangle rect;
    char letter;
    bool pressed;
    bool visible;

} KeyButton;


/* -------------------- Function Prototypes -------------------- */

void draw_hangman(int tries);

void init_guessed_word(
    const char *word,
    char *guessed,
    bool *revealed_mask,
    int *unique_letters
);

void randomly_reveal(
    char *word,
    char *guessed,
    bool *revealed_mask,
    int reveal_count,
    int *correct_count
);

int load_words(
    const char *filename,
    WordEntry *list,
    int max_words
);

int create_keyboard(KeyButton *keys);

char handle_keyboard_buttons(
    KeyButton *keys,
    int key_count,
    Vector2 mouse_pos,
    bool mouse_clicked
);


/* -------------------- Hangman Drawing -------------------- */

void draw_hangman(int tries)
{
    /* Stand */
    DrawRectangleLines(120, 120, 260, 380, Fade(BLACK, 0.6f));

    DrawLine(200, 500, 420, 500, DARKGRAY);
    DrawLine(250, 500, 250, 160, DARKGRAY);
    DrawLine(250, 160, 370, 160, DARKGRAY);
    DrawLine(370, 160, 370, 210, DARKGRAY);

    /* Head */
    if (tries >= 1)
    {
        DrawCircle(370, 235, 30, BLACK);
        DrawCircleLines(370, 235, 30, GRAY);
    }

    /* Body */
    if (tries >= 2) DrawLine(370, 265, 370, 360, BLACK);

    /* Hands */
    if (tries >= 3) DrawLine(370, 290, 330, 330, BLACK);
    if (tries >= 4) DrawLine(370, 290, 410, 330, BLACK);

    /* Legs */
    if (tries >= 5) DrawLine(370, 360, 330, 410, BLACK);
    if (tries >= 6) DrawLine(370, 360, 410, 410, BLACK);

    /* Background */
    if (tries > 0)
    {
        DrawRectangle(120, 120, 260, 380, Fade(RAYWHITE, 0.02f));
    }
}


/* -------------------- Initialize Word -------------------- */

void init_guessed_word(
    const char *word,
    char *guessed,
    bool *revealed_mask,
    int *unique_letters
)
{
    int length = strlen(word);

    bool present[26] = { false };

    *unique_letters = 0;

    for (int i = 0; i < length; i++)
    {
        char ch = word[i];

        if (isalpha((unsigned char) ch))
        {
            guessed[i] = '_';
            revealed_mask[i] = false;

            char lower = tolower(ch);

            if (!present[lower - 'a'])
            {
                present[lower - 'a'] = true;
                (*unique_letters)++;
            }
        }
        else
        {
            guessed[i] = ch;
            revealed_mask[i] = true;
        }
    }

    guessed[length] = '\0';
}


/* -------------------- Random Reveal -------------------- */

void randomly_reveal(
    char *word,
    char *guessed,
    bool *revealed_mask,
    int reveal_count,
    int *correct_count
)
{
    int length = strlen(word);
    int tries  = 0;

    while (reveal_count > 0 && tries < 1000)
    {
        int position = rand() % length;

        if (!revealed_mask[position] &&
            isalpha((unsigned char) word[position]))
        {
            guessed[position] = tolower(word[position]);
            revealed_mask[position] = true;

            (*correct_count)++;
            reveal_count--;
        }

        tries++;
    }
}


/* -------------------- Load Words -------------------- */

int load_words(
    const char *filename,
    WordEntry *list,
    int max_words
)
{
    FILE *file = fopen(filename, "r");

    if (!file) return 0;

    char buffer[300];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) && count < max_words)
    {
        buffer[strcspn(buffer, "\r\n")] = 0;

        if (strlen(buffer) == 0) continue;

        char *separator = strchr(buffer, ':');

        if (separator)
        {
            *separator = '\0';

            strncpy(list[count].topic, buffer, MAX_LEN - 1);
            strncpy(list[count].word, separator + 1, MAX_LEN - 1);

            list[count].topic[MAX_LEN - 1] = '\0';
            list[count].word[MAX_LEN - 1]  = '\0';

            count++;
        }
    }

    fclose(file);

    return count;
}


/* -------------------- Create Keyboard -------------------- */

int create_keyboard(KeyButton *keys)
{
    const char *row1 = "ABCDEFGHI";
    const char *row2 = "JKLMNOPQR";
    const char *row3 = "STUVWXYZ";

    int margin_x = 40;
    int start_y  = 420;

    int key_w = 48;
    int key_h = 48;
    int gap   = 12;

    int index = 0;
    int x_pos = margin_x;

    /* First Row */
    for (int i = 0; row1[i]; i++)
    {
        keys[index].rect =
            (Rectangle){ x_pos, start_y, key_w, key_h };

        keys[index].letter  = row1[i];
        keys[index].pressed = false;
        keys[index].visible = true;

        x_pos += key_w + gap;
        index++;
    }

    /* Second Row */
    x_pos = margin_x;

    for (int i = 0; row2[i]; i++)
    {
        keys[index].rect =
            (Rectangle){ x_pos,
                         start_y + key_h + gap,
                         key_w,
                         key_h };

        keys[index].letter  = row2[i];
        keys[index].pressed = false;
        keys[index].visible = true;

        x_pos += key_w + gap;
        index++;
    }

    /* Third Row */
    x_pos = margin_x + 24;

    for (int i = 0; row3[i]; i++)
    {
        keys[index].rect =
            (Rectangle){ x_pos,
                         start_y + 2 * (key_h + gap),
                         key_w,
                         key_h };

        keys[index].letter  = row3[i];
        keys[index].pressed = false;
        keys[index].visible = true;

        x_pos += key_w + gap;
        index++;
    }

    return index;
}


/* -------------------- Keyboard Handler -------------------- */

char handle_keyboard_buttons(
    KeyButton *keys,
    int key_count,
    Vector2 mouse_pos,
    bool mouse_clicked
)
{
    char pressed = 0;

    for (int i = 0; i < key_count; i++)
    {
        if (!keys[i].visible) continue;

        Color background =
            keys[i].pressed ? Fade(DARKGREEN, 0.9f) : LIGHTGRAY;

        if (CheckCollisionPointRec(mouse_pos, keys[i].rect))
        {
            background = Fade(SKYBLUE, 0.7f);

            if (mouse_clicked && !keys[i].pressed)
            {
                keys[i].pressed = true;
                pressed = tolower(keys[i].letter);
            }
        }

        DrawRectangleRec(keys[i].rect, background);

        DrawRectangleLinesEx(
            keys[i].rect,
            2,
            Fade(GRAY, 0.7f)
        );

        DrawText(
            TextFormat("%c", keys[i].letter),
            keys[i].rect.x + 15,
            keys[i].rect.y + 8,
            22,
            BLACK
        );
    }

    return pressed;
}


/* -------------------- Main Function -------------------- */

int main(void)
{
    /* Initialize Window */
    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Hangman"
    );

    SetTargetFPS(60);
    srand((unsigned) time(NULL));


    /* Load Words */
    WordEntry words[MAX_WORDS];

    int word_count =
        load_words("words.txt", words, MAX_WORDS);

    if (word_count == 0)
    {
        strcpy(words[0].topic, "Fruits");
        strcpy(words[0].word,  "banana");

        strcpy(words[1].topic, "Country");
        strcpy(words[1].word,  "bangladesh");

        word_count = 2;
    }


    /* Create Keyboard */
    KeyButton keys[26];

    int key_count = create_keyboard(keys);


    /* Select Random Word */
    int random_index = rand() % word_count;

    char topic[MAX_LEN];
    char word[MAX_LEN];

    strcpy(topic, words[random_index].topic);
    strcpy(word,  words[random_index].word);


    for (int i = 0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
    }


    int word_length = strlen(word);

    char guessed[MAX_LEN];
    bool revealed_mask[MAX_LEN];

    int unique_letters = 0;

    init_guessed_word(
        word,
        guessed,
        revealed_mask,
        &unique_letters
    );


    /* Reveal Logic */
    int reveal_count;

    if (word_length <= 4)      reveal_count = 1;
    else if (word_length <=6) reveal_count = 2;
    else                      reveal_count = 3;


    int correct_count = 0;

    randomly_reveal(
        word,
        guessed,
        revealed_mask,
        reveal_count,
        &correct_count
    );


    /* Game State */
    int tries = 0;

    bool game_over = false;
    bool win       = false;

    bool guessed_alpha[26] = { false };


    /* Main Game Loop */
    while (!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();

        bool mouse_clicked =
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON);


        /* Drawing */
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("HANGMAN", 350, 14, 52, DARKBLUE);

        draw_hangman(tries);

        handle_keyboard_buttons(
            keys,
            key_count,
            mouse_pos,
            mouse_clicked
        );

        EndDrawing();


        /* Exit on ESC */
        if (IsKeyPressed(KEY_ESCAPE))
        {
            break;
        }
    }


    CloseWindow();

    return 0;
}
