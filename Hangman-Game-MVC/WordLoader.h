#ifndef WORD_LOADER_H
#define WORD_LOADER_H

#include "hangman_types.h"
#include <vector>
#include <string>

class WordLoader {
public:
    static std::vector<WordEntry> LoadWords(const std::string& filename);
};

#endif
