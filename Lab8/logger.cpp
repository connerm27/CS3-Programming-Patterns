// Conner Montgomery
// Lab 8
// Edited 3/17/2022


#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::endl;
using std::string;

class Logger {

public:
	static Logger& instance() {
		static Logger l;
		return l;
	}

	void report(const string& s) {
		// append string to file
		std::ofstream fout;
   		fout.open("test.txt", std::fstream::out | std::fstream::app);
   		fout << s << std::endl;
   		fout.close();

	}

	~Logger() {

	}

private:
	Logger() {}
	Logger(const Logger&) {}
	Logger& operator=(const Logger&){}


};


void myFunc(){
   Logger::instance().report("myfunc");
   Logger::instance().report("also in myfunc");
}

void myFunc2(){
   Logger::instance().report("myfunc2");
   Logger::instance().report("also in myfunc2");
}


int main() {


	Logger::instance().report("Conner");
	Logger::instance().report("Test");
	Logger::instance().report("Computer Science"); 
	Logger::instance().report("Lorem Ipsum");

	myFunc();
	myFunc2();


}
