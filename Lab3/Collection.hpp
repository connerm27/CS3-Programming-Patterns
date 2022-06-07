// Conner Montgomery
// 2/3/2022
// Collection.hpp


#ifndef COLLECTION
#define COLLECTION

#include <iostream>
#include "list.hpp"

template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T> &, const Collection<T> &);


template <typename T>
class Collection {

public:
	// Default Constructor
	Collection();


	// Add
	void add(T);

	//remove
	void remove(T);

	//last
	T last();

	//print
	void print();

	//Friend function defined at top
	friend bool equal<T>(const Collection&, const Collection&);

private:
	node<T> *node_;
	int size;



};



template <typename T>
Collection<T>::Collection() {

        node_ = NULL;
	size = 0;

}

template <typename T>
void Collection<T>::add(T data) {

// creates new temp node and sets the data to new node added
node<T> *newNode = new node<T>();
newNode->setData(data);

// creates temp node to find the last node
node<T> *lastNode = node_;

//adds node if it is empty
if(node_ == nullptr) {
	node_ = newNode;
} else {

	// traverses collection until it gets to the last node
	while(lastNode->getNext() != nullptr) {
		lastNode = lastNode->getNext();

	}
// sets newnode that has the sent data to the last node in the collection
lastNode->setNext(newNode);
//increases the size counter
size++;

}

}


template <typename T>
void Collection<T>::print() {
	// creates temp node pointing at front of collection
	node<T> *temp = node_;
	// traverses through collection
	while(temp != NULL) {
		// each time it prints the data from the collection
		std::cout << temp->getData() << "\n";
		temp = temp->getNext();
	}

}


template <typename T>
void Collection<T>::remove(T data) {

	// equals head of collection
	node<T> *temp = node_;

	// while the pointer isn't at the end
	while(temp->getNext() != nullptr) {
		// if the data equals the data given
		if(temp->getNext()->getData() == data) {
			// sets the pointer to the next one, therefore removing current item
			temp->setNext(temp->getNext()->getNext());
			//reduces size
			size--;
		} else {
			// goes to next item in collection
			temp = temp->getNext();
		}


	}





 }

template <typename T>
T Collection<T>::last() {


	//creates temp node set to the head of the lsit
	node<T> *lastNode = node_;

		// traverses until it finds the last node
       		while(lastNode->getNext() != nullptr) {
                	lastNode = lastNode->getNext();

        	}
		// returns last
		return lastNode->getData();



}

// friend function definition
template <typename T>
bool equal(const Collection<T> &c1, const Collection<T> &c2) {

	// make sure both collections are the same size
	if(c1.size != c2.size) {
		return false;
	}

	//Creates temp pointers
	node<T> *cNode1 = c1.node_;
	node<T> *cNode2 = c2.node_;

	// loop while both pointers are NOT pointing at nullptr
	while(cNode1 != nullptr && cNode2 != nullptr) {
		//if item in first collection doesn't equal item in second collection at the same place
		if(cNode1->getData() != cNode2->getData()) {
			return false;
		}
		// Goes to next node
		cNode1 = cNode1->getNext();
		cNode2 = cNode2->getNext();

	}

	// If not falses, then it must be equal

	return true;

}




#endif
