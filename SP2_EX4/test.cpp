#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "tests/doctest.h"
#include "src/complex.hpp"
#include "src/node.hpp"
#include "src/tree.hpp"

// Test cases for Complex class
TEST_CASE("Complex Class Tests")
{
    SUBCASE("Default Constructor")
    {
        Complex c;
        CHECK(c.getReal() == doctest::Approx(0.0));
        CHECK(c.getImag() == doctest::Approx(0.0));
    }

    SUBCASE("Parameterized Constructor")
    {
        Complex c(1.0, 2.0);
        CHECK(c.getReal() == doctest::Approx(1.0));
        CHECK(c.getImag() == doctest::Approx(2.0));
    }

    SUBCASE("Copy Constructor")
    {
        Complex c1(1.0, 2.0);
        Complex c2 = c1;
        CHECK(c2.getReal() == doctest::Approx(1.0));
        CHECK(c2.getImag() == doctest::Approx(2.0));
    }

    SUBCASE("Addition Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(3.0, 4.0);
        Complex result = c1 + c2;
        CHECK(result.getReal() == doctest::Approx(4.0));
        CHECK(result.getImag() == doctest::Approx(6.0));
    }

    SUBCASE("Equality Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 2.0);
        CHECK(c1 == c2);
    }

    SUBCASE("Inequality Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        CHECK(c1 != c2);
    }

    SUBCASE("Greater Than Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        CHECK(c2 > c1);
    }

    SUBCASE("Less Than Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        CHECK(c1 < c2);
    }

    SUBCASE("Greater or Equal Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        Complex c3(1.0, 2.0);
        CHECK(c2 >= c1);
        CHECK(c1 >= c3);
    }

    SUBCASE("Less or Equal Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        Complex c3(1.0, 2.0);
        CHECK(c1 <= c2);
        CHECK(c1 <= c3);
    }
}

// Test cases for Node class
TEST_CASE("Node Class Tests")
{
    SUBCASE("Constructor and Value Access")
    {
        Node<int> node(10);
        CHECK(node.get_value() == 10);
    }

    SUBCASE("Parent-Child Relationships")
    {
        Node<int> parent(10);
        Node<int> child1(20);
        Node<int> child2(30);

        parent.children.push_back(std::make_shared<Node<int>>(child1));
        parent.children.push_back(std::make_shared<Node<int>>(child2));

        CHECK(parent.children.size() == 2);
        CHECK(parent.children[0]->get_value() == 20);
        CHECK(parent.children[1]->get_value() == 30);
    }
}


TEST_CASE("Complex Class Tests")
{
    SUBCASE("Addition Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(3.0, 4.0);
        Complex result = c1 + c2;
        CHECK(result == Complex(4.0, 6.0));
    }

    SUBCASE("Equality Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 2.0);
        CHECK(c1 == c2);
    }

    SUBCASE("Comparison Operator")
    {
        Complex c1(1.0, 2.0);
        Complex c2(1.0, 3.0);
        CHECK(c2 > c1);
    }
}

TEST_CASE("Node Class Tests")
{
    SUBCASE("Constructor and Value Access")
    {
        Node<int> node(10);
        CHECK(node.get_value() == 10);
    }

    SUBCASE("Parent-Child Relationships")
    {
        Node<int> parent(10);
        Node<int> child1(20);
        Node<int> child2(30);

        parent.children.push_back(std::make_shared<Node<int>>(child1));
        parent.children.push_back(std::make_shared<Node<int>>(child2));

        CHECK(parent.children.size() == 2);
        CHECK(parent.children[0]->value == 20);
        CHECK(parent.children[1]->value == 30);
    }
}

TEST_CASE("Tree Class Tests")
{
    SUBCASE("Adding Root and Subnodes")
    {
        Tree<int, 2> tree;
        Node<int> root(10);
        Node<int> child1(20);
        Node<int> child2(30);

        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        CHECK(tree.root->value == 10);
        CHECK(tree.root->children.size() == 2);
        CHECK(tree.root->children[0]->value == 20);
        CHECK(tree.root->children[1]->value == 30);
    }

    SUBCASE("Finding Nodes")
    {
        Tree<int, 2> tree;
        Node<int> root(10);
        Node<int> child1(20);
        Node<int> child2(30);

        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        auto found_node = tree.find_node(tree.root, 20);
        CHECK(found_node != nullptr);
        CHECK(found_node->value == 20);

        auto not_found_node = tree.find_node(tree.root, 40);
        CHECK(not_found_node == nullptr);
    }

    SUBCASE("Tree Iterators")
    {
        Tree<int, 2> tree;
        Node<int> root(10);
        Node<int> child1(20);
        Node<int> child2(30);

        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        int expected[] = {10, 20, 30};
        int index = 0;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
        {
            CHECK(*it == expected[index++]);
        }
    }

    SUBCASE("Tree Deletion")
    {
        Tree<int, 2> tree;
        Node<int> root(10);
        Node<int> child1(20);
        Node<int> child2(30);

        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        tree.clearTree(tree.root);

        CHECK(tree.root == nullptr);
    }
}