// Conner Montgomery
// Lab 2

#ifndef _WORDOCCURRENCE_HPP_
#define _WORDOCCURRENCE_HPP_

#include <iostream>
#include <string>


class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0) {
	word_ = word;
	num_ = num;
	}
    bool matchWord(const std::string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    std::string getWord() const; 
    int getNum() const;

private:
    std::string word_;
    int num_;
};


#endif


