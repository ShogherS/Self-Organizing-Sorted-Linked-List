#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template <typename T>	// The list is implemented for templates, so that the user can instatntiate it
class List
{
	public:
		List();		// Constructor with no parameters
		List(const List&);	// Copy constructor
		List(List&&);		// Move constructor
		List(std::initializer_list<T>); // Initialaizer list constructor
		List(size_t, const T&);		// Parametric constructor
		~List();		// Dtestructor
		const T& getAt(const int) const; // Getes the value of the node in mentioned possition
		void push_back(const T&);	// Push a node at the end
		void push_front(const T&);	// Push a node at the fornt
		void insertAt(const T&, int);	// Insertes a node at the mentioned possition
		void pop_back();	// Removes a node from the end
		void pop_front();	// Removes a node from the front
		void removeAt(size_t);	// Removes a node from the mentioned possition
		void unique();		// Removes the repeating elements from the container
		size_t size() const;	// Returns the size of the list
		bool empty()const;	// Checks whether the container is empty 
		auto& operator= (const List&);	// Assigns values to the container 
		bool operator== (const List&) const;	// Compares the contents of two lists
		bool operator!= (const List&) const;	// Compares the contents of two lists
		bool operator< (const List&) const;	// Compares the contents of two lists
		bool operator> (const List&) const;	// Compares the contents of two lists
		bool operator<= (const List&) const;	// Compares the contents of two lists
		bool operator>= (const List&) const;	// Compares the contents of two lists
		void merge(List&);	// Merges two lists 
		void traverse(void (*)(const T&), bool forward = true) const;	// Traverses the container it default order
		void traverseSorted(void (*)(const T&), bool assending = true) const;	// Traverses the container in sorted order
		void reverse();
	protected:
		struct Node	// A node struct saves all the data
		{      		Node() :	 // Constructor with parameter
				next{nullptr},
				prev{nullptr},
				lesser{nullptr},
				greater{nullptr}
				{}
			 Node(const T& d) :		// Constructor with a parameter
				data{d},		// The value of the node
				next{nullptr},		// A pointer to the next node
				prev{nullptr},		// A pointer to the previouse node
				lesser{nullptr},	// A pointer to the node with lesser value
				greater{nullptr}	// A pointer to the node with greater value
				{}
			 T data;         // A actual data that seves the node
			 Node* next;     // A pointer to the next node
			 Node* prev;     // A pointer to the previous node
			 Node* lesser;   // A pointer to the node with smaller value
			 Node* greater;  // A pointer to the node with bigger value
		};
	private:
		Node* head;	// A pointer to the start of the list
		Node* tail;	// A pointer to the end of the list
		Node* asc_head;	// A pointer to the node with the minimum value
		Node* desc_head;	// A pointer to the node with the maximum value  
		size_t size_;	// Saves the size of the container
		void putInSortedOrder(Node*);	// Puts the node in sorted order in terms of greater and lesser values
		void clear();	// Removes the container and brings it to the empty state
		void advance(Node*);	// Implements kinde of caching, brings the node one possition to the left
		void removeNode(Node*);	//Removes the mentioned node from the list
};

#endif //LIST_H
