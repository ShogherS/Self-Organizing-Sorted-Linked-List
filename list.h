#include <stdexcept>

template <typename T>	// The list is implemented for templates, so that the user can instatntiate it
class List
{
	public:
		List();		// Ctor with no parameters
		List(const List&);	// Copy ctor
		List(List&&);		// Move ctor
		~List();		// Dtor
		const T& getAt(const int) const; // Getes the value of the node in mentioned possition
		void push_back(const T&);	// Push a node at the end
		void push_front(const T&);	// Push a node at the fornt
		void insertAt(const T&, int);	// Insertes a node at the mentioned possition
		void pop_back();	// Removes a node from the end
		void pop_front();	// Removes a node from the front
		void removeAt(size_t);	// Removes a node from the mentioned possition
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
	protected:
		struct Node	// A node struct saves all the data
		{      		Node() :	 // Ctor with parameter
				next{nullptr},
				prev{nullptr},
				lesser{nullptr},
				greater{nullptr}
				{}
			 Node(const T& d) :
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
};

template <typename T>
List<T>::List():	    // Constructor for the List class.
	head{nullptr},	    // Initializes the "head" pointer to nullptr.
	tail{nullptr},	    // Initializes the "tail" pointer to nullptr.
	asc_head{nullptr},    // Initializes the "asc_head" pointer to nullptr.
	desc_head{nullptr},    // Initializes the "desc_head" pointer to nullptr.
	size_{0}    // Initializes the "size_" data member to 0.
{}    // Constructor body is empty, as it's primarily responsible for initialization.

template <typename T>	
List<T>::List(const List& list)		//Constructor for the List class that takes another 
{ 					//List object as a parameter and creates a deep copy of its elements.
	size_t count = 0;    // Initialize a variable "count" to keep track of the elements being copied.
	while (count < list.size()) {    // Use a loop to iterate through each element in the source list "list."
		this->push_back(list.getAt(count)); // Call the "push_back" method to add a copy of the element at index "count"
		++count;	// Increment the "count" variable to move to the next element in the source list
	}		
}

template <typename T>	// Move constructor for the List class that takes an rvalue reference to another List object.
List<T>::List(List&& list)	// This constructor transfers ownership of the source list's resources to the current list.
{
	this->head = list.head;    // Transfer ownership of the "head" pointer from the source list to the current list.
	this->tail = list.tail;		// Transfer ownership of the "tail" pointer from the source list to the current list.
	this->ask_head = list.ask_head;    // Transfer ownership of the "asc_head" pointer from the source list to the current list.
	this->desk_head = list.desk_head;    // Transfer ownership of the "desc_head" pointer from the source list to the current list.
	list.head = nullptr;    // Set the "head" pointer in the source list to nullptr to indicate ownership transfer.
	list.tail = nullptr;    // Set the "tail" pointer in the source list to nullptr to indicate ownership transfer.
	list.desk_head = nullptr;    // Set the "asc_head" pointer in the source list to nullptr to indicate ownership transfer.
	list.ask_head = nullptr;    // Set the "desc_head" pointer in the source list to nullptr to indicate ownership transfer.
}

template <typename T> 	// Destructor for the List class.
List<T>::~List() 	// It's responsible for cleaning up any dynamically allocated memory
{			// and releasing resources held by the List object.
	clear();	// Call the "clear" method to remove all elements from the list
}

template <typename T>
void List<T>::push_front(const T& d)    // Adds a new node with the given data 'd' to the front of the list.
{
	Node* newNode = new Node(d);    // Create a new node with the provided data 'd'.
	if (head) {    // If the list is not empty (head is not nullptr),
		head->prev = newNode;        // Make the previous pointer of the current head point to the new node.
	} else {        // If the list is empty, set the tail pointer to the new node.
		tail = newNode;
	}
	newNode->next = head;    // Make the 'next' pointer of the new node point to the current head.
	head = newNode;    // Update the 'head' pointer to point to the new node, making it the new head.
	putInSortedOrder(newNode);    // Ensure the list remains sorted (assuming this function maintains sorted order).
	++size_;    // Increment the size of the list to reflect the addition of a new node.
}
template <typename T>
void List<T>::push_back(const T& data) {    // Add a new element to the end of the list
	Node* newNode = new Node(data);    // Create a new node with the provided data.
	if (!head) {    // If the list is empty (head is nullptr),
		head = newNode;        // Set both head and tail to point to the new node,
	} else {        // If the list is not empty, set the 'next' pointer of the current tail
		tail->next = newNode;        // to point to the new node, and set the 'prev' pointer of the new node
		newNode->prev = tail;        // to point to the current tail.
	}
	tail = newNode;    // Update the 'tail' pointer to point to the new node, as it's now the last node.
	putInSortedOrder(newNode);    // Ensure the list remains sorted (assuming this function maintains sorted order).
	++size_;    // Increment the size of the list to reflect the addition of a new element.
}

template <typename T>
void List<T>::removeAt(size_t pos)     // Remove the element at the specified position 'pos' in the list.
{
	if (pos >= size_) {    // Check if 'pos' is out of bounds (greater than or equal to the size of the list).
		throw std::invalid_argument("The mentioned argument is invalid");
	}
	if (pos == 0) {    // If 'pos' is 0, it's the first element; use 'pop_front' to remove it.
		pop_front();
	} else if (pos == size_ - 1) {    // If 'pos' is the last element, use 'pop_back' to remove it.
		pop_back();
	} else {    // If 'pos' is somewhere in the middle of the list,
		Node* current = head;        // Traverse the list to find the node at position 'pos'.
		size_t count{};
		while (count < pos) {
			current = current->next;
			++count;
		}
		if (current == asc_head) {        // Update the ascending and descending pointers if necessary.
			asc_head = current->greater;
		}
		if (current == desc_head) {
			desc_head = current->lesser;
		}
		if (current->lesser) {        // Update the pointers of neighboring nodes.
			current->lesser->greater = current->greater;
		}
		if (current->greater) {
			current->greater->lesser = current->lesser;
		}
		current->prev->next = current->next;        // Adjust the pointers to remove 'current' from the linked list.
		current->next->prev = current->prev;
		delete current;        // Deallocate memory for 'current' and set it to nullptr.
		current = nullptr;
		--size_;        // Decrease the size of the list to reflect the removal of an element.
	}
}

template <typename T>
void List<T>::insertAt(const T& d, int pos)    // Insert a new element with the provided data 'd' at the specified position 'pos' in the list.
{
	if (pos < 0 || pos > size_) {    // Check if 'pos' is out of bounds (negative or greater than the size of the list).
		throw std::invalid_argument("The mentioned position is invalid");
	}
	if (pos == 0) {    // If 'pos' is 0, insert the element at the front of the list using 'push_front'.
		return push_front(d);
	}
	if (pos == size_) {    // If 'pos' is equal to the size, insert the element at the end using 'push_back'.
		return push_back(d);
	}
	Node* newNode = new Node(d);    // Create a new node with the provided data.
	Node* current = getAt(pos);    // Find the node at position 'pos' in the list.
	newNode->next = current;    // Update pointers to insert 'newNode' into the list.
	current->prev->next = newNode;
	newNode->prev = current->prev;
	current->prev = newNode;	
	putInSortedOrder(newNode);    // Ensure the list remains sorted (assuming this function maintains sorted order).
	++size_;    // Increment the size of the list to reflect the insertion of a new element.
}

template <typename T>
void List<T>::pop_back()    // Remove the last element from the list.
{
	if (!head) {    // If the list is empty (head is nullptr), there's nothing to remove.
		return;
	}
	if (size_ == 1) {    // If there is only one element in the list, clear the list.
		clear();
	} else {    // If there are multiple elements in the list,
		if (tail == asc_head) {
			asc_head = head->greater;
			if (tail->greater) {            // Update the 'lesser' pointer of the new 'asc_head' node to nullptr.
				tail->greater->lesser = nullptr;
			}
		}
		if (tail == desc_head) {        // Check if the 'tail' node is also the 'desc_head' node.
			desc_head = head->lesser;
			if (tail->lesser) {            // Update the 'greater' pointer of the new 'desc_head' node to nullptr.
				tail->lesser->greater = nullptr;
			}
		}
		if (tail->greater) {        // Update pointers of neighboring nodes.
			tail->greater->lesser = tail->lesser;
		}
		if (tail->lesser) {
			tail->lesser->greater = tail->greater;
		}
		Node* tmp = tail;        // Update the 'tail' pointer to the previous node.
		tail = tail->prev;
		tail->next = nullptr;
		delete tmp;        // Deallocate memory for the removed node and set it to nullptr.
		tmp = nullptr;
		--size_;        // Decrement the size of the list to reflect the removal of an element.
	}
}

template <typename T>
void List<T>::pop_front()    // Remove the first element from the list.
{
	if (!head) {    // If the list is empty (head is nullptr), there's nothing to remove.
		return;
	}
	if (size_ == 1) {    // If there is only one element in the list, clear the list.
		clear();
	} else {    // If there are multiple elements in the list,
		if (asc_head == head) {        // Check if the 'asc_head' node is also the 'head' node.
			asc_head = head->greater;
			if (head->greater) {            // Update the 'lesser' pointer of the new 'asc_head' node to nullptr.
				head->greater->lesser = nullptr;
			}
		}
		if (desc_head == head) {        // Check if the 'desc_head' node is also the 'head' node.
			desc_head = head->lesser;
				if (head->lesser) {
				head->lesser->greater = nullptr;
			}
		}
		if (head->greater) {
			head->greater->lesser = head->lesser;
		}
		if (head->lesser) {
			head->lesser->greater = head->greater;	
		}		
		Node* tmp = head;        // Update the 'head' pointer to the next node.
		head = head->next;
		head->prev = nullptr;
		delete tmp;        // Deallocate memory for the removed node and set it to nullptr.
		tmp = nullptr;
		--size_;        // Decrement the size of the list to reflect the removal of an element.
	}
}

template <typename T>
const T& List<T>::getAt(const int pos) const    // Retrieve the element at the specified position 'pos' in the list.
{
	if ( pos < 0 || pos > size_) {    // Check if 'pos' is out of bounds (negative or greater than the size of the list).
		throw std::invalid_argument("The mentioned position is invalid");
	}
	Node* current = head;    // Initialize a pointer 'current' to the 'head' of the list.
	int count = 0;    // Initialize a counter 'count' to keep track of the current position.
	while (count < pos) {    // Traverse the list to find the node at position 'pos'.
		current = current->next;
		++count;
	}
	return current->data;    // Return a reference to the data stored in the node at position 'pos'.
}

template <typename T>
size_t List<T>::size() const    // Return the current size of the list, which represents the number of elements in it.
{
	return size_;
}

template <typename T>
bool List<T>::empty() const    // Check if the list is empty by evaluating whether its size is equal to 0.
{
	bool isEmpty = size ? true : false;    // Return true if the list is empty; otherwise, return false.
	return isEmpty;
}

template <typename T>
auto& List<T>::operator= (const List& rhs)    // Assignment operator overload for making a deep copy of another List.
{
	if (this != &rhs) {    // Check for self-assignment (comparing the addresses of this object and rhs).
		int count{};
		this->clear();        // Clear the current list to prepare for a deep copy.
		while (count < rhs.size()) {        // Iterate through the elements in the rhs List and copy them to this List.
			this->push_back(rhs.getAt(count));
			++count;
		}	
	}	
	return *this;    // Return a reference to this List after the assignment.
}

template <typename T>
bool List<T>::operator== (const List& rhs) const    // Comparison operator overload to check if two Lists are equal.
{
	if (size_ != rhs.size_) {    // If the sizes of the two Lists are not the same, they cannot be equal.
		return false;
	}
	Node* current = head;    // Initialize pointers 'current' and 'current2' to traverse both Lists.
	Node* current2 = rhs.head;
	while (current && current2) {    // Compare elements of both Lists element by element.
		if (current->data != current2->data) {            // If a mismatch is found, the Lists are not equal.
			return false;
		}
		current = current->next;
		current2 = current2->next;
	}
	return true;    // If both Lists have been traversed without finding any mismatches, they are equal.
}

template <typename T>
bool List<T>::operator!= (const List& rhs) const    // Inequality operator overload to check if two Lists are not equal.
{
	return !(&this == rhs);    // Use the equality operator to determine if the Lists are equal
}

template <typename T>
bool List<T>::operator< (const List& rhs) const    // Less-than operator overload to compare if this List is lexicographically less than another List ('rhs').
{
	Node* current = head;    // Initialize pointers 'current' and 'current2' to traverse both Lists.
	Node* current2 = rhs.head;
	while (current && current2) {    // Iterate through both Lists element by element.
		if (current->data < current2->data) {	// If the current element in this List is less than the corresponding element in 'rhs',
			return true;            // this List is considered lexicographically less.
		}
		if (current->data > current2->data) {            // If the current element in this List is greater than the corresponding element in 'rhs',
			return false;            // this List is considered lexicographically greater.
		}
		current = current->next;
		current2 = current2->next;
	}
    	// If all elements have been compared and no difference is found,
	// this List is considered lexicographically less if it is shorter in size.
	return (!current && current2);
}

template <typename T>
bool List<T>::operator> (const List& rhs) const    // Greater-than operator overload to compare if this List is lexicographically greater than another List ('rhs').
{
	if ( *this == rhs || *this < rhs) {    // Check if this List is equal to 'rhs' or if it is lexicographically less than 'rhs'.
		return false;
	}
	return true;    // If the above conditions are not met, this List is considered lexicographically greater than 'rhs'.
}

template <typename T>
void List<T>::traverse(void(*visit)(const T&), bool forward) const    // Traverse the list and apply the provided 'visit' function to each element.
{
	Node* current = forward ? current = head : current = tail;    // Initialize a pointer 'current' based on the traversal direction.
	while (current) {    // Traverse the list and call the 'visit' function for each element.
	
		visit(current->data);
		forward ? current = current->next : current = current->prev;        // Update 'current' based on the traversal direction.
	}
}

template <typename T>
bool List<T>::operator<= (const List& rhs) const    // Less-than-or-equal-to operator overload to compare if this List is lexicographically less than or equal to another List ('rhs').
{
	if ( *this == rhs || *this < rhs) {    // Check if this List is equal to 'rhs' or if it is lexicographically less than 'rhs'.
		return true;
	}
	return false;    // If the above conditions are not met, this List is considered lexicographically greater than 'rhs'.
}

template <typename T>
bool List<T>::operator>= (const List& rhs) const    // Greater-than-or-equal-to operator overload to compare if this List is lexicographically greater than or equal to another List ('rhs').
{
	if ( !(*this < rhs)) {    // Check if this List is not lexicographically less than 'rhs'.
		return true;
	}
	return false;    // If the above condition is not met, this List is considered lexicographically less than 'rhs'.
}
template <typename T>
void List<T>::merge(List& other)    // Merge the elements of another List ('other') into this List, maintaining sorted order.
{
	if (!tail) {    // If this List is empty (has no 'tail'), simply assign the 'other' List to this List.
		head = other.head;
		tail = other.tail;
		asc_head = other.asc_head;
		desc_head = other.desc_head;
	} else {    // If this List is not empty, append the elements from 'other' to this List while preserving sorted order.
		Node* current = other.head;
		while (current) {
			tail->next = current;            // Append 'current' to the end of this List.
			current->prev = tail;
			tail = tail->next;	
			current = current->next;
			putInSortedOrder(tail);            // Ensure that the newly appended element maintains sorted order in this List.
		}
	}
	other.head = nullptr;    // Clear the 'other' List by resetting its pointers and size.
	other.tail = nullptr;
	other.asc_head = nullptr;
	other.desc_head = nullptr;
	other.size_ = 0;
}

template <typename T>
void List<T>::traverseSorted(void (*visit)(const T& d), bool assending) const    // Traverse the List in sorted order (either ascending or descending) and apply the provided 'visit' function to each element.
{
	Node* current = assending ? asc_head : desc_head;    // Initialize a pointer 'current' based on the sorting order (ascending or descending).
	while (current) {    // Traverse the List while following the specified sorting order and call the 'visit' function for each element.
		visit(current->data);
		current = assending ? current->greater : current->lesser;        // Update 'current' based on the sorting order (ascending or descending).

	}
}

template <typename T>
void List<T>::putInSortedOrder(Node* node)    // Insert the given 'node' into the List while maintaining sorted order.
{
	if (!node) {    // If 'node' is nullptr, there's nothing to insert.
		return;
	}
	if (!asc_head) {    // If the ascending sorted list is empty, set 'asc_head' and 'desc_head' to 'node'.
		return;
	}
	Node* current = asc_head;    // Initialize a pointer 'current' to traverse the ascending sorted list.
	while (current->data < node->data && current->greater) {    // Traverse the ascending sorted list to find the appropriate position for 'node'.
		current = current->greater;
	} 	
	if (current->data < node->data) {    // Check if 'node' should be inserted after 'current'.
		node->lesser = current;
		node->greater = current->greater;
		current->greater = node;
		if (!node->greater) {
			desc_head = node;
		}
	} else {    // Otherwise, 'node' should be inserted before 'current'.
		node->lesser = current->lesser;
		if (current->lesser) {		
			current->lesser->greater = node;
		} else {
			asc_head = node;
		}
		node->greater = current;
		current->lesser = node;
	}
}

template <typename T>
void List<T>::clear() {        // Clear the list by releasing memory for all nodes.
	while (head) {    // Iterate through the list and delete each node.
		Node* tmp{head};
		head = head->next;
		delete tmp;
	}
	asc_head = nullptr;    // Reset pointers and size to indicate an empty list.
	desc_head = nullptr;
	tail = nullptr;
	head = nullptr;
	size_ = 0;
}

template <typename T>
void List<T>::advance(Node* node)    // Move a given 'node' one position forward in the list, maintaining the list's structure.
{
	if (node == head || !node) {    // Check if the provided 'node' is the head of the list or if it is nullptr.
		return;
	}
	Node* lhs = node->prev;    // Retrieve the nodes to the left (lhs) and right (rhs) of the provided 'node'.
	Node*  rhs = node->next;
	if (lhs) {    // If 'lhs' (left neighbor) exists, update its pointers to accommodate 'node'.
		if (lhs->prev) {
			lhs->prev->next = node;
			node->prev = lhs->prev;
		}
		lhs->next = rhs;
		lhs->prev = node;
		node->next = lhs;
		
	} 
	if (rhs) {    // Update the 'prev' pointer of 'rhs' (right neighbor) if it exists.
		rhs->prev = lhs;
	}
	if (lhs == head) {    // Update the 'head' pointer if 'lhs' was the previous head.
		head = node;
	}
	if (node == tail) {    // Update the 'tail' pointer if 'node' was the previous tail.
		tail = lhs;
	} 
}
