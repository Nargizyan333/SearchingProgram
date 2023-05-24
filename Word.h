#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
    std::string mWord;
public:
    Word(std::string word);
    void setWord(const std::string& word);
    void toLowercase();
    void removeSpecialChars();
    [[nodiscard]] std::string getWord();
};

#endif