#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <stack>
#include <set>
#include <algorithm>

// Forward declaration of iterator classes
template <typename T>
class PreOrderIterator;

template <typename T>
class PostOrderIterator;

template <typename T>
class InOrderIterator;

template <typename T>
class BFSIterator;

template <typename T>
class DFSIterator;

template <typename T>
class HeapIterator;

template <typename T, int K = 2>
class Tree
{
public:
    // Constructor and Destructor
    Tree() : root(nullptr) {}
    ~Tree()
    {
        clearTree(root);
    }

    void clearTree(std::shared_ptr<Node<T>> &node)
    {
        if (!node)
            return;

        for (auto &child : node->children)
        {
            clearTree(child);
        }
        node->children.clear(); // Ensure all children are cleared
        node.reset();           // Release the current node
    }

    std::shared_ptr<Node<T>> root;

    void add_root(Node<T> &node)
    {
        root = std::make_shared<Node<T>>(node);
    }

    void add_sub_node(Node<T> &parent_node, Node<T> &child_node)
    {
        auto parent = find_node(root, parent_node.get_value());
        if (parent && parent->children.size() < K)
        {
            parent->children.push_back(std::make_shared<Node<T>>(child_node));
            parent->children.back()->parent = parent; // Set parent pointer
        }
    }

    std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, T value)
    {
        if (!current)
            return nullptr;
        if (current->value == value)
            return current;
        for (auto &child : current->children)
        {
            auto found = find_node(child, value);
            if (found)
                return found;
        }
        return nullptr;
    }

    // Pre-Order Iterator
    using PreOrderIter = PreOrderIterator<T>;
    PreOrderIter begin_pre_order() const { return PreOrderIter(root); }
    PreOrderIter end_pre_order() const { return PreOrderIter(nullptr); }

    // Post-Order Iterator
    using PostOrderIter = PostOrderIterator<T>;
    PostOrderIter begin_post_order() const { return PostOrderIter(root); }
    PostOrderIter end_post_order() const { return PostOrderIter(nullptr); }

    // In-Order Iterator
    using InOrderIter = InOrderIterator<T>;
    InOrderIter begin_in_order() const { return InOrderIter(root); }
    InOrderIter end_in_order() const { return InOrderIter(nullptr); }

    // BFS Iterator
    using BFSIter = BFSIterator<T>;
    BFSIter begin_bfs_scan() const { return BFSIter(root); }
    BFSIter end_bfs_scan() const { return BFSIter(nullptr); }

    // DFS Iterator
    using DFSIter = DFSIterator<T>;
    DFSIter begin_dfs_scan() const { return DFSIter(root); }
    DFSIter end_dfs_scan() const { return DFSIter(nullptr); }

    // Heap Iterator
    using HeapIter = HeapIterator<T>;
    HeapIter begin_heap() const { return HeapIter(root); }
    HeapIter end_heap() const { return HeapIter(nullptr); }

    // Range-based for loop support using BFSIter
    BFSIter begin() const { return begin_bfs_scan(); }
    BFSIter end() const { return end_bfs_scan(); }

    // Overload << operator for printing the tree
    friend std::ostream &operator<<(std::ostream &os, const Tree<T, K> &tree)
    {
        tree.printTree(os, tree.root, "", true);
        return os;
    }

    // Print tree structure recursively
    void printTree(std::ostream &os, std::shared_ptr<Node<T>> node, std::string prefix, bool isLeft) const
    {
        if (node)
        {
            os << prefix;
            os << (isLeft ? "├── " : "└── ");
            os << node->value << std::endl;

            for (size_t i = 0; i < node->children.size(); ++i)
            {
                printTree(os, node->children[i], prefix + (isLeft ? "│   " : "    "), i < node->children.size() - 1);
            }
        }
    }

    std::pair<HeapIterator<T>, HeapIterator<T>> myHeap()
    {
        std::vector<std::shared_ptr<Node<T>>> nodes;
        collectNodes(root, nodes);

        // Heapify the vector of nodes
        std::make_heap(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node<T>> &a, const std::shared_ptr<Node<T>> &b)
                       { return a->value > b->value; });

        // Create a new heap root from the heapified nodes
        std::shared_ptr<Node<T>> heapRoot = nodes.front();
        for (size_t i = 1; i < nodes.size(); ++i)
        {
            auto parentIdx = (i - 1) / K;
            nodes[parentIdx]->children.push_back(nodes[i]);
        }

        // Return iterators for the heap
        return std::make_pair(HeapIterator<T>(heapRoot), HeapIterator<T>(nullptr));
    }

private:
    void collectNodes(std::shared_ptr<Node<T>> node, std::vector<std::shared_ptr<Node<T>>> &nodes)
    {
        if (node)
        {
            nodes.push_back(node);
            for (auto &child : node->children)
            {
                collectNodes(child, nodes);
            }
        }
    }
};

#endif

// PreOrderIterator class
template <typename T>
class PreOrderIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    PreOrderIterator(std::shared_ptr<Node<T>> root)
    {
        if (root)
            node_stack.push(root);
    }

    bool operator!=(const PreOrderIterator &other) const
    {
        return !node_stack.empty() || !other.node_stack.empty();
    }

    PreOrderIterator &operator++()
    {
        if (!node_stack.empty())
        {
            auto current = node_stack.top();
            node_stack.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
            {
                node_stack.push(*it);
            }
        }
        return *this;
    }

    T operator*() const
    {
        return node_stack.top()->get_value();
    }
};

// PostOrderIterator class
template <typename T>
class PostOrderIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    PostOrderIterator(std::shared_ptr<Node<T>> root)
    {
        fill_stack(root);
    }

    bool operator!=(const PostOrderIterator &other) const
    {
        return !node_stack.empty() || !other.node_stack.empty();
    }

    PostOrderIterator &operator++()
    {
        if (!node_stack.empty())
        {
            node_stack.pop();
        }
        return *this;
    }

    T operator*() const
    {
        return node_stack.top()->get_value();
    }

private:
    void fill_stack(std::shared_ptr<Node<T>> node)
    {
        if (!node)
            return;

        std::stack<std::shared_ptr<Node<T>>> temp_stack;
        temp_stack.push(node);

        while (!temp_stack.empty())
        {
            auto current = temp_stack.top();
            temp_stack.pop();
            node_stack.push(current);
            for (auto &child : current->children)
            {
                temp_stack.push(child);
            }
        }
    }
};

// InOrderIterator class
template <typename T>
class InOrderIterator
{
    using NodePtr = std::shared_ptr<Node<T>>;
    std::stack<NodePtr> node_stack;
    std::set<NodePtr> visited;

public:
    InOrderIterator(NodePtr root)
    {
        push_leftmost(root);
    }

    bool operator!=(const InOrderIterator &other) const
    {
        return !node_stack.empty() || !other.node_stack.empty();
    }

    InOrderIterator &operator++()
    {
        auto current = node_stack.top();
        node_stack.pop();
        visited.insert(current);

        for (auto &child : current->children)
        {
            if (visited.find(child) == visited.end())
            {
                push_leftmost(child);
                break;
            }
        }

        return *this;
    }

    T operator*() const
    {
        return node_stack.top()->get_value();
    }

private:
    void push_leftmost(NodePtr node)
    {
        while (node && visited.find(node) == visited.end())
        {
            node_stack.push(node);
            if (!node->children.empty())
            {
                node = node->children.front();
            }
            else
            {
                break;
            }
        }
    }
};

// BFSIterator class
template <typename T>
class BFSIterator
{
    std::queue<std::shared_ptr<Node<T>>> node_queue;

public:
    BFSIterator(std::shared_ptr<Node<T>> root)
    {
        if (root)
            node_queue.push(root);
    }

    bool operator!=(const BFSIterator &other) const
    {
        return !node_queue.empty() || !other.node_queue.empty();
    }

    BFSIterator &operator++()
    {
        if (!node_queue.empty())
        {
            auto current = node_queue.front();
            node_queue.pop();
            for (auto &child : current->children)
            {
                node_queue.push(child);
            }
        }
        return *this;
    }

    T operator*() const
    {
        return node_queue.front()->get_value();
    }
};

// DFSIterator class
template <typename T>
class DFSIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    DFSIterator(std::shared_ptr<Node<T>> root)
    {
        if (root)
            node_stack.push(root);
    }

    bool operator!=(const DFSIterator &other) const
    {
        return !node_stack.empty() || !other.node_stack.empty();
    }

    DFSIterator &operator++()
    {
        if (!node_stack.empty())
        {
            auto current = node_stack.top();
            node_stack.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
            {
                node_stack.push(*it);
            }
        }
        return *this;
    }

    T operator*() const
    {
        return node_stack.top()->get_value();
    }
};

// HeapIterator class
template <typename T>
class HeapIterator
{
    std::shared_ptr<Node<T>> current;

public:
    HeapIterator(std::shared_ptr<Node<T>> root) : current(root) {}

    bool operator!=(const HeapIterator &other) const
    {
        return current != other.current;
    }

    HeapIterator &operator++()
    {
        // Placeholder for heap traversal logic
        current = nullptr;
        return *this;
    }

    T operator*() const
    {
        return current->get_value();
    }
};
