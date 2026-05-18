//
// Created by marius on 2/19/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class BST {
    private:
        struct Node {
            T key;
            Node* left;
            Node* right;
            Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
        };

    public:
        BST() : root_(nullptr), size_(0) {}

        ~BST() {
            clear();
        }

        BST(const BST&) = delete;
        BST& operator=(const BST&) = delete;

        bool empty() const {
            return size_ == 0;
        }

        std::size_t size() const {
            return size_;
        }

        bool contains(const T& key) const {
            return contains(root_, key);
        }

        void insert(const T& key) {
            bool inserted = false;
            root_ = insert(root_, key, inserted);
            if (inserted) size_++;
        }

        bool remove(const T& key) {
            bool removed = false;
            root_ = remove(root_, key, removed);
            if (removed) size_--;
            return removed;
        }

        const T& min() const {
            if (!root_) throw std::out_of_range("empty");
            return min(root_);
        }

        const T& max() const {
            if (!root_) throw std::out_of_range("empty");
            return max(root_);
        }

        void inorder(T* out) const {
            std::size_t idx = 0;
            inorder(root_, out, idx);
        }

        std::size_t height() const {
            return height(root_);
        }

        void clear() {
            clear(root_);
            root_ = nullptr;
            size_ = 0;
        }

    private:
        Node* insert(Node* node, const T& key, bool& inserted) {
            if (!node) {
                inserted = true;
                return new Node(key);
            }
            if (key < node->key)
                node->left = insert(node->left, key, inserted);
            else if (key > node->key)
                node->right = insert(node->right, key, inserted);
            return node;
        }

        bool contains(Node* node, const T& key) const {
            if (!node) return false;
            if (key == node->key) return true;
            if (key < node->key)
                return contains(node->left, key);
            return contains(node->right, key);
        }

        Node* remove(Node* node, const T& key, bool& removed) {
            if (!node) return nullptr;

            if (key < node->key) {
                node->left = remove(node->left, key, removed);
            } else if (key > node->key) {
                node->right = remove(node->right, key, removed);
            } else {
                removed = true;

                if (!node->left && !node->right) {
                    delete node;
                    return nullptr;
                }

                if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                }

                if (!node->right) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }

                Node* successor = find_min_node(node->right);
                node->key = successor->key;
                node->right = remove(node->right, successor->key, removed);
            }

            return node;
        }

        Node* find_min_node(Node* node) const {
            while (node->left)
                node = node->left;
            return node;
        }

        const T& min(Node* node) const {
            while (node->left)
                node = node->left;
            return node->key;
        }

        const T& max(Node* node) const {
            while (node->right)
                node = node->right;
            return node->key;
        }

        void inorder(Node* node, T* out, std::size_t& idx) const {
            if (!node) return;
            inorder(node->left, out, idx);
            out[idx++] = node->key;
            inorder(node->right, out, idx);
        }

        std::size_t height(Node* node) const {
            if (!node) return 0;
            std::size_t l = height(node->left);
            std::size_t r = height(node->right);
            return 1 + (l > r ? l : r);
        }

        void clear(Node* node) {
            if (!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
        }

    private:
        Node* root_;
        std::size_t size_;
    };

} // namespace dsa
