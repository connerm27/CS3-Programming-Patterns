// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Conner Montgomery
// 02/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;  using std::for_each;
using std::count_if; using std::find_if;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};


bool comp(Apples a, Apples b)
{
    return (a.weight < b.weight);
}

double acc(double &x, double y) {
 return x+y;

}



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
/*
   for(auto it = crate.begin(); it != crate.end(); ++it){
      it->weight = minWeight + 
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      it->color = rand() % 2 == 1 ? "green" : "red";
   }
*/
  // Uses generate to create random apple objects and add them to the crate, captures by reference
   generate(crate.begin(), crate.end(), [&] { 
	Apples a;
	a.weight = minWeight + 
                   static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
	a.color = rand() % 2 == 1 ? "green" : "red";
	return a;
   });





    // for_each() possibly
   cout << "all appleas"<< endl;
/*
   for(const auto &e: crate) {
      e.print();
   }
*/
   // uses for_each to print apples
   for_each(crate.begin(), crate.end(), [] (auto it) {
	return it.print();
	});

   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
/*
   int cnt = 0;
   for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
      if(it->weight > toFind) ++cnt;
*/
   // Uses count_if to determine num of apples greater than given weight
   int cnt = count_if(crate.begin(), crate.end(), [toFind] (auto it) { return it.weight >  toFind; });


   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;


   // find_if()
//   cout << "at positions ";
/*
   for(int i=0; i < size; ++i)
      if(crate[i].weight > toFind)
	 cout << i << ", ";
   cout << endl;
*/

  // Uses find_if to print positions of heavier apples
  auto it =  find_if(crate.begin(), crate.end(), [&] (auto x) { return x.weight > toFind;});

  if(it != crate.end()){
      cout << "at positions ";
      do{
         cout << it - crate.begin() << " ";
         it=find_if(++it, crate.end(), [&] (auto s){ return s.weight > toFind;});
      } while(it != crate.end());
   }


   // max_element()
/*
   double heaviest = crate[0].weight;
   for(int i=1; i < size; ++i)
      if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
*/

 // Finds the maximum element
 auto h = std::max_element(crate.begin(), crate.end(), comp);
  
 cout << "Heaviest apple weighs: " << h->weight << " oz" << endl;


   // for_each() or accumulate()
/*
   double sum = 0;
   for(int i=0; i < size; ++i)
      sum += crate[i].weight;
*/
// uses accumulate to add up the weight of all the apples 
double d = 0;
cout << "Total apple weight is: " << std::accumulate(crate.begin(), crate.end(), d,
    [](double sum, auto it) { return sum + it.weight; }) << " oz" << endl;




   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
/*
   for(int i=0; i < crate.size(); ++i)
      crate[i].weight += toGrow;
*/
  // uses transform to add toGrow value
  transform(crate.begin(), crate.end(), crate.begin(),  
    [&] (auto t) { 
	t.weight = t.weight + toGrow;
	return t; });  




   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
/*   
   for(auto it=crate.begin(); it != crate.end(); )
      if(it->weight < minAccept)
	 it = crate.erase(it);
      else
	 ++it;
*/
 //uses remove_if to remove elements under accepted value.  uses remove/erase idiom
 auto rit = remove_if(crate.begin(), crate.end(), [minAccept] (auto x) {return x.weight < minAccept;});
 crate.erase(rit, crate.end()); 
   cout << "removed " << size - crate.size() << " elements" << endl;


   // bubble sort, replace with sort()

/*
   bool swapped;
   do{
      swapped = false;
      for(int i=0; i < crate.size()-1; ++i)
	 if(crate[i].weight > crate[i+1].weight){
	    std::swap(crate[i], crate[i+1]);
	    swapped = true;
	 }
   }while(swapped);
*/
// uses sort, and comp function to compare apple objects i implemented earlier
std::sort(crate.begin(), crate.end(), comp);

   // for_each() possibly

/*
   cout << "sorted remaining apples"<< endl;
   for(const auto &e: crate) {
      e.print();
   }
*/

// uses for_each to print apples
   for_each(crate.begin(), crate.end(), [] (auto it) {
        return it.print();
        });


}

