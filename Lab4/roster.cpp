// vector and list algorithms
// Conner Montgomery
// 2/10/2022
// Lab 4

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);  

// printing a list out
void printRoster(const list<string>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }

   // Student Entry vectors
   vector<list<string>> studentEntries;

// vector of courses of students
   vector <list<string>> courseStudents; 

  // takes in a list of students from each class
   for(int i=1; i < argc-1; ++i){
      list<string> roster;
      readRoster(roster, argv[i]);
      courseStudents.push_back(move(roster));


   }
	
   // For each list of students from each class
   for(auto x: courseStudents) {
	// for each student in the given class
	for(auto y: x) {
		// create new sample list
		list<string> sample;
		// add student to the list
		sample.push_back(move(y));
		// add sample to the student entries
		int flag = 0;
		for(auto &s: studentEntries) {
			if(sample.front() == s.front()) {
				flag = 1;
			} 
		}
		if(flag == 1) {
			// do nothing
		} else {
			studentEntries.push_back(move(sample));
		}
	}
   }

   // puts the classes each student is in, in the list for each student in student entries
   // For every list (x) in studetnEntries
   for(auto& x: studentEntries) {
	//Counter determines which list they are on aka CS1, CS2, CS3, CS4
	int counter = 0;
		// for each list in course students
		for(auto z: courseStudents) {
			//increment counter
			counter++;
				// for each string in each list
				for(auto y: z) {
					// compares student entries list to the lists of students in each class
					if (x.front()==y) {
						// determines which class they are in based on the counter, and then pushes that class name to the student entry list
						if (counter == 1) {
							x.push_back("CS1");
						} else if (counter ==2) {
							x.push_back("CS2");
						} else if (counter == 3) {
							x.push_back("CS3");
						} else if (counter == 4) {
							x.push_back("CS4");
						}
					}
				}

		}

   }


	

	cout << "All Students\n";
	cout << "First Name Last Name: Courses Enrolled\n";

	for(auto z: studentEntries) {

		printRoster(z); 
		cout << endl;
	
	}




   // reading in dropouts
   list<string> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
	//   cout << "\n\n dropouts \n"; printRoster(dropouts);




   // For each student 
	int itCount = 0;
	for (auto &s: studentEntries) {
	       //For each dropout in dropouts
		for(auto &d: dropouts) {
			if(s.front() == d) {
				studentEntries.erase(studentEntries.begin()+itCount);

			}
		}
		itCount++;

	}

	sort(studentEntries.begin(), studentEntries.end());


	cout << "\n\nAll students, dropouts removed and sorted\n";
	cout << "First Name Last Name: Course Enrolled\n";


 for(auto z: studentEntries) {

                printRoster(z); 
                cout << endl;

        }


}

// reading in a file of names into a list of strings
void readRoster(list<string>& roster, string fileName){
   ifstream course(fileName);

   string first, last;
   string courseName;

   while(course >> first >> last)
      roster.push_back(move(first + ' ' + last + ": "));
   course.close();
}

// printing a list out
void printRoster(const list<string>& roster){
   for(const auto& str : roster)
      cout << str << " ";;
}




