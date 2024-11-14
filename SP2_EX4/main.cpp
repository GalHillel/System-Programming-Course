#include <iostream>
#include <string>
#include "src/node.hpp"
#include "src/tree.hpp"
#include "src/complex.hpp"

using namespace std;

int main()
{
    // Double Tree Example
    Node<double> root_double = Node<double>(1.1);
    Tree<double> double_tree;
    double_tree.add_root(root_double);
    Node<double> n1_double = Node<double>(1.2);
    Node<double> n2_double = Node<double>(1.3);
    Node<double> n3_double = Node<double>(1.4);
    Node<double> n4_double = Node<double>(1.5);
    Node<double> n5_double = Node<double>(1.6);

    double_tree.add_sub_node(root_double, n1_double);
    double_tree.add_sub_node(root_double, n2_double);
    double_tree.add_sub_node(n1_double, n3_double);
    double_tree.add_sub_node(n1_double, n4_double);
    double_tree.add_sub_node(n2_double, n5_double);

    // Printing for Double Tree
    cout << "Double Tree:" << endl;
    cout << "Pre-Order Traversal:" << endl;
    for (auto node = double_tree.begin_pre_order(); node != double_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << "Post-Order Traversal:" << endl;
    for (auto node = double_tree.begin_post_order(); node != double_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    cout << "In-Order Traversal:" << endl;
    for (auto node = double_tree.begin_in_order(); node != double_tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    cout << "BFS Traversal:" << endl;
    for (auto node = double_tree.begin_bfs_scan(); node != double_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout << "Range-Based For Loop:" << endl;
    for (auto node : double_tree)
    {
        cout << node << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout << "Double Tree Visualization:" << endl;
    cout << double_tree << endl;

    // Complex Tree Example
    Node<Complex> root_complex = Node<Complex>(Complex(1.1, 2.2));
    Tree<Complex, 3> complex_tree;
    complex_tree.add_root(root_complex);
    Node<Complex> n1_complex = Node<Complex>(Complex(1.2, 2.3));
    Node<Complex> n2_complex = Node<Complex>(Complex(1.3, 2.4));
    Node<Complex> n3_complex = Node<Complex>(Complex(1.4, 2.5));
    Node<Complex> n4_complex = Node<Complex>(Complex(1.5, 2.6));
    Node<Complex> n5_complex = Node<Complex>(Complex(1.6, 2.7));

    complex_tree.add_sub_node(root_complex, n1_complex);
    complex_tree.add_sub_node(root_complex, n2_complex);
    complex_tree.add_sub_node(n1_complex, n3_complex);
    complex_tree.add_sub_node(n1_complex, n4_complex);
    complex_tree.add_sub_node(n2_complex, n5_complex);

    // Printing for Complex Tree
    cout << "\nComplex Tree:" << endl;
    cout << "Pre-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: (1.1 + 2.2i), (1.2 + 2.3i), (1.4 + 2.5i), (1.5 + 2.6i), (1.3 + 2.4i), (1.6 + 2.7i)
    cout << endl;

    cout << "Post-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: (1.4 + 2.5i), (1.5 + 2.6i), (1.2 + 2.3i), (1.6 + 2.7i), (1.3 + 2.4i), (1.1 + 2.2i)
    cout << endl;

    cout << "In-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // prints: (1.4 + 2.5i), (1.2 + 2.3i), (1.5 + 2.6i), (1.1 + 2.2i), (1.3 + 2.4i), (1.6 + 2.7i)
    cout << endl;

    cout << "BFS Traversal:" << endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: (1.1 + 2.2i), (1.2 + 2.3i), (1.3 + 2.4i), (1.4 + 2.5i), (1.5 + 2.6i), (1.6 + 2.7i)
    cout << endl;

    cout << "Range-Based For Loop:" << endl;
    for (auto node : complex_tree)
    {
        cout << node << " ";
    } // same as BFS: (1.1 + 2.2i), (1.2 + 2.3i), (1.3 + 2.4i), (1.4 + 2.5i), (1.5 + 2.6i), (1.6 + 2.7i)
    cout << endl;

    cout << "Complex Tree Visualization:" << endl;
    cout << complex_tree << endl;

    // 4-ary Tree Example
    Node<int> root_int = Node<int>(10);
    Tree<int, 4> int_tree;
    int_tree.add_root(root_int);
    Node<int> n1_int = Node<int>(20);
    Node<int> n2_int = Node<int>(30);
    Node<int> n3_int = Node<int>(40);
    Node<int> n4_int = Node<int>(50);
    Node<int> n5_int = Node<int>(60);
    Node<int> n6_int = Node<int>(70);
    Node<int> n7_int = Node<int>(80);
    Node<int> n8_int = Node<int>(90);
    Node<int> n9_int = Node<int>(100);

    int_tree.add_sub_node(root_int, n1_int);
    int_tree.add_sub_node(root_int, n2_int);
    int_tree.add_sub_node(root_int, n3_int);
    int_tree.add_sub_node(root_int, n4_int);
    int_tree.add_sub_node(n1_int, n5_int);
    int_tree.add_sub_node(n1_int, n6_int);
    int_tree.add_sub_node(n2_int, n7_int);
    int_tree.add_sub_node(n3_int, n8_int);
    int_tree.add_sub_node(n4_int, n9_int);

    // Printing for Integer 4-ary Tree
    cout << "\nInteger K-ary Tree:" << endl;
    cout << "Pre-Order Traversal:" << endl;
    for (auto node = int_tree.begin_pre_order(); node != int_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 10, 20, 60, 70, 30, 80, 40, 90, 50, 100
    cout << endl;

    cout << "Post-Order Traversal:" << endl;
    for (auto node = int_tree.begin_post_order(); node != int_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 60, 70, 20, 80, 30, 90, 40, 100, 50, 10
    cout << endl;

    cout << "In-Order Traversal:" << endl;
    for (auto node = int_tree.begin_in_order(); node != int_tree.end_in_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 60, 20, 70, 10, 80, 30, 40, 90, 50
    cout << endl;

    cout << "BFS Traversal:" << endl;
    for (auto node = int_tree.begin_bfs_scan(); node != int_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 10, 20, 30, 40, 50, 60, 70, 80, 90
    cout << endl;

    cout << "Range-Based For Loop:" << endl;
    for (auto node : int_tree)
    {
        cout << node << " ";
    } // same as BFS: 10, 20, 30, 40, 50, 60, 70, 80, 90
    cout << endl;

    cout << "Integer K-ary Tree Visualization:" << endl;
    cout << int_tree << endl;

    Tree<int> tree;
    Node<int> root(10);
    tree.add_root(root);

    Node<int> child1(20);
    Node<int> child2(30);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    auto heapIterators = tree.myHeap();
    auto heapBegin = heapIterators.first;
    auto heapEnd = heapIterators.second;

    std::cout << "Heap elements in order:" << std::endl;
    for (auto it = heapBegin; it != heapEnd; ++it)
    {
        std::cout << *it << " ";
    }

    return 0;

}
