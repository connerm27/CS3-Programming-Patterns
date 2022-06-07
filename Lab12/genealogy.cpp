// traversing genealogical tree using Composite and Visitors
// Conner Montgomery
// Lab 12



#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string; 
using std::vector;
using std::cin;

class Person{ // component
public:
   Person(string firstName, Person *spouse, Person *father, Person *mother):
      firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
   const string & getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}
   Person *getMother() {return mother_;}
   virtual void accept(class PersonVisitor *)=0;  
   virtual ~Person(){}
private:
   const string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};


// leaf
// man has a last name 
class Man: public Person{
public:
   Man(string lastName, string firstName, Person *spouse, 
       Person *father, Person *mother): 
      lastName_(lastName), 
      Person(firstName, spouse, father, mother){}
   const string & getLastName(){return lastName_;}
   void accept(class PersonVisitor *visitor) override;
private:
   const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
   Woman(vector<Person *> children, 
       string firstName, 
       Person *spouse, 
       Person *father, Person *mother): 
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren() {return children_;}
   void setChildren(const vector<Person *> &children){ children_ = children;}
   void accept(class PersonVisitor *visitor) override;
private:
   vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*)=0;
   virtual void visit(Woman*)=0;
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

   visitor->visit(this);
   
   // traversing descendants
   for(auto child : children_) 
      child->accept(visitor);   
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << " " << m->getLastName() << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << " ";
      if (w->getSpouse() != nullptr)
	 cout << static_cast<Man *>(w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 cout << static_cast<Man *> (w->getFather())->getLastName();
      else
	 cout << "Doe";
      cout << endl;
   }
};


class ChildrenPrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << ": ";
      Woman *spouse = static_cast<Woman *>(m->getSpouse());
      if(spouse != nullptr)
	 printNames(spouse->getChildren());
      cout << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << ": ";
      printNames(w->getChildren());
      cout << endl;
   }
private:
   void printNames(const vector<Person *> &children){
      for(const auto c: children)
	 cout << c->getFirstName() << ", ";
   }
};


class FindPersonVisitor : public PersonVisitor {
public:
  FindPersonVisitor(string firstName, string lastName) :
    firstName_(firstName),
    lastName_(lastName),
    toFind(nullptr) {}

  void visit(Man *m) override {
    if (m->getFirstName() == firstName_ && m->getLastName() == lastName_)
      toFind = m;
  }
  void visit(Woman *w) override {
    string tempLastName = "";
    if (w->getFirstName() == firstName_) {
      if (w->getSpouse() != nullptr)
        tempLastName = static_cast<Man*>(w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
        tempLastName = static_cast<Man*>(w->getFather())->getLastName();
      else
        tempLastName = "Doe";
    }
    if (tempLastName == lastName_) {
      toFind = w;
    }
  }

 
  

  Person* getFound() { return toFind; }

private:
  const string firstName_;
  const string lastName_;
  Person* toFind;
};

class FindRelated: public PersonVisitor {

public:


   FindRelated(Person *a, Person *b) : a_(a), b_(b) {}


   void visit(Man *m) override {

   }

   void visit(Woman *w) override {

   }


   bool isRelated();



private:

   Person *a_;
   Person *b_;


};

bool FindRelated::isRelated() {


   // If both are the same person, function should return true
   if(a_ == b_) {
	return true;
   }


   // if sibilings 
  if(a_->getMother() == b_->getMother()) {
  	return true;
  }

  // If parent-child relationship
  if(a_->getMother() == b_ || a_->getFather() == b_) {
	return true;
  }

  if(b_->getMother() == a_ || b_->getFather() == a_) {
	return true;
  }


  // Aunts and Uncles
  Woman* mother = static_cast<Woman*>(a_->getMother());
  if (mother != nullptr) {
    if (mother->getMother() != nullptr) {
      Woman* grandMother = static_cast<Woman*>(mother->getMother());
      vector<Person*> auntsAndUncles = grandMother->getChildren();
      for (Person* temp : auntsAndUncles) {
        if (b_ == temp) return true;
      }
    }
  }

  return false;

}


// demonstrating the operation
int main(){

   // setting up the genealogical tree      
   // the tree is as follows
   //    
   //
   //       James Smith  <--spouse-->   Mary 
   //	                                  |
   //	                                 children -------------------------
   //	                                  |              |                |
   //	                                  |              |                |
   //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //	                                  |
   //	                                 children------------
   //	                                  |                 |
   //                                     |                 |
   //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
   //	       |
   //	     children
   //	       |
   //          |
   //	     Susan


   // first generation
   Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
   Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
   ms->setSpouse(js); js->setSpouse(ms);

   // second generation
   Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
   Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
   ps->setSpouse(wj); wj->setSpouse(ps);

   vector<Person *> marysKids  = {ps,
			          new Man("Smith", "Robert", nullptr, js, ms),
			          new Woman({}, "Linda", nullptr, js, ms)};
   ms->setChildren(marysKids);

   // third generation
   Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
   vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
   ps->setChildren(patsKids);

   Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
   vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

   jj->setSpouse(mj); mj->setSpouse(jj);
   jj->setChildren(jensKids);
   

   // defining two visitors
   ChildrenPrinter *cp = new ChildrenPrinter;
   NamePrinter *np = new NamePrinter;

   // executing the traversal with the composite
   // and the specific visitor
   /*
   cout << "\nNAME LIST\n";
   ms->accept(np);
   cout << endl << endl;
   */
   
   cout << "CHILDREN LIST\n";
   ms->accept(cp);

   
   cout << "\nJAMES' CHILDREN\n";
   js->accept(cp);



   // My code
   cout << "Enter first candidate: ";
   string first;
   std::getline(std::cin, first);

   string f1 = first.substr(0, first.find(' '));
   string l1 = first.substr(first.find(' ')+1, first.length());

   FindPersonVisitor *find1 = new FindPersonVisitor(f1, l1);
   ms->accept(find1);
   js->accept(find1);
   wj->accept(find1);
   jj->accept(find1); 
  Person *p1 = find1->getFound();

//  cout << p1->getFirstName() <<  endl;

   // Second Candidate

   cout << "Enter second candidate: ";
   string second;
   std::getline(std::cin, second);

   string f2 = second.substr(0, second.find(' '));
   string l2 = second.substr(second.find(' ')+1, second.length());

   FindPersonVisitor *find2 = new FindPersonVisitor(f2, l2);
   ms->accept(find2);
   js->accept(find2);
   wj->accept(find2);
   jj->accept(find2);   
   Person *p2 = find2->getFound();

  // cout << p2->getFirstName() << endl;

   FindRelated *fr = new FindRelated(p1, p2);
   if(fr->isRelated() == true) {
	cout << "Closely Related" << endl;
   } else {
	cout << "Just Friends." << endl;
   }



}
