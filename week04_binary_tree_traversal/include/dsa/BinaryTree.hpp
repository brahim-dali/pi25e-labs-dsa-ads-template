//
// Created by marius on 2/11/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    // BinaryTree<T>
    // Educational binary tree used to practice recursion and traversals.
    // Not a BST (no ordering rules).
    template <class T>
    class BinaryTree {
    private:
        struct Node {
            T value;
            Node* left;
            Node* right;
            Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
        };

    public:
        BinaryTree();
        ~BinaryTree();

        BinaryTree(const BinaryTree&) = delete;
        BinaryTree& operator=(const BinaryTree&) = delete;

        bool empty() const;
        std::size_t size() const;

        // Build tree manually (for labs/tests)
        // Creates root if empty, otherwise throws
        void set_root(const T& value);
        void add_left(const T& parentValue, const T& childValue);
        void add_right(const T& parentValue, const T& childValue);

        // Traversals (fill output array in order)
        // Precondition: out has capacity >= size()
        void preorder(T* out) const;
        void inorder(T* out) const;
        void postorder(T* out) const;

        // Useful recursive algorithms
        std::size_t height() const;            // height in nodes: empty=0, leaf=1
        bool contains(const T& value) const;

        void clear();

    private:
        Node* find(Node* node, const T& value) const;

        void preorder(Node* node, T* out, std::size_t& idx) const;
        void inorder(Node* node, T* out, std::size_t& idx) const;
        void postorder(Node* node, T* out, std::size_t& idx) const;

        std::size_t height(Node* node) const;
        bool contains(Node* node, const T& value) const;

        void clear(Node* node);

    private:
        Node* root_;
        std::size_t size_;
    };

} // namespace dsa
