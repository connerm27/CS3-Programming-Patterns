// Conner Montgomery
// Lab 10

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;


// Context
class Process {
public:
   Process();

   // behaviors
   void dispatch();
   void suspend();
   void block();
   void unblock();
   void exit();
   void report();
   static int tracker;

  // int getTracker(){ return tracker;};
   // part of implementation of state pattern
   void changeState(State* state){state_=state;}
private:
   State* state_;   
};

int Process::tracker = 0;



// abstract state

// absract state
class State{
public:
   // provides default implementation
   virtual void dispatch(Process*){} 
   virtual void suspend(Process*){}
   virtual void block(Process*){}
   virtual void unblock(Process*){}
   virtual void exit(Process*){}
   virtual void report() =0;
   void changeState(Process* p, State* s){
      p->changeState(s);
   }
};



class Ready: public State{
public:
   static State* instance(){
      static State* onlyInstance = new Ready;
      return onlyInstance;
   }
   void dispatch(Process*) override;

   void report() override {
	cout << "process " << Process::tracker  <<  " is ready\n";
   }
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};


class Running: public State{
public:
   static State* instance(){
      static State* onlyInstance = new Running;
      return onlyInstance;
   }
   void exit(Process*) override; 
   void suspend(Process*) override;
   void block(Process*) override; 
   void report() override {
	cout << "process " << Process::tracker <<  " is running\n";
   }
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};


class Blocked: public State{
public:
   static State* instance(){
      static State* onlyInstance = new Blocked;
      return onlyInstance;
   }
   void unblock(Process*) override;  
   void report() override {
	cout << "process " << Process::tracker  <<  " is blocked\n";
   }
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};

// State Transitions Member Functions

// Ready
void Ready::dispatch(Process *p) {
   changeState(p, Running::instance());
} 


// Running
void Running::suspend(Process *p) {
   changeState(p, Ready::instance());
} 

void Running::block(Process *p) {
   changeState(p, Blocked::instance());

}

void Running::exit(Process *p) {
	// terminates process 

	//delete p;
	cout << "Process Terminated\n";

	//changeState(p, nullptr);

}



// Blocked
void Blocked::unblock(Process *p) {
   changeState(p, Ready::instance());
}



// Process Member Functions
Process::Process(){
	state_=Ready::instance();
	tracker++;
}

// handles/behaviors
void Process::dispatch(){state_->dispatch(this);}
void Process::suspend(){state_->suspend(this);}
void Process::block(){state_->block(this);}
void Process::unblock(){state_->unblock(this);}
void Process::exit(){state_->exit(this);}

//int Process::getTracker() { return tracker; }

void Process::report(){state_->report();}







int main() {

   Process p;

  cout << "Initial Process State: ";
  p.report();
  cout << " d = Dispatch\n s = Suspend\n b = Block\n u = Unblock\n e = Exit\n";


int e = 0;

while( e == 0 ) {
  cout << "Choose an Action [d/s/b/u/e] ";
  char action;
  cin >> action;

 if(action == 'd') {
	p.dispatch();
        p.report(); 
 } else if (action == 's') {
	p.suspend();
	p.report();
 } else if (action == 'b') {
	p.block();
	p.report();
 } else if (action == 'u') {
	p.unblock();
	p.report();
 } else if(action == 'e') {
  	p.exit();
	e = 1;
 } else {
	cout << "Action not available, try again!\n";

 }
}


Process p2;
p2.report();
p2.dispatch();
p2.report();

}






