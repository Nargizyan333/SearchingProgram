#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Word.h"
#include "Text.h"

std::vector<Word*> merge(Text& t1, Text& t2);

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream fout;
    std::ifstream fin;
    fin.open("./words_alpha.txt");
    Text alphaWords;
    if (fin.is_open()) {
        std::string word;
        while (fin >> word) {
            alphaWords.addWord(new Word(word));
        }
    }
    fin.close();

    fin.open("./1.txt");
    Text words1;
    if (fin.is_open()) {
        std::string word;
        while (fin >> word) {
            Word wordObj(word);
            words1.addWord(wordObj.getWord());
        }
    }
    fin.close();

    Text words2;
    fin.open("./2.txt");
    if (fin.is_open()) {
        std::string word;
        while (fin >> word) {
            Word wordObj(word);
            words2.addWord(wordObj.getWord());
        }
    }
    fin.close();

    fout.open("./db.txt");
    Text db;
    db.setWords(merge(words1, words2));
    for (Word* word : db.getWords()) {
        fout << word->getWord() << " : ";
        if (words1.contains(word->getWord())) {
            fout << "1, ";
        }
        if (words2.contains(word->getWord())) {
            fout << "2, ";
        }
        fout << std::endl;
    }
    fout.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Working time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs" << std::endl;
    bool open = true;
    while (open) {
        int choice;
        std::cout << "Choose the option: " << std::endl;
        std::cout << "1) Close the program" << std::endl;
        std::cout << "2) Find word" << std::endl;
        std::cin >> choice;
        if (choice == 1) {
            open = false;
        } else if (choice == 2) {
            std::string word;
            std::cout << "Input the word:\t";
            std::cin >> word;
            std::vector<Word*>&& vec = db.getWords();
            auto count = std::count_if(vec.begin(), vec.end(), [&](Word* wordObj) {
                return wordObj->getWord() == word;
            });
            if (count == 2) {
                std::cout << "./1.txt" << std::endl << "./2.txt" << std::endl;
            } else if (count == 0) {
                std::cout << "Word not found" << std::endl;
            } else {
                if (words1.contains(word)) {
                    std::cout << "./1.txt" << std::endl;
                } else {
                    std::cout << "./2.txt" << std::endl;
                }
            }
        }
    }
    return 0;
}

std::vector<Word*> merge(Text& t1, Text& t2) {
    t1.sort();
    int s1 = t1.removeDuplicates();
    t2.sort();
    int s2 = t2.removeDuplicates();
    std::vector<Word*> res(s1 + s2);
    int i = 0, j = 0, index = 0;
    auto&& vec1 = t1.getWords();
    auto&& vec2 = t2.getWords();
    while (i < s1 && j < s2) {
        if (vec1[i]->getWord() <= vec2[i]->getWord()) {
            res[index] = vec1[i];
            ++i;
        } else {
            res[index] = vec2[j];
            ++j;
        }
        ++index;
    }
    while (i < s1) {
        res[index] = vec1[i];
        ++i;
        ++index;
    }
    while (j < s2) {
        res[index] = vec2[j];
        ++j;
        ++index;
    }
    return res;
}