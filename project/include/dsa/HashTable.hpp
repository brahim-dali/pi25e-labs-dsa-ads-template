//
// Created by marius on 2/20/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    class HashTable {
    private:
        struct Node {
            int key;
            int value;
            Node* next;

            Node(int k, int v, Node* n = nullptr)
                : key(k), value(v), next(n) {}
        };

    public:
        explicit HashTable(int capacity)
            : capacity_(capacity), size_(0) {

            buckets_ = new Node*[capacity_];

            for (int i = 0; i < capacity_; ++i) {
                buckets_[i] = nullptr;
            }
        }

        ~HashTable() {
            for (int i = 0; i < capacity_; ++i) {
                clear_bucket(buckets_[i]);
            }

            delete[] buckets_;
        }

        HashTable(const HashTable&) = delete;
        HashTable& operator=(const HashTable&) = delete;

        bool put(int key, int value) {
            int index = index_for(key);

            Node* current = buckets_[index];

            while (current != nullptr) {
                if (current->key == key) {
                    current->value = value;
                    return false;
                }

                current = current->next;
            }

            buckets_[index] = new Node(key, value, buckets_[index]);
            ++size_;

            return true;
        }

        bool contains(int key) const {
            int index = index_for(key);

            Node* current = buckets_[index];

            while (current != nullptr) {
                if (current->key == key) {
                    return true;
                }

                current = current->next;
            }

            return false;
        }

        int* get(int key) {
            int index = index_for(key);

            Node* current = buckets_[index];

            while (current != nullptr) {
                if (current->key == key) {
                    return &current->value;
                }

                current = current->next;
            }

            return nullptr;
        }

        bool remove(int key) {
            int index = index_for(key);

            Node* current = buckets_[index];
            Node* previous = nullptr;

            while (current != nullptr) {
                if (current->key == key) {
                    if (previous == nullptr) {
                        buckets_[index] = current->next;
                    } else {
                        previous->next = current->next;
                    }

                    delete current;
                    --size_;

                    return true;
                }

                previous = current;
                current = current->next;
            }

            return false;
        }

        int size() const {
            return size_;
        }

        int bucket_count() const {
            return capacity_;
        }

    private:
        int index_for(int key) const {
            int index = key % capacity_;

            if (index < 0) {
                index += capacity_;
            }

            return index;
        }

        void clear_bucket(Node*& head) {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

    private:
        Node** buckets_;
        int capacity_;
        int size_;
    };

} // namespace dsa
