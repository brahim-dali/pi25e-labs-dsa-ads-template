//
// Created by marius on 1/27/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class SinglyLinkedList {
    private:
        struct Node {
            T value;
            Node* next;
            Node(const T& v, Node* n = nullptr) : value(v), next(n) {}
        };

    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        // Rule of 3/5: LATER (not implementing just copying now)
        SinglyLinkedList(const SinglyLinkedList&) = delete;
        SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

        bool empty() const;
        std::size_t size() const;

        T& front();
        const T& front() const;

        T& back();               // O(n) for singly list (unless you store tail)
        const T& back() const;

        void push_front(const T& value);
        void push_back(const T& value);

        void pop_front();        // throws if empty
        void pop_back();         // throws if empty

        void clear();

    private:
        Node* head_;
        std::size_t size_;
    };

} // namespace dsa
