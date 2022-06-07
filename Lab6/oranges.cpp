// selecting oranges
// converting vectors to multimaps
// Conner Montgomery
// 2/24/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

/*
struct Fruit{
   Variety v;
   string color; // red, green or orange
};
*/

int main(){
   srand(time(nullptr));


   multimap<Variety, string> tree;

  int r = rand()%100+1; 
  for(int i=0; i< r; i++) {
	tree.emplace(make_pair(static_cast<Variety>(rand()%3),colors[rand()%3]));
  }
 

   cout << "Colors of the oranges: ";
   for(auto it=tree.lower_bound(static_cast<Variety>(0)); it != tree.upper_bound(static_cast<Variety>(0)); ++it) {
       cout << it->second << ", ";
  }
   cout << endl;

}

