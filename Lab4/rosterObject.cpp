// vector and list algorithms with objects in containers
// Conner Montgomery
// 02/15/2022
//Lab 4

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <array>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}

/* 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      courses_(move(org.courses_))
   {}
  */
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return lastName_ + ", " + firstName_;}


 void addCourse(string s) {
	courses_.push_back(s);
}


 void printCourses() {
	for(auto &c: courses_) {
		cout << c << " ";
	}
}

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
   list<string> courses_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      courseStudents.push_back(move(roster)); 
   }


   //Vector that will contain the master list of students
  vector <Student> studentEntries;
  // for each class roster
  for(auto x:courseStudents) {
	//for each student in each class roster
	for(auto y: x) {
		// this will filter out duplicates when building the new roster
		int flag = 0;
		// Loops through the student entries to see if there is a duplicate
		for(auto &z: studentEntries) {
			if(z == y) {
				flag = 1;
			}
		}
	
		if (flag == 1) {
			// do nothing
		} else {
			studentEntries.push_back(move(y));
		}

	}

 }



// Puts the classes each student is in into the students list in each Student Object
// for every student in student entries
   for(auto &s: studentEntries) {
	//Counter determines which list they are on aka CS1, CS2, CS3, CS4
	int counter = 0;
	// for each list in course students
	for(auto l: courseStudents) {
		counter++;
			// for each students in each list
			for(auto stu: l) {
				if(s == stu) {
					// determines which class they are in based on the counter, and then pushes that class name to the student entry list
					if (counter == 1) {
						s.addCourse("CS1");
					} else if (counter ==2) {
						s.addCourse("CS2");
					} else if (counter == 3) {
						s.addCourse("CS3");
					} else if (counter == 4) {
						s.addCourse("CS4");
					}
				}
			}
	}

   }





   cout << "All Students\n";
   cout << "Last Name, First Name: Courses Enrolled\n";
   // Prints master list of each student and each course said student is in
   for (auto student: studentEntries) {
	cout << student.print() << ": ";
	student.printCourses();
	cout << "\n";
   }



   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
  
   // For each student 
	vector<int> ds;
	int itCount = 0;
	for (auto &s: studentEntries) {
	       //For each dropout in dropouts
		for(auto d: dropouts) {
			if(s == d) {
				ds.push_back(itCount);
			}
		}
		itCount++;

	}

  

   // Erases collected dropouts from above
  int i=0;  
   for(auto x: ds) {
	studentEntries.erase(studentEntries.begin()+(x-i));
   	i++;
   }

  sort(studentEntries.begin(), studentEntries.end());

   cout << "\n\nAll Students\n";
   cout << "Last Name, First Name: Courses Enrolled\n";
   // Prints master list of each student and each course said student is in
   for (auto student: studentEntries) {
        cout << student.print() << ": ";
        student.printCourses();
        cout << "\n";
   }





/*
   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

*/

/*
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
