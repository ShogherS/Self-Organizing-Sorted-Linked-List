# Self-Organizing-Sorted-Linked-List
This C++ code provides an implementation of a self organized linked list using templates. 
It allows you to create, manage, and manipulate a linked list of elements of any data type.

## Table of Contents

- [List Class](#list-class)
  - [Methods](#methods)
- [Usage and Examples](#usage)
- [Contributing](#contributing)

## List Class

The `List` class is the core of this self-organizing sorted linked list implementation. It provides various methods to manipulate and access the elements in the list.

### Methods

### List Member Functions 

1. **List();**
   - *Description:* Constructor with no parameters.
   
2. **List(const List&);**
   - *Description:* Copy constructor. Creates a new list by copying the elements from an existing list.

3. **List(List&&);**
   - *Description:* Move constructor. Creates a new list by moving the elements from an existing list, which can be more efficient than copying.

4. **List(std::initializer_list<T>);**
   - *Description:* Initializer list constructor. Creates a list from an initializer list, allowing you to initialize the list with a set of elements in a single statement.

5. **List(size_t, const T&);**
   - *Description:* Parametric constructor. Creates a list with a specified number of elements, all initialized to a given value.

6. **~List();**
   - *Description:* Destructor. Cleans up the memory used by the list when it goes out of scope or is explicitly deleted.

7. **const T& getAt(const int) const;**
   - *Description:* Retrieves the value of the node at the specified position in the list.

8. **void push_back(const T&);**
   - *Description:* Appends a new node with the provided value to the end of the list.

9. **void push_front(const T&);**
   - *Description:* Inserts a new node with the provided value at the beginning of the list.

10. **void insertAt(const T&, int);**
    - *Description:* Inserts a new node with the provided value at the specified position in the list.

11. **void pop_back();**
    - *Description:* Removes the last node from the list.

12. **void pop_front();**
    - *Description:* Removes the first node from the list.

13. **void removeAt(size_t);**
    - *Description:* Removes the node at the specified position in the list.

14. **void unique();**
    - *Description:* Removes repeating elements from the container, leaving only unique elements.

15. **size_t size() const;**
    - *Description:* Returns the number of elements in the list.

16. **bool empty() const;**
    - *Description:* Checks whether the container is empty (contains no elements).

17. **auto& operator= (const List&);**
    - *Description:* Assigns values from another list to the container.

18. **bool operator== (const List&) const;**
    - *Description:* Compares the contents of two lists for equality.

19. **bool operator!= (const List&) const;**
    - *Description:* Compares the contents of two lists for inequality.

20. **bool operator< (const List&) const;**
    - *Description:* Compares the contents of two lists to determine if one is less than the other.

21. **bool operator> (const List&) const;**
    - *Description:* Compares the contents of two lists to determine if one is greater than the other.

22. **bool operator<= (const List&) const;**
    - *Description:* Compares the contents of two lists to determine if one is less than or equal to the other.

23. **bool operator>= (const List&) const;**
    - *Description:* Compares the contents of two lists to determine if one is greater than or equal to the other.

24. **void merge(List&);**
    - *Description:* Merges the elements of two lists into one list.

25. **void traverse(void (*)(const T&), bool forward = true) const;**
    - *Description:* Traverses the container and applies a provided function to each element. By default, it traverses in the forward direction.

26. **void traverseSorted(void (*)(const T&), bool ascending = true) const;**
    - *Description:* Traverses the container in sorted order and applies a provided function to each element. By default, it traverses in ascending order.

27. **void reverse();**
    - *Description:* Reverses the order of elements in the list.

These member functions provide various operations and utilities for working with a self-organized linked list, allowing you to manipulate and access the data within the list efficiently.
Here's a description of the `Node` struct and its member variables for your self-organized linked list class:

### Node Struct

1. **struct Node**
   - *Description:* The `Node` struct represents a node in the linked list. It stores all the data and maintains pointers to adjacent nodes with respect to their values.

2. **Node() :**
   - *Description:* Constructor with no parameters for the `Node` struct. Initializes the node with default values, setting all pointers to `nullptr`.

3. **Node(const T& d) :**
   - *Description:* Constructor with a parameter for the `Node` struct. Initializes the node with the provided data value `d`. It also sets all pointers to `nullptr`.

### Member Variables within the Node Struct

4. **T data;**
   - *Description:* `data` represents the actual data stored in the node. It holds the value associated with the node.

5. **Node* next;**
   - *Description:* `next` is a pointer to the next node in the linked list, allowing traversal in the forward direction.

6. **Node* prev;**
   - *Description:* `prev` is a pointer to the previous node in the linked list, enabling traversal in the reverse direction.

7. **Node* lesser;**
   - *Description:* `lesser` is a pointer to the node with a smaller value than the current node. It helps maintain the self-organizing property of the linked list.

8. **Node* greater;**
   - *Description:* `greater` is a pointer to the node with a greater value than the current node. Similar to `lesser`, it aids in preserving the self-organizing nature of the list.

The `Node` struct encapsulates the fundamental elements of a node in your self-organized linked list. It stores the actual data, maintains connections to adjacent nodes, and assists in organizing the list based on the values of the nodes. These members and constructors collectively enable the list to efficiently organize, access, and manipulate its elements.
### Private Member Variables

1. **Node* head;**
   - *Description:* A pointer to the start of the list, pointing to the first node.

2. **Node* tail;**
   - *Description:* A pointer to the end of the list, pointing to the last node.

3. **Node* asc_head;**
   - *Description:* A pointer to the node with the minimum value in the list.

4. **Node* desc_head;**
   - *Description:* A pointer to the node with the maximum value in the list.

5. **size_t size_;**
   - *Description:* Saves the current size of the container, indicating the number of elements it contains.

### Private Member Functions

6. **void putInSortedOrder(Node*);**
   - *Description:* Puts the node in sorted order in terms of greater and lesser values. This function maintains the self-organizing property of the list by rearranging nodes as necessary.

7. **void clear();**
   - *Description:* Removes all nodes in the container, effectively bringing it to an empty state. This function deallocates memory and frees resources used by the list.

8. **void advance(Node*);**
   - *Description:* Implements a form of caching by bringing the specified node one position to the left. This function is used to optimize frequently accessed elements, making them closer to the front of the list.

9. **void removeNode(Node*);**
   - *Description:* Removes the specified node from the list. This function is used to delete a specific node when needed, maintaining the integrity of the linked list structure.

These private member variables and functions are essential for the internal operations of the linked list and help in maintaining the list's self-organizing behavior, memory management, and structural integrity. They are not intended to be directly accessed or used externally but play a critical role in supporting the public member functions of the `List` class.
## Usage and Examples

You can use this self-organizing sorted linked list implementation to efficiently manage and manipulate collections of elements. Here's a basic example of how to use it:

```cpp
#include "List.h"

int main() {
    // Create a self-organizing sorted linked list of integers
    List<int> myList;

    // Add elements to the list
    myList.push_back(10);
    myList.push_back(5);
    myList.push_back(20);
    
    // Display the elements in the list
    myList.traverse([](const int& value) {
        std::cout << value << " ";
    });

    return 0;
}

```


### Contributing

If you would like to contribute to this project or report issues, please feel free to create a pull request or submit an issue on GitHub.
