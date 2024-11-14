
# Tree Container with STL, Templates, and Iterators

## Overview

This project implements a k-ary tree container using STL, templates, and iterators. It supports various types of iterators and provides methods to manipulate and traverse the tree. The project includes a demonstration of the tree container using complex numbers and comprehensive tests to ensure its functionality.

## Structure

```
tree
.
├── main.cpp
├── Makefile
├── README.md
├── src
│   ├── complex.hpp
│   ├── node.hpp
│   └── tree.hpp
└── tests
    ├── doctest.h
    └── test.cpp
```

### Files

- **main.cpp**: Demonstrates how the tree container works.
- **Makefile**: Builds the project.
- **README.md**: This file.
- **src/complex.hpp**: Defines the `Complex` class.
- **src/node.hpp**: Defines the `Node` class template.
- **src/tree.hpp**: Defines the `Tree` class template and iterator classes.
- **tests/doctest.h**: Testing framework header.
- **tests/test.cpp**: Contains test cases for the tree container.

## Class Hierarchy

### Complex Class (complex.hpp)

The `Complex` class represents a complex number with real and imaginary parts. It supports addition, equality comparison, and greater-than comparison.

- **Complex(double r = 0.0, double i = 0.0)**: Constructor to initialize a complex number.
- **Complex operator+(const Complex &other) const**: Overloaded addition operator.
- **friend std::ostream &operator<<(std::ostream &os, const Complex &comp)**: Overloaded stream insertion operator for printing.
- **bool operator==(const Complex &other) const**: Overloaded equality operator.
- **bool operator>(const Complex &other) const**: Overloaded greater-than operator.

### Node Class (node.hpp)

The `Node` class template represents a node in the k-ary tree.

- **Node(T val)**: Constructor to initialize a node with a value.
- **T get_value() const**: Returns the value of the node.

### Tree Class (tree.hpp)

The `Tree` class template represents a k-ary tree container. It supports various types of iterators for tree traversal.

- **Tree()**: Constructor to initialize an empty tree.
- **~Tree()**: Destructor to delete the entire tree.
- **void add_root(Node<T> &node)**: Adds a root node to the tree.
- **void add_sub_node(Node<T> &parent_node, Node<T> &child_node)**: Adds a child node to a parent node in the tree.
- **std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, T value)**: Finds a node in the tree with the specified value.
- **PreOrderIter begin_pre_order() const**: Returns a pre-order iterator to the beginning of the tree.
- **PreOrderIter end_pre_order() const**: Returns a pre-order iterator to the end of the tree.
- **PostOrderIter begin_post_order() const**: Returns a post-order iterator to the beginning of the tree.
- **PostOrderIter end_post_order() const**: Returns a post-order iterator to the end of the tree.
- **InOrderIter begin_in_order() const**: Returns an in-order iterator to the beginning of the tree.
- **InOrderIter end_in_order() const**: Returns an in-order iterator to the end of the tree.
- **BFSIter begin_bfs_scan() const**: Returns a BFS iterator to the beginning of the tree.
- **BFSIter end_bfs_scan() const**: Returns a BFS iterator to the end of the tree.
- **DFSIter begin_dfs_scan() const**: Returns a DFS iterator to the beginning of the tree.
- **DFSIter end_dfs_scan() const**: Returns a DFS iterator to the end of the tree.
- **HeapIter begin_heap() const**: Returns a heap iterator to the beginning of the tree.
- **HeapIter end_heap() const**: Returns a heap iterator to the end of the tree.
- **BFSIter begin() const**: Returns a BFS iterator for range-based for loop support.
- **BFSIter end() const**: Returns a BFS iterator for range-based for loop support.
- **void clearTree(std::shared_ptr<Node<T>> &node)**: Recursively deletes the entire tree.
- **friend std::ostream &operator<<(std::ostream &os, const Tree<T, K> &tree)**: Overloaded stream insertion operator for printing the tree.
- **void printTree(std::ostream &os, std::shared_ptr<Node<T>> node, std::string prefix, bool isLeft) const**: Prints the tree structure recursively.

### Iterator Classes

- **PreOrderIterator**: Implements pre-order traversal.
- **PostOrderIterator**: Implements post-order traversal.
- **InOrderIterator**: Implements in-order traversal.
- **BFSIterator**: Implements BFS traversal.
- **DFSIterator**: Implements DFS traversal.
- **HeapIterator**: Implements heap traversal.

## Libraries Used

- **Standard Template Library (STL)**: Used for various container classes and algorithms.
- **doctest**: A light and feature-rich C++98/C++11 single-header testing framework for unit tests.

## Usage

### Building the Project

To build the project, run the following command:

```bash
make
```

### Running the Demonstration

To run the demonstration program, execute:

```bash
make tree
```

### Running the Tests

To run the tests, execute:

```bash
make test
```