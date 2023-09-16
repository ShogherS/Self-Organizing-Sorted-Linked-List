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

- `List()`: Default constructor to initialize an empty self-organizing sorted linked list.
- `List(const List&)`: Copy constructor to create a new list by copying elements from another list.
- `List(List&&)`: Move constructor to create a new list by moving elements from another list efficiently.
- `~List()`: Destructor to clear the list and release memory when it goes out of scope.
- `const T& getAt(const int) const`: Retrieve the value of the node at the specified position in the list.
- `void push_back(const T&)`: Add a new element to the end of the list.
- `void push_front(const T&)`: Add a new element to the front of the list.
- `void insertAt(const T&, int)`: Insert a new element at the specified position in the list.
- `void pop_back()`: Remove the last element from the list.
- `void pop_front()`: Remove the first element from the list.
- `void removeAt(size_t)`: Remove an element from a specific position in the list.
- `size_t size() const`: Get the number of elements in the list.
- `bool empty() const`: Check if the list is empty.
- `auto& operator= (const List&)`: Assign values from another list to this list.
- `bool operator== (const List&) const`: Compare the contents of two lists for equality.
- `bool operator!= (const List&) const`: Compare the contents of two lists for inequality.
- `bool operator< (const List&) const`: Compare two lists to determine if this list is less than another.
- `bool operator> (const List&) const`: Compare two lists to determine if this list is greater than another.
- `bool operator<= (const List&) const`: Compare two lists to determine if this list is less than or equal to another.
- `bool operator>= (const List&) const`: Compare two lists to determine if this list is greater than or equal to another.
- `void merge(List&)`: Merge the elements of another list into this list, maintaining sorted order.
- `void traverse(void (*)(const T&), bool forward = true) const`: Traverse the list and perform a custom operation on each element.
- `void traverseSorted(void (*)(const T&), bool ascending = true) const`: Traverse the list in sorted order and perform a custom operation on each element.

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
