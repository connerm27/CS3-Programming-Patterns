// vector and list algorithms with objects in containers
// Conner Montgomery
// 02/23/2022

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;
using std::pair; 

class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return lastName_ + ", " + firstName_ + ": ";}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

void printList(const list<string>& s);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
//      cout << "\n\n" << argv[i] << "\n";  
  //    printRoster(roster);
      courseStudents.push_back(move(roster)); 
   }


   // Create Map
   map<Student, list<string>> masterList;
 
  // Loop through the course vector, loop through each list inside that vector
   for(auto &l: courseStudents) {
	for(auto&s: l) {
		list <string> l;
		masterList.insert(make_pair(s,l));
	}
   } 

  // for each student in the master list
  for(auto it=masterList.cbegin(); it != masterList.cend(); it++) {
	// counts to determine which class they are in
	int counter = 0; 
	for(auto l: courseStudents) {
		counter++;
		//for each student in the list
		for(auto stu: l) {
			if(it->first == stu) {
				//pushes back courses
				if (counter == 1) {
				
					masterList[stu].push_back("CS1");
				} else if (counter ==2) {
				
                                        masterList[stu].push_back("CS2");
				} else if (counter == 3) {
				
                                        masterList[stu].push_back("CS3");
				} else if (counter == 4) {

                                        masterList[stu].push_back("CS4");
				}
				 
			}
		}
	}


  }




cout << "All Students" << endl;
cout << "last name, first name: courses enrolled" << endl;
//printing
for(auto it=masterList.cbegin(); it != masterList.cend(); it++) {

	cout <<	it->first.print();
        printList(it->second);
	cout << endl;

}
 cout << endl << endl;


   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
//   cout << "\n\n dropouts \n"; printRoster(dropouts);
// gets rid of dropouts
for(auto x: dropouts) {

	for(auto it=masterList.cbegin(); it != masterList.cend();) {
		if(it->first == x) {
			masterList.erase(it++->first);
		} else {
			it++;
		}
	}
}



cout << "All Students" << endl;
cout << "last name, first name: courses enrolled" << endl;
//Printing
for(auto it=masterList.cbegin(); it != masterList.cend(); it++) {

        cout << it->first.print();
        printList(it->second);
        cout << endl;

}
 cout << endl << endl;



/*
   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

   cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);

   allStudents.sort(); // sorting master list
   cout << "\n\n all students sorted \n"; printRoster(allStudents);

   allStudents.unique(); // eliminating duplicates
   cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   
   for (const auto& str : dropouts)  // removing individual dropouts
      allStudents.remove(str);
   cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);

*/

}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.push_back(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}


void printList(const list<string>& s) {
 for(const auto& x: s) {
	cout << x << " ";
}
}
