//Conner Montgomery
//Lab1


#include <iostream>
#include <fstream>
#include <string.h>


using std::cout; using std::endl; using std::string;


int main(int argc, char* argv[]){
   //for(int i=0; i < argc; ++i)
      // for (auto e : argv)
//	cout << argv[i] << endl;

// assigns files instream vars to files inputted on command line

// Terminates program for incorrect # of command line arguments
if (argc != 3) {
	std::cout << "Incorrect number of command line arguments\n";
	return 0;
}

std::ifstream file1 (argv[1]);
std::ifstream file2 (argv[2]);


if(!file1.is_open()) {
	std::cout << "Unable to open file\n";
}

if(!file2.is_open()) {
        std::cout << "Unable to open file\n";
}

// Variable to keep track of line number
int count = 0;

// While the files still have lines of text to input
while (!file1.eof() || !file2.eof()) {

	count++;	// increments line count

	// Gets line from first file
	string line;
	std::getline(file1, line);

	// Gets line from second file
	string line2;
        std::getline(file2, line2);

	 if(line.compare(line2) == 0) {

               // Do Nothing

        } else {

		std::cout << argv[1] <<  ": " << count << ": ";
		std::cout << line << " \n";

        	std::cout << argv[2] <<  ": " << count << ": ";
        	std::cout << line2 << " \n";
	
		// Determines loop size of smaller line to find difference
		int loopSize;
		if (line.size() < line2.size()) {

			loopSize = line.size();

		} else {

			loopSize = line2.size();

		}

		char c;
		char c2;
		int length;
		for(int i=0; i<loopSize; i++) {
			c = line.at(i);
			c2 = line2.at(i);
			//compares each character of each line, breaks loop when difference is found
			if(c != c2) {
				length = i;
				break;
			}
		}
			//if the line is empty, then length of spaceString is 0
		if (line.empty() || line2.empty()) {
			length = 0;
		}
		// Handles if line number is one or two digits
		if(count < 10) {

			length = length + 5 + strlen(argv[1]);
		} else {
			length = length + 6 + strlen(argv[1]);
		}
		string spaceString(length, ' ');

		std::cout << spaceString << "^"  << "\n";




        }


	std::cout << "\n";


}

}

