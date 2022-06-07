//Conner Montgomery
// Lab 2


#include "WordOccurrence.hpp"
#include "WordList.hpp"
#include <iostream>
#include <fstream>
#include <string.h>


using std::cout; using std::endl; using std::string;


int main(int argc, char* argv[]){

std::ifstream file (argv[1]);


if(!file.is_open()) {
	std::cout << "Unable to open file\n";

	return 0;
}

if(argc > 2) {
	cout << "Too many arguments\n";
	return 0;
}

WordList w;
string word;
while(!file.eof()) {

// Get character from file

char inChar;
file.get(inChar);


if(inChar != ' ' && inChar != '\n' && inChar != '\0') {
	// Makes a word
	word.push_back(inChar);

} else {
	if (word != "") {
		// makes sure is it alphanumeric
		if(w.alNum(word)) {
			w.addWord(word);
		}
	}
	word = "";
}


}

//Sort array then print
w.bubbleSort();
w.print();







}




