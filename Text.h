#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>
class Word;

class Text {
private:
    std::vector<Word*> mWords;
public:
    Text();
    void addWord(Word& word);
    void addWord(Word* word);
    void addWord(std::string&& word);
    void setWords(std::vector<Word*>& words);
    void setWords(std::vector<Word*>&& words);
    [[nodiscard]] std::size_t size() const;
    void print() const;
    [[nodiscard]] std::vector<Word*> getWords() const;
    [[nodiscard]] bool contains(const std::string& word) const;
    void sort();
    int removeDuplicates();
};

#endif