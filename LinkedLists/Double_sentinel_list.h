/*****************************************
* Contributors: 
 * Evan Finnigan
 * Forest Finnigan
 * Jon Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"
#include <iostream>

using namespace std;

template <typename Type>
class Double_sentinel_list {
	private:
		Double_node<Type> *list_head;
		Double_node<Type> *list_tail;
		int list_size;

	public:
		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node<Type> *head() const;
		Double_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {

	//allocate space for the head and tail sentinel
	Double_node <Type> * head_sentinal = new Double_node<Type>(-1, nullptr, nullptr);	
	Double_node <Type> * tail_sentinal = new Double_node<Type>(-1, nullptr, nullptr);

	head_sentinal->next_node = tail_sentinal;
	tail_sentinal ->previous_node = head_sentinal;

	list_head = head_sentinal;
	list_tail = tail_sentinal;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	
	//create an empty list first
    Double_node <Type> * sentinel_1 = new Double_node<Type>(-1, nullptr, nullptr);	
	Double_node <Type> * sentinel_2 = new Double_node<Type>(-1, nullptr, nullptr);

	sentinel_1->next_node = sentinel_2;
	sentinel_2 ->previous_node = sentinel_1;

	list_head = sentinel_1;
	list_tail = sentinel_2;

	//push everything in the existing list into the new list
	Double_node <Type> * current = list.list_head;
	for(int i = 0; i < list.list_size; i++){
		current = current -> next_node;
		push_back(current -> element);
	}
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	
	//remove all of the non_sentinel elements with the pop function
	while (!empty()) pop_front();

	//now delete the head and tail sentinels
	delete list_head;
	delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	
	//if the list_size is not 0, then then this will not be set to true
	bool return_value = false;

	if(list_size == 0)
		return_value = true;

	return return_value;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	//get a pointer to the first element in the list
	Double_node<Type> *tmpPtr = list_head->next();
	//return the last element with the retrieve function
    return tmpPtr->retrieve();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	//get a pointer to the last element in the list
	Double_node<Type> * tmpPtr = list_tail->previous();
	//return the last element with the retrieve function
	return tmpPtr->retrieve();
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
	// return the list_head pointer
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
	//return the list_tail pointer
	return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	int returnCount = 0;

	//iterate through the list with a pointer called current
	Double_node <Type> * current = list_head;
	for(int i = 0; i < list_size; i++){
		current = current -> next_node;
		//if the element at the current pointer is the object iterate returnCount
		if(current->element == obj){
			returnCount ++;
		}
	}

	return returnCount;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
	Double_sentinel_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

	Double_node <Type> * temporary = new Double_node<Type>(obj, list_head, list_head->next_node);
	
	//make the first sentinel node point to our new node
	list_head->next_node = temporary;
	
	//make the next node point back to the new node
	temporary -> next_node -> previous_node = temporary;

	list_size++;

}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {

	Double_node <Type> * temporary = new Double_node<Type>(obj, list_tail -> previous_node, list_tail);
	
	//make the last sentinel node point to the new node
	list_tail -> previous_node = temporary;
	
	//make the last node be pointing towards the new node
	temporary ->previous_node ->next_node = temporary;

	list_size++;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
	//if the list size is zero throw an underflow error
	try{
		if(list_size == 0)
			throw underflow();
		//save the value to return later
		Type to_return = list_head-> next_node -> element;
		//save a temporary pointer to delete later
		Double_node<Type> * temporary = list_head->next_node;
		//point list head to the next element
		list_head->next_node = temporary -> next_node;
		//point the next element to list head
		temporary -> next_node -> previous_node = list_head;

		delete temporary;

		list_size --;

		return to_return;
	}catch(underflow & e){
		cout << "Underflow error" << endl;
		return 0;
	}

}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
	
	//if the list is overdrawn throw an error
	try{
		if(list_size == 0)
			throw underflow();
		//save the value to return
		Type to_return = list_tail -> previous_node -> element;
		//save temporary pointer to delete later
		Double_node<Type> * temporary = list_tail->previous_node;
		//point the list tail pointer to the previoius node
		list_tail->previous_node = temporary -> previous_node;
		//point the previous node to the list tail
		temporary -> previous_node ->next_node = list_tail;

		delete temporary;

		list_size -- ;

		return to_return;
	}catch(underflow & e){
		cout << "Underflow error" << endl;
		return 0;
	}


}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	int deleted = 0;
	//if the list is overdrawn, throw an error
	try{
		if(list_size == 0)
			throw underflow();
		//use the pointer current to iterate through the list
		Double_node<Type> * current = list_head;
		for(int i = 0; i < list_size ; i++){
			//if the element of the current pointer is eqaul to the object to delete,
			//iterate the return value,deleted
			//create a temporary node to delete later
			//point the next nodes, previous pointer to current
			//point the next node to current's next node
			if(current->next_node -> element == obj){
				deleted ++;
				Double_node<Type> * temporary = current->next_node;
				current ->next_node->next_node->previous_node = current;
				current ->next_node = current ->next_node ->next_node;
				delete temporary;
				list_size--;	// Must decrement list_size to reflect the deletion
			}else

				current = current->next_node;
			}
	}catch(underflow & e){
		cout << "Underflow error" << endl;
	}
	return deleted;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
