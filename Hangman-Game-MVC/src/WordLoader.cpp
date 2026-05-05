#include "WordLoader.h"
#include <fstream>

std::vector<WordEntry> WordLoader::LoadWords(const std::string& filename) {
    std::vector<WordEntry> wordList;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line) && wordList.size() < MAX_WORDS) {
        if (line.empty()) continue;
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            WordEntry entry;
            entry.topic = line.substr(0, pos);
            entry.word = line.substr(pos + 1);
            wordList.push_back(std::move(entry));
        }
    }
    return wordList;
}
