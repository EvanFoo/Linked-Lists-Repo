/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

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
	
		Double_node <Type> * sentinel_1 = new Double_node<Type>(0, nullptr, nullptr);	
		Double_node <Type> * sentinel_2 = new Double_node<Type>(0, nullptr, nullptr);

		sentinel_1->next_node = sentinel_2;
		sentinel_2 ->previous_node = sentinel_1;

		list_head = sentinel_1;
		list_tail = sentinel_2;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// enter your implementation here
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// enter your implementation here
	return true;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
	return 0;
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
	//need to add some bounds checking for if temporary->previous_node == nullptr 
	//this would mean that it is the first sentinel

	Type to_return = list_head-> next_node -> element;
		
	Double_node<Type> * temporary = list_head->next_node;

	list_head->next_node = temporary -> next_node;

	delete temporary;

	list_size --;


	return to_return;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
	Type to_return = list_tail -> previous_node -> element;

	Double_node<Type> * temporary = list_tail->previous_node;

	list_tail->previous_node = temporary -> previous_node;

	delete temporary;

	return to_return;


}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
	return 0;
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