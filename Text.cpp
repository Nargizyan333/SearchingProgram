#include "Text.h"
#include "Word.h"
#include <iostream>

Text::Text() = default;

void Text::addWord(Word& word) {
    mWords.push_back(&word);
}

void Text::addWord(Word *word) {
    mWords.push_back(word);
}

void Text::addWord(std::string&& word) {
    mWords.push_back(new Word(std::move(word)));
}

std::vector<Word *> Text::getWords() const {
    return mWords;
}

bool Text::contains(const std::string &word) const {
    return std::any_of(mWords.begin(), mWords.end(), [&](Word* const wordObj) {
        return wordObj -> getWord() == word;
    });
}

std::size_t Text::size() const {
    return mWords.size();
}

void Text::print() const {
    for (Word* word : mWords) {
        std::cout << word->getWord() << std::endl;
    }
}

void Text::sort() {
    std::sort(mWords.begin(), mWords.end(), [] (Word* const word1, Word* const word2) {
        return word1->getWord() < word2->getWord();
    });
}

int Text::removeDuplicates() {
    int index = 0;
    for (int i = 0; i < mWords.size(); ++i) {
        if (mWords[i - 1]->getWord() != mWords[i]->getWord() || i == 0) {
            mWords[index] = mWords[i];
            ++index;
        }
    }
    return index;
}

void Text::setWords(std::vector<Word *> &&words) {
    mWords = std::move(words);
}

void Text::setWords(std::vector<Word *> &words) {
    mWords = words;
}