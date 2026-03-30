#include "word_provider.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char filename[256];
} FileProviderData;

static int fileLoadWords(WordProvider* self, WordEntry* wordList, int maxWords) {
    FileProviderData* data = (FileProviderData*)self->data;
    FILE *file = fopen(data->filename, "r");
    if (!file) return 0;

    char buffer[300];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) && count < maxWords) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strlen(buffer) == 0) continue;

        char *sep = strchr(buffer, ':');
        if (sep) {
            *sep = '\0';
            strncpy(wordList[count].topic, buffer, MAX_WORD_LENGTH - 1);
            wordList[count].topic[MAX_WORD_LENGTH - 1] = '\0';
            
            strncpy(wordList[count].word, sep + 1, MAX_WORD_LENGTH - 1);
            wordList[count].word[MAX_WORD_LENGTH - 1] = '\0';
            count++;
        }
    }
    fclose(file);
    return count;
}

static void fileGetRandomWord(WordProvider* self, WordEntry* outWord, 
                              const WordEntry* wordList, int wordCount) {
    if (wordCount <= 0) return;
    int idx = rand() % wordCount;
    *outWord = wordList[idx];
}

WordProvider createFileWordProvider(const char* filename) {
    static FileProviderData data;
    strncpy(data.filename, filename, sizeof(data.filename) - 1);
    data.filename[sizeof(data.filename) - 1] = '\0';

    WordProvider wp = {0};
    wp.data = &data;
    wp.loadWords = fileLoadWords;
    wp.getRandomWord = fileGetRandomWord;

    return wp;
}