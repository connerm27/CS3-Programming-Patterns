
// drink class to be used in Coffee Shack lab
// Conner Montgomery

#include <string>
#include <iostream>
#include <vector>
#include <set>


using std::string; using std::cout; using std::cin;
using std::vector; using std::endl; using std::set;

enum class DrinkType {small, medium, large};

class Drink {
public:
   Drink(DrinkType type = DrinkType::small, int price=0):
                 type_(type), price_(price) {

	 if (type_ == DrinkType::small) {
                size_= "small";
        } else if (type_ == DrinkType::medium) {
                size_ = "medium";
        } else {
                size_ = "large";
        }


   }

   virtual int getPrice() const {

	if (type_ == DrinkType::small) {
                return smallPrice;
        } else if (type_ == DrinkType::medium) {
                return mediumPrice;
        } else {
                return largePrice;
	}

   }

   virtual string getName() const { return size_;  }

   void setCustName(string cName) {name = cName;}
   string getCustName() {return name;}


private: 
   int price_;
   DrinkType type_;
   string size_;

   string name;

   //S/M/L Prices
   int smallPrice = 5;
   int mediumPrice = 7;
   int largePrice = 10;

};





// Decorator 1
class Sugar: public Drink {

public:
   Sugar(const Drink* ingredient): ingredient_(ingredient) {}

   int getPrice() const override { return 1 + ingredient_->getPrice(); }
   string getName() const override {return "Sugar " + ingredient_->getName();}

private:
   const Drink* ingredient_;

};


// Decorator 2
class Cream: public Drink {

public:
   Cream(const Drink* ingredient): ingredient_(ingredient) {}

   int getPrice() const override { return 2 + ingredient_->getPrice(); }
  string getName() const override {return "Cream " + ingredient_->getName();}

private:
   const Drink* ingredient_;




};


// Decorator 3
class MilkFoam: public Drink {

public:
   MilkFoam(const Drink* ingredient): ingredient_(ingredient) {}

   int getPrice() const override { return 3 + ingredient_->getPrice(); }
  string getName() const override {return "MilkFoam " + ingredient_->getName();}

private:
   const Drink* ingredient_;




};



// Vector of drinks that all levels will be able to access
vector <Drink *> drinks;


// #######################################################

// Customer Class

class Customer {

public:
   Customer();
   void notify(Drink *);

  // Getters
  string getName() {return name_;}

  // Setters
  void setName(string name) { name_ = name; }
  void serveCustomer() {hasBeenServed_ = true;}
  bool hasBeenServed() {return hasBeenServed_;}
private:
  // Customers name
  string name_;
  // has the customer been served or not
  bool hasBeenServed_;

};

set <Customer *> customers;

Customer::Customer() : hasBeenServed_(false) {}

//#########################################################

//Barista Class

class Barista {

public:
  Barista(Barista *successor = nullptr): successor_(successor) {}
  // Function Takes an order
  virtual void handleRequest(Customer *c)=0;
  // Customer completed
  void deregisterCustomer(Customer *c) { customers.erase(c); }
  // Notify Customers
  void notifyCustomers();

// protected so we can access it with xBarista type
protected:
  Barista* successor_;


};



class JuniorBarista: public Barista {

public:
   JuniorBarista(Barista *successor = nullptr): Barista(successor) {}
   void handleRequest(Customer *c) override;

};

class SeniorBarista: public Barista {

public:
   SeniorBarista(Barista *successor = nullptr): Barista(successor) {}
   void handleRequest(Customer *c) override;

};

class Manager: public Barista {

public:
   Manager(Barista *successor = nullptr): Barista(successor) {}
   void handleRequest(Customer *c) override;
};


void JuniorBarista::handleRequest(Customer *c) {

   Drink *d;

   cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
   char a;
   cin >> a;

   if(a == 's') {
        d = new Drink(DrinkType::small);
   } else if (a == 'm')  {
        d = new Drink(DrinkType::medium);
   } else if (a == 'l') {
        d = new Drink(DrinkType::large);
   } else {
	cout << "Wrong Drink Type";
   }

  cout << "Do you want anything in your coffee? [y/n] ";
  char b;
  cin >> b;

  // if yes, we must pass off the order to a senior barista, else, junior can handle it
  if( b == 'y') {
        cout << "I will need to call on a Senior Barista to complete this order" << endl;
        // put drink in drinks vector
        drinks.push_back(d);
        // Send to next person in chain of responsibility
        successor_->handleRequest(c);

  } else {
	cout << "As a Junior Barista, I can handle your order..." << endl;
        cout << "What is your name? ";
        string name;
        cin >> name;

        c->setName(name);
        d->setCustName(name);
        cout << "Your total will be $" << d->getPrice() << " , please." << endl;

        cout << "We'll call your name when your order's up!" << endl;
        drinks.push_back(d);
        customers.insert(c);

  }

}

void SeniorBarista::handleRequest(Customer *c) {

   // Get most recent drink in drinks vector
   Drink *d = drinks.back();
   drinks.pop_back();

  // Dialogue
  cout << "As a Senior Barista, I can only put in certain ingredients" << endl;


  char ch = 'z';
  while(ch != 'd' && ch != 'f') {
        cout << "Would you like to add [s]ugar, [c]ream, milk [f]oam, or [d]one? "; 
        cin >> ch;

        if (ch == 's') {
                d = new Sugar(d);
        } else if (ch == 'c') {
                d = new Cream(d);
        }

  }
  // If the customer wants foam, move to Manager in chain of responsible
  if (ch == 'f') {
	cout << "As a Senior Barista, I cannot do milk foam, I will call on my Manager" << endl;
	drinks.push_back(d);
	successor_->handleRequest(c);
  } else {

	cout << "As a Senior  Barista, I can handle your order..." << endl;
        cout << "What is your name? ";
        string name;
        cin >> name;

        c->setName(name);
	d->setCustName(name);
        cout << "Your total will be $" << d->getPrice() << " , please." << endl;

        cout << "We'll call your name when your order's up!" << endl;
        drinks.push_back(d);
        customers.insert(c);

  }



}

void Manager::handleRequest(Customer *c) {

   // Get most recent drink in drinks vector
   Drink *d = drinks.back();
   drinks.pop_back();

  // Dialogue
  cout << "I am the Manager, I will be able to add the milk foam" << endl;
  // add the foam
   d = new MilkFoam(d);

  cout << "I added the Milk Foam, would you like anything else? " << endl;

  char ch = 'z';
  while(ch != 'd') {
        cout << "Would you like to add [s]ugar, [c]ream, milk [f]oam, or [d]one? "; 
        cin >> ch;

        if (ch == 's') {
                d = new Sugar(d);
        } else if (ch == 'c') {
                d = new Cream(d);
        } else if (ch == 'f') {
                d = new MilkFoam(d);
        } 

  }


        cout << "What is your name? ";
        string name;
        cin >> name;

        c->setName(name);
	d->setCustName(name);
        cout << "Your total will be $" << d->getPrice() << " , please." << endl;

        cout << "We'll call your name when your order's up!" << endl;
        drinks.push_back(d);
        customers.insert(c);


}

void Barista::notifyCustomers() {

   Drink *readyDrink = drinks[0];

   cout << readyDrink->getName() << " coffee is ready!" << endl;

  for(auto cust: customers)  {
    cust->notify(readyDrink);
  }
  drinks.erase(drinks.begin());


}

void Customer::notify(Drink * readyDrink) {

   if(readyDrink->getCustName() == name_) {
	hasBeenServed_ = true;
	cout << name_ << " has been served" << endl;
   } 

}


int main() {

   // 4 customers as in assignment

   const int number = 4;
   srand(0);

   // Junior Barista -- 
   JuniorBarista b(new SeniorBarista(new Manager));


   vector <Customer *> allCustomers;
   for(int i=0; i < number; i++) {
	// adds 4 new customers in the "line"
	allCustomers.push_back(new Customer());
   }


   // Keep track of served customers
   int served = 0;

   for(auto a: allCustomers) {
	cout << "Next Customer in Line " << endl;
	b.handleRequest(a);
	// Random probability 
	if(rand()%2 == 0) {
	   b.notifyCustomers();
	   served++;
        }

   }

  // Notify remaining customer
  while(served<number) {
   b.notifyCustomers();
   served++;
  }




}

