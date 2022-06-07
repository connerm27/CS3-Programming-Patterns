// Conner Montgomery
// Lab 12

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;
using std::stack; using std::to_string;





// Memento class below
class Memento;






// receiver
class Document {
public:

   Document(const vector <string> & lines={}): lines_(lines){}

   // actions
   void insert(int line, const string &str) {
      const int index = line-1;
      if (index <= lines_.size())
	 lines_.insert(lines_.begin() + index, str); 
      else
	 cout << "line out of range" << endl; 
   }

   string remove(int line) {
      const int index = line-1;
      string deletedLine="";
      if(index < lines_.size()){
	 deletedLine = lines_[index];
	 lines_.erase(lines_.begin() + index); 
      }else
	 cout << "line out of range" << endl; 
      return deletedLine;
   } 

   void show() {
      for(int i = 0; i < lines_.size(); ++i)
	 cout << i + 1 << ". " << lines_[i] << endl; 
   }


   // Returns line count, size of vector
   size_t getLineCount() { return lines_.size(); }


  Memento* createMemento () const;
  void restoreState (Memento*);

private:
   vector<string> lines_; 
};






 

// abstract command
class Command{
public:
   Command(Document *doc) : doc_(doc){}
   virtual void execute() = 0; 
   virtual void unexecute() = 0; 
   virtual string getAction() =0;
   virtual ~Command(){}
protected:
   Document *doc_; 
}; 

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line, const string &str): 
      Command(doc), line_(line),  str_(str) {}
   void execute() override { doc_->insert(line_, str_);}
   void unexecute() override {doc_->remove(line_);}
   string getAction() override {return "inserted \"" + str_ + "\" at line " +  to_string(line_);}
private:
   int line_; 
   string str_; 
}; 


class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line): 
      Command(doc), line_(line), str_("") {}
   void execute() override {str_ = doc_->remove(line_);}
   void unexecute() override {doc_-> insert(line_, str_);}
   string getAction() override {return "erased line " + to_string(line_);}
private:
   int line_;
   string str_;
};

// client

class DocumentWithHistory{
public:
   DocumentWithHistory(Document *d) : doc_(d){}
   
   bool insert(int line, string str) {
	if(line > doc_->getLineCount() ) {
		cout << "Line out of range" << endl;
		return false;
	}

      Command *com = new InsertCommand(doc_, line, str); 
      com->execute(); 
      doneCommands_.push(com);
	return true; 
   }

   void erase(int line){
      Command *com = new EraseCommand(doc_, line);
      com->execute();
      doneCommands_.push(com);
   }

   void undo() {
      if(doneCommands_.size() != 0) {
	 Command *com = doneCommands_.top(); 
	 doneCommands_.pop(); 
	 com->unexecute();
	 delete com; // don't forget to delete command
      }else
	 cout << "no commands to undo" << endl; 
   }

   void show() {doc_->show();}

   // New
   // Saves current state of document 
   void saveState() {
	// save state as memento
	checkpoint = doc_->createMemento();

   }

   // Restores the state of the document
   void restoreState() {
	if(checkpoint) {
		doc_->restoreState(checkpoint);
		// gets rid of all commands on the stack
		while(!doneCommands_.empty()) {
			doneCommands_.pop();
		}
        } else {
		cout << "No Saved State" << endl;

        }
   }

   // Gets the history of the document
   string getHis() {
	string docHistory = "";
	int counter = 0;

	// Create a copy of the command stack, pop each command and print
	stack<Command*> commandCopy(doneCommands_);
	while(!commandCopy.empty()) {
		counter++;
		docHistory += to_string(counter) + ".) ";
		docHistory += commandCopy.top()->getAction() + "\n";
		commandCopy.pop();
        }

	return docHistory;

   }

   // Redoes last action
   void redo(const size_t r) {

	// when the counter reaches the command number to redo, add the command to the top 
	int counter = 0;
	stack<Command *> commandCopy(doneCommands_);
	while (!commandCopy.empty()) {
		counter++;
		if(counter == r) {
			Command *c = doneCommands_.top();
			c->execute();
			doneCommands_.push(c);
			break;
    		}
		commandCopy.pop();
	}
	

    }

   // get number of commands completed
   size_t numCommands() { return doneCommands_.size(); }


private:
   Document *doc_;
   stack<Command*> doneCommands_; 
   Memento* checkpoint;
  
}; 



// Memento class below
class Memento {
public:
   Memento(const Document& doc): doc_(doc) {}
   const Document& getState() const {return doc_;}  
private:
   const Document doc_;
};


void Document::restoreState(Memento *mem) {
  *this = mem->getState();  // copying back
}

Memento* Document::createMemento() const {
  // copying the Document itself
  return new Memento(*this);
}






// invoker
int main() {

  const vector<string> text = {
	 "Lorem Ipsum is simply dummy text of the printing and typesetting",
	 "industry. Lorem Ipsum has been the industry's standard dummy text",
	 "ever since the 1500s, when an unknown printer took a galley of",
	 "type and scrambled it to make a type specimen book. It has",
	 "survived five centuries."};


   Document doc(text);
   DocumentWithHistory his(&doc);

   char option;
   do{
      his.show(); 
      cout << endl;

     static Memento *checkpoint = nullptr;


      cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last, (c)heckpoint, roll(b)ack, (h)history (r)edo command:";

      cin >> option; 

      int line; string str; 
      switch(option) {
      case 'i':
	 cout << "line number to insert: "; 
	 cin >> line; 
	 cout << "line to insert: "; 
	 cin.get(); // removes end-of-line character so getline() works correctly
	 getline(cin, str); 
	 his.insert(line, str); 
	 break;
 
      case 'e':
	 cout << "line number to remove: ";
	 cin >> line;
	 his.erase(line);
	 break;

      case 'u':
	 his.undo(); 
	 break;

      case 'c':
	 his.saveState();
	 break;

      case 'r':
	 if(his.numCommands() == 0) {
		cout << "No commands available to redo! " << endl;
	 } else {
		size_t line;
		cout << his.getHis() << endl;
		cout << "Which command to redo? ";
		cin >> line;
		his.redo(line);
	}
         break;

     case 'b':
	his.restoreState();
	break;

     case 'h':
	cout << his.getHis() << endl;
	break; 
      }

   }while(option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'r' || option == 'b' || option == 'h');
}
