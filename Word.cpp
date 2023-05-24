#include "Word.h"
#include <iostream>

Word::Word(std::string word) : mWord(word) {}

void Word::setWord(const std::string &word) {
    mWord = word;
}

void Word::toLowercase() {
    std::transform(mWord.begin(), mWord.end(), mWord.begin(), [](char c) {
        return std::tolower(c);
    });
}

void Word::removeSpecialChars() {
    mWord.erase(std::remove_if(mWord.begin(), mWord.end(), [](char c) {
        return !(std::isalpha(c) || c == '\'' || c == '-');
    }), mWord.end());
}

std::string Word::getWord() {
    toLowercase();
    removeSpecialChars();
    return mWord;
}