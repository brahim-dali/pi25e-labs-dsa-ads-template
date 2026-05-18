#pragma once

#include <cstddef>
#include <stdexcept>

namespace dsa {

template <typename T>
class BinaryTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    std::size_t size_;

    Node* find(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (node->value == value) return node;

        Node* left = find(node->left, value);
        if (left) return left;

        return find(node->right, value);
    }

    void preorder_impl(Node* node, T* out, std::size_t& index) const {
        if (!node) return;
        out[index++] = node->value;
        preorder_impl(node->left, out, index);
        preorder_impl(node->right, out, index);
    }

    void inorder_impl(Node* node, T* out, std::size_t& index) const {
        if (!node) return;
        inorder_impl(node->left, out, index);
        out[index++] = node->value;
        inorder_impl(node->right, out, index);
    }

    void postorder_impl(Node* node, T* out, std::size_t& index) const {
        if (!node) return;
        postorder_impl(node->left, out, index);
        postorder_impl(node->right, out, index);
        out[index++] = node->value;
    }

    std::size_t height_impl(Node* node) const {
        if (!node) return 0;

        std::size_t left_h = height_impl(node->left);
        std::size_t right_h = height_impl(node->right);

        return 1 + (left_h > right_h ? left_h : right_h);
    }

    bool contains_impl(Node* node, const T& value) const {
        if (!node) return false;
        if (node->value == value) return true;

        return contains_impl(node->left, value) ||
               contains_impl(node->right, value);
    }

    void clear_impl(Node* node) {
        if (!node) return;

        clear_impl(node->left);
        clear_impl(node->right);
        delete node;
    }

public:
    BinaryTree() : root_(nullptr), size_(0) {}

    ~BinaryTree() {
        clear();
    }

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    void set_root(const T& value) {
        if (root_ != nullptr) {
            throw std::logic_error("Root already exists");
        }
        root_ = new Node(value);
        size_ = 1;
    }

    void add_left(const T& parentValue, const T& childValue) {
        Node* parent = find(root_, parentValue);
        if (!parent) {
            throw std::out_of_range("Parent not found");
        }
        if (parent->left != nullptr) {
            throw std::logic_error("Left child already exists");
        }

        parent->left = new Node(childValue);
        size_++;
    }

    void add_right(const T& parentValue, const T& childValue) {
        Node* parent = find(root_, parentValue);
        if (!parent) {
            throw std::out_of_range("Parent not found");
        }
        if (parent->right != nullptr) {
            throw std::logic_error("Right child already exists");
        }

        parent->right = new Node(childValue);
        size_++;
    }

    void preorder(T* out) const {
        std::size_t index = 0;
        preorder_impl(root_, out, index);
    }

    void inorder(T* out) const {
        std::size_t index = 0;
        inorder_impl(root_, out, index);
    }

    void postorder(T* out) const {
        std::size_t index = 0;
        postorder_impl(root_, out, index);
    }

    std::size_t height() const {
        return height_impl(root_);
    }

    bool contains(const T& value) const {
        return contains_impl(root_, value);
    }

    void clear() {
        clear_impl(root_);
        root_ = nullptr;
        size_ = 0;
    }
};

} // namespace dsa
