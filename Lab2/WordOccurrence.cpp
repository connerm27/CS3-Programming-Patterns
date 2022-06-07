#include "WordOccurrence.hpp"
#include <iostream>
#include <string>



bool WordOccurrence::matchWord(const std::string& word) {

// Compares current obj to passed in word
if(word.compare(word_) == 0) {
	return true;
} else {
	return false;
}


}


void WordOccurrence::increment() {

	num_++;

}


std::string WordOccurrence::getWord() const {

	return word_;

}



int WordOccurrence::getNum() const {

	return num_;


}
