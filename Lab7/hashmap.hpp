
// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014
// Edit by: Conner Montgomery
// Date: March 7, 2022




#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
   DefaultHash(size_t numBuckets = defaultNumBuckets);
   size_t hash(const T& key) const;
   size_t numBuckets() const { return numBuckets_; }

private:
   // default number of buckets in the hash
   static const size_t defaultNumBuckets = 101; 
   size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
   size_t res = 0;
   for (size_t i = 0; i < sizeof(key); ++i) {
      const unsigned char b = 
      *(reinterpret_cast<const unsigned char *>(&key) + i);
      res += b;
   }
   return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{

public:
   typedef pair<const Key, Value> Element;

   // constructor
   // invokes constructors for comparison and hash objects
   hashmap(const Compare& comp = Compare(), 
	   const Hash& hash = Hash());

   Element* find(const Key& x);      // returns pointer to element with key x,
                                     // nullptr if not found
   pair<typename hashmap <Key, Value, Compare, Hash>::Element*,bool> insert(const Element& x);    // inserts the key/value pair 
   pair<typename hashmap <Key, Value, Compare, Hash>::Element*,bool> erase(const Key& x);         // erases element with key x, if exists
   Value& operator[] (const Key& x); // returns reference on value of
                                     // element with key, inserts if does not exist

   void rehash(size_t n);	//rehash function


private:

   // helper function for various searches
   typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

   size_t size_;   // number of elements in the container
   Compare comp_;  // comparison functor, equal_to by default
   Hash hash_;     // hash functor 

   // hash contents: vector of buckets
   // each bucket is a list containing key->value pairs
   vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
   hashmap<Key, Value, Compare, Hash>::hashmap(
   const Compare& comp, const Hash& hash):
   size_(0), comp_(comp), hash_(hash) {
      elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, 
          typename Compare, typename Hash>
   typename list<pair<const Key, Value>>::iterator // return type
   hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

   // look for the key in the bucket
   for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
      if (comp_(it->first, x))
	 return it;

   return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
   typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
   hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

   size_t bucket = hash_.hash(x);
   auto it=findElement(x, bucket);    // use the findElement() helper   

   if (it != elems_[bucket].end())
      // found the element. Return a pointer to it.
      return &(*it); // dereference the iterator to list 
                     // then take the address of list element
   
   else // didn't find the element -- return nullptr
      return nullptr;
}





// finds the element with key x, inserts an



// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap <Key, Value, Compare, Hash>::Element*,bool> hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
//pair<hashmap < key,  Value,  Compare, Hash>::Element*,bool>
   size_t bucket = hash_.hash(x.first);   
   auto it = findElement(x.first, bucket);    // try to find the element
   
   // if not found, insert a new one.
   if (it == elems_[bucket].end()) {
      ++size_;

     	auto t = elems_[bucket].insert(elems_[bucket].end(), x);
	// elems_[bucket].push_back(x);

        return make_pair(&(*t),true);
   } else {
	return make_pair(&(*it),false);
   }

 
}






// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap <Key, Value, Compare, Hash>::Element*,bool> hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

   // returns number of buckets
   size_t bucket = hash_.hash(x);

   // Attempts to find element
   auto f = findElement(x, bucket);
   
   // If f is not equal the the end(), then it found the key
   if(f != elems_[bucket].end()) {
	// Since it is found, the element will be erased and size of elements in container will subtract 1
	--size_;

	// If size is 0, then we reached the end (returns nullptr)
	if(size_ == 0) {
		elems_[bucket].erase(f);
		return make_pair(nullptr, true);
	}

	// Check if next element is in the bucket 
	if(f++ != elems_[bucket].end()) {
		// then erase the element at f-1 (because we just added one to f) and set it equal to current f
		f = elems_[bucket].erase(--f);
		return make_pair(&(*f), true);

	} else {
		f = elems_[bucket].erase(--f);
		// Needs to return iterator in next non-empty bucket
		// Get the next bucket
		int nextBucket = bucket + 1;

		// increases bucket if the bucket is empty
		while(elems_[nextBucket].empty()) {
			nextBucket++;
		}
		f = elems_[nextBucket].begin();
		return make_pair(&(*f), true);

	}


	
   } else {
	// otherwise returns nullptr and false
	return make_pair(nullptr, false);
   }


}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

   Element* found = find(x); // a pointer to the element found or nullptr

   // declares pair of return type of insert function
   pair<typename hashmap <Key, Value, Compare, Hash>::Element*, bool> p;

   // if key is not found, insert a new key and return the pointer to it
   if (found == nullptr) {
 	p = insert(make_pair(x, Value()));
	return(p.first)->second;

   } else {

  	 // Otherwise, if the key exists, simply return the value of the key that was found at the first invocation of find();
   	return found->second;

   }




}





// sets number of buckets in container to n, then rehashes all values
template<typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {

   // Set number of buckets to given size (n)
   hash_ = DefaultHash<Key>(n);


   //  Create temporary hash (elems_) and move resources from original
   auto temp = std::move(elems_);

   // Clear all current elements in elems_ before rehashing (re inserting pairs), after clearing size is 0
   elems_.clear();
   size_ = 0;

   // resize elems_ to fit n buckets
    elems_.resize(n);

   // for each bucket in the temp hash, for each element in each bucket, insert the element back in (rehashes)
   for(auto b: temp) {
	for(auto e: b) {
		insert(e);
	}
   }


}
