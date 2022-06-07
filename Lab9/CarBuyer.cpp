// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(){return car4sale_;}

   // lotSize() function returns lot size 
   int lotSize() { return lot_size;}

   // nextCar() function
   Car *nextCar() {

	// Increment next (going to next car)
   	next++;
   	// When next reaches the lot size, it returns to 0
   	 if(next == lot_size) {
		next = 0;
    	}
    	// Create new car option
    	Car *newOption = &car4sale_[next];

    	return newOption;
   }



   // if a car is bought, requests a new one
   Car *buyCar(){ 
      Car *bought = &car4sale_[next];
      car4sale_[next] = 
        *(factories_[rand()%factories_.size()]->requestCar());
      return bought;
  }


private:
   // Holds Lot Size
   static const int lot_size = 10;
   // count for "next" car
   int next;

   Car car4sale_[lot_size]; // lot size cars for sale at the lot
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // Fills the lot with random cars from the factories
   for(int i = 0; i < lot_size; i++) {
   	car4sale_[i] = *(factories_[rand() % factories_.size()] -> requestCar());
   }



}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();



   for(int i = 0; i < carLotPtr->lotSize(); i++) {
   	Car *toBuy = carLotPtr -> nextCar(); 

   	cout << "Jill Toyoter " << id << endl;
   	cout << "test driving " 
		<< toBuy->getMake() << " "
		<< toBuy->getModel();

	// Creates a toyota that has a random model
	Toyota T;


   	if (toBuy->getMake() == "Toyota" && T.getModel() == toBuy->getModel()){
      		cout << " love it! buying it!" << endl;
      		carLotPtr -> buyCar();
		break;
   	} else {
      		cout << " did not like it!" << endl;
   	}
   }



}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();
   

   for(int i = 0; i < carLotPtr->lotSize(); i++) {
      Car *toBuy = carLotPtr -> nextCar();
   
      cout << "Jack Fordman " << id << endl;
      cout << " test driving "
         << toBuy->getMake() << " "
         << toBuy->getModel();
   
      // Create ford with a random model
      Ford F;


      if (toBuy->getMake() == "Ford" && F.getModel() == toBuy->getModel()){
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
	 break;
      } else
         cout << " did not like it!" << endl;

      }



}



int main() {
   srand(time(nullptr));

   const int numBuyers=20;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
	 toyotaLover(i);
      else
	 fordLover(i);
  
}
