// Test Code for Hashmap
// Conner Montgomery
// March 13th, 2022

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout;
using std::endl; using std::string;

int main() {

// Create integer, integer hashmap
hashmap<int, int> h;

//insert values (tests insert)
h.insert(pair<int,int>(30, 60));
h.insert(make_pair(20, 40));
h.insert(make_pair(10, 20));

auto x = h.find(20);
auto y = h.find(30);
auto z = h.find(10);

cout << "Testing Insert: " << endl;

if (x != nullptr) 
	cout << "20 map to " << x->second << endl;
else 
	cout << "cannot find 20 in map" << endl;

if (x != nullptr) 
        cout << "30 map to " << y->second << endl;
else 
     	cout << "cannot find 30 in map" << endl;



if (x != nullptr) 
        cout << "10 map to " << z->second << endl;
else 
     	cout << "cannot find 10 in map" << endl;


cout << "------------" << endl;
cout << "Testing erase: (erasing key 10)" << endl;

h.erase(10);

   auto x2 = h.find(10);
   if (x2 != nullptr)
      cout << "10 maps to " << x2->second << endl;
   else 
      cout << "cannot find 10 in map (successfully removed!)" << endl;
cout << "___________" << endl;

cout << "Testing [] Operator: " << endl;

h[10] = 100;
h[10] = 80;

auto x3 = h.find(10);
if (x3 != nullptr)
      cout << "10 maps to " << x3->second << endl;
   else 
      cout << "cannot find 10 in map" << endl;

cout << "[] operator successful!" << endl;
cout << "__________" << endl;

cout << "Testing Roster of Players on a Sports Team: " << endl;

  hashmap<int, string> roster;

   // entering entries with indexing operator
   roster[7] = "Conner";
   roster[14] = "Brennen";
   roster[18] = "Mason";
   roster[26] = "Matthew";
   roster[27] = "Owen";

   cout << "Enter new player number: "; int num; cin >> num;
   cout << "Enter new player name: "; string name; cin >> name;

   roster[num] = name; // "unsafe" insert

   // searching map
   cout << "Enter player number to look for: (for testing purposes try 7) "; cin >> num;
   auto it = roster.find(num);
   if(it != nullptr)
      cout << it->first << ":" << it->second << endl;
   else
      cout << "player not found" << endl;

   // removing from a map
   cout << "Enter player number to cut from roster: (for testing purposes try 26) "; cin >> num;
   auto removed = roster.erase(num);
   // check if not there
   if (removed.second == true)
      cout << "Player cut successfully" << endl;
   else 
      cout << "Player could not be cut (does not exist)";
cout << "________" << endl;
  // testing rehash
 
   cout << endl << "Testing rehash: " << endl;
   roster.rehash(201);
//   cout << "New number of buckets is " << roster.numBuckets() << endl;

   // testing if hashmap is still correct after rehash
   cout << 27 << ": " << roster[27] << endl;
   cout << 7 << ": " << roster[7] << endl;


}
