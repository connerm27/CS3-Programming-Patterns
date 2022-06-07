// Conner Montgomery
// Lab 10

// USE THIS CODE FOR LAB 10 SCHEDUlER PART 3


#include <iostream>
#include <string>
#include <queue>

using std::cin; using std::cout; using std::endl; using std::string; using std::queue;

class State;


// Context
class Process {
public:
   Process();
   // Cloned for Scheduler
   Process* clone();

   // behaviors
   void dispatch();
   void suspend();
   void block();
   void unblock();
   void exit();
   string report();
   static int tracker;
   int getID() {return current_id;};
  // int getTracker(){ return tracker;};
   // part of implementation of state pattern
   void changeState(State* state){state_=state;}
private:
   State* state_;
  int current_id;
};

int Process::tracker = -1;



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
   virtual string report() =0;
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

   string report() override {
	return "ready";
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
   string report() override {
	return  "running";
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
   string report() override {
	return "blocked";
   }
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};

// State Transitions Member Functions

// Ready
void Ready::dispatch(Process *p) {
   cout << "Dispatched" << endl;
   p->report();
   changeState(p, Running::instance());
} 


// Running
void Running::suspend(Process *p) {
    cout << "Suspended" << endl;
   p->report();
   changeState(p, Ready::instance());
} 

void Running::block(Process *p) {
   cout << "Blocked" << endl;
   p->report();
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
  cout << "Unblocked" << endl;
  p->report(); 
  changeState(p, Ready::instance());
}



// Process Member Functions
Process::Process(){
	state_=Ready::instance();
	tracker++;
	current_id = tracker;
}




Process* Process::clone() {
  // returns process in new state
  return new Process();
}



// handles/behaviors
void Process::dispatch(){state_->dispatch(this);}
void Process::suspend(){state_->suspend(this);}
void Process::block(){state_->block(this);}
void Process::unblock(){state_->unblock(this);}
void Process::exit(){state_->exit(this);}

//int Process::getTracker() { return tracker; }
string Process::report(){return state_->report();}





//#########################################################3

// PROTOTYPE CODE BELOW


class Scheduler {

public: 
	Scheduler();
	~Scheduler();

	void admit();
        void run();
	void dispatch();
        void suspend();
	void block();
	void exit();
	queue<Process*> readyQueue;
	queue<Process*> exitQueue;


private:

  	queue<Process*> blockedQueue; 
        Process* prototype;
	Process* dispatchedProcess;

};



Scheduler::Scheduler() {
   // Create new prototype from Process
   prototype = new Process();


}


Scheduler::~Scheduler() {
  delete prototype;
}


void Scheduler::admit() {
   // Create new Process as clone
   Process* newProcess = prototype->clone();

   // Make State of Process "Ready"
   newProcess->changeState(Ready::instance());

   // report new process creation
   cout << "Process " << newProcess->getID() << " is " << newProcess->report() << endl;

   // Add to ready queue
   readyQueue.push(newProcess);

   
}


void Scheduler::run() {

while(!readyQueue.empty() || !blockedQueue.empty()) {

   // if the ready queue is empty, but there are still blocked processes, run this
    if(readyQueue.empty() && !blockedQueue.empty()) {
	while(!blockedQueue.empty()) {
		blockedQueue.front()->changeState(Ready::instance());
	        cout << "Process " << blockedQueue.front()->getID() << " has been unblocked and is " << blockedQueue.front()->report() << endl;
        	readyQueue.push(blockedQueue.front());
        	blockedQueue.pop();
   	}

    }

    // dispatch the admitted processes in the queue
    dispatch();



}

}



void Scheduler::dispatch() {



   cout << "Dispatching Process " << readyQueue.front()->getID() << "..." << endl;


   // get process from ready queue to dispatch

   dispatchedProcess = readyQueue.front();

   //change state
   dispatchedProcess->changeState(Running::instance());
  cout << "Process " << readyQueue.front()->getID() << " is " << readyQueue.front()->report() << endl;

// Probability of what happens with the running instance

   int random =  1 + (rand() % 100);
      if(random < 33) {
         exit();
      } else if (random >= 33 || random < 66) {
         block();
      } else {
         suspend();
      }

readyQueue.pop();

}



void Scheduler::suspend() {
   // Process Suspended, ready must move to tail of queue
   // Add to ready queue
   cout << "Process " << readyQueue.front()->getID() << " is suspended" <<  endl;
   dispatchedProcess->changeState(Ready::instance());
   readyQueue.push(dispatchedProcess);
  cout << "Process " << readyQueue.front()->getID() << " is " <<  readyQueue.front()->report() <<  endl;

}

void Scheduler::block() {
  // Process moves to tail of blocking queue

  
  cout << "Process " << readyQueue.front()->getID() << " Blocked" << endl;
  dispatchedProcess->changeState(Blocked::instance());
  blockedQueue.push(dispatchedProcess);


  // Unblocking probability 
  int random =  1 + (rand() % 100);

   if(random > 50) {
	// Do Nothing
   } else {
	blockedQueue.front()->changeState(Ready::instance());
	cout << "Process " << blockedQueue.front()->getID() << " has been unblocked and is " << blockedQueue.front()->report() << endl;
	readyQueue.push(blockedQueue.front());
	blockedQueue.pop();
   }
}


void Scheduler::exit() {
  exitQueue.push(dispatchedProcess);
   cout << "Process " << readyQueue.front()->getID()  << " Completed (Exits)" << endl;

}






int main() {


srand(time(0));
// Make Scheduler and admit 4 process
   Scheduler s;
   s.admit();

   s.admit();
 
   s.admit();
 
   s.admit();


// Run Schduler
  s.run();








}






