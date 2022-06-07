// Conner Montgomery
// Lab2

#include <iostream>
#include <string>
#include <ctype.h>
#include "WordList.hpp"
#include "WordOccurrence.hpp"

WordList::WordList() {

	// Creates an array of WordOccurrences
	wordArray_ = new WordOccurrence[10000];

	// Defaults size to zero
	size_ = 0;

}


WordList::WordList(const WordList& list) {

	//Stored an array of  WordOccurrences the same size as the given list 
	//Must be same size since the we are making a copy of it
	wordArray_ = new WordOccurrence[list.size_];



	// Must copy each element in the array of WordOccurrences (WordList)
	// Copy Each element to wordArray_ that was created above

	for (int i=0; i < list.size_; i++) {

		wordArray_[i] = list.wordArray_[i];

	}

	//Copies size of WordList
        this->size_ = list.size_;
}



WordList::~WordList() {

	delete [] wordArray_;



}


void WordList::swap(WordList& list) {

	WordOccurrence *temp = wordArray_;
	wordArray_ = list.wordArray_;
	list.wordArray_ = temp;

	int temp_size = size_;
	size_ = list.size_;
	list.size_ = temp_size;




}



WordList& WordList::operator=(WordList rhs) {

	swap(rhs);
	return *this;

}

void WordList::addWord(const std::string& word) {

	// Flag variable to determine whether the word is a match or not
	bool flag = false;
	// Go through list
	for(int i=0;i<size_;++i) {
		// use matchWord function to determine if the words are the same
	 	if(wordArray_[i].matchWord(word)==true) {

               		wordArray_[i].increment();	//increments number of occurrences
              		 flag=true;			// Sets flag to true
               		break;
               	}
       	}

	// If flag is false, instead of incrementing existing wordoccurrence, we add a word to the array
       	if(flag==false) {
           wordArray_[size_]=word;	// Adds word
           wordArray_[size_++].increment(); // Increment that word occurrence to one
        }






}

void WordList::print() {

	for(int i=0; i<size_; i++) {
		std::cout << "Word: " << wordArray_[i].getWord() << "\n";
		std::cout << "Count: " << wordArray_[i].getNum() << "\n\n";
	}


}


bool equal(const WordList& list1, const WordList& list2) {





	// First checks to see if both lists are equal size
	if (list1.size_ == list2.size_) {


	bool flag = true;	//initializes flag as true
	 for(int i=0; i<list1.size_; i++) {
		
		// Check each element in each list, if different, return false, if all equal, return true
               if(list1.wordArray_[i].matchWord(list2.wordArray_[i].getWord()) == false) {
			flag = false;
		}
	 }

		return flag;

        } else {

		return false;
	}





}


bool WordList::alNum(std::string& word) {

	// Function to ensure each word is alpha numeric

	// For each character in the word
	for(int i=0; i<word.length(); i++) {
		if(ispunct(word[i])) {
			word.erase(i--,1);		// uses erase() to delete punctuation in word
		}
	}

	for(int i=0; i<word.length(); i++) {
		if(!isalnum(word[i])) {
			return false;
		}
	}

	return true;					// Should return true at all times 

}


void WordList::bubbleSort() {

// I decided to use bubble sort becuase it is the easiest to implement
// Algorithm is pretty standard

	for(int i=0; i<size_-1; i++) {
		for(int j=0; j<size_-i-1; j++) {

			//Check to see if current word is greater that the one next to it
			if(wordArray_[j].getNum() > wordArray_[j+1].getNum()) {
				// simply swaps the value if current value is greater than the one next to it 
				// sorts them from smallest to greatest
				WordOccurrence temp = wordArray_[j+1];
				wordArray_[j+1] = wordArray_[j];
				wordArray_[j] = temp;
			}

		}
	}



}
