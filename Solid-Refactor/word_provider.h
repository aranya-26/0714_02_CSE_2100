#ifndef WORD_PROVIDER_H
#define WORD_PROVIDER_H

#include "hangman_types.h"

typedef struct WordProvider WordProvider;

typedef int  (*LoadWordsFunc)(WordProvider* self, WordEntry* wordList, int maxWords);
typedef void (*GetRandomWordFunc)(WordProvider* self, WordEntry* outWord, const WordEntry* wordList, int count);

struct WordProvider {
    LoadWordsFunc     loadWords;
    GetRandomWordFunc getRandomWord;
    void*             data;
};

WordProvider createFileWordProvider(const char* filename);

#endif