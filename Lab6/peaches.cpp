// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;
using namespace std::placeholders;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   // uses generate to assign random values to objects in the basket

   generate(basket.begin(), basket.end(), [&] { 
	Peaches p;
	p.weight = minWeight + 
                   static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
	p.ripe = rand() % 2;
	return p;
    });

   
   // for_each() possibly
   cout << "all peaches"<< endl;
   // for each to return all peaches in the basket
   for_each(basket.begin(), basket.end(), [] (auto it) {
	return it.print();
   });


   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;

/*
   for(auto it=basket.begin(); it != basket.end();)
      if(it->ripe){
	 peck.push_front(std::move(*it));
	 it=basket.erase(it);
      }else
	 ++it;
*/
  // uses remove_copy_if to move and insert contents into peck
  std::remove_copy_if(basket.begin(), basket.end(), std::back_inserter(peck), [] (auto p){return !p.ripe;});

  auto r = remove_if(basket.begin(), basket.end(), [] (auto p) {return p.ripe;});
  basket.erase(r, basket.end());



   // for_each() possibly
/*
   cout << "peaches remainng in the basket"<< endl;
   for(const auto &e: basket) {
      e.print(); 
   }
*/

   // for each to return all peaches in the basket
   cout << "peaches remaining in the basket"<< endl;
   for_each(basket.begin(), basket.end(), [] (auto it) {
        return it.print();
   });

   cout << endl;



   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
/*
   for(const auto &e: peck) {
      e.print();
   }
*/
   // for each to return all peaches in the deck
   for_each(peck.begin(), peck.end(), [] (auto it) {
	return it.print();
  });





   // prints every "space" peach in the peck
   // 
   const int space=3;
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
/*
   auto it=peck.cbegin(); int i = 0;   
   while(it != peck.cend()){
      if(i == space){
	 it->print();
	 i=0;
      }
      ++i; 
      ++it;
   }
*/

//   int num = std::distance(peck.begin(), peck.end());
 // std::advance(std::next(peck.begin(), space), num);

 auto it=peck.cbegin(); int i = 0;   
   while(it != peck.cend()){
      if(i == space){
         it->print();
         i=0;
      }
      ++i; 
      it = std::next(it,1);
   }






   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0; 

   for(auto it=peck.begin(); it != peck.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=peck.erase(it);
      }else
	 ++it;

  // cout << "Weight of jam is: " << jamWeight << endl;

   cout << "Weight of jam is: " << jamWeight << endl;



}


