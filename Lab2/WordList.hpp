// Conner Montgomery
// Lab2

#ifndef _WORDLIST_HPP_
#define _WORDLIST_HPP_

#include "WordOccurrence.hpp"
#include <iostream>
#include <string>


class WordList{
public:
    // Default Constructor
	WordList();

    // copy constructor
	WordList(const WordList&);


    // Destructor
	~WordList();

    // Overloaded Assignment
	WordList& operator=(WordList);

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const std::string &);
    void print();
    void swap(WordList&);
    bool alNum(std::string& word);
    void bubbleSort();


private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};


#endif


