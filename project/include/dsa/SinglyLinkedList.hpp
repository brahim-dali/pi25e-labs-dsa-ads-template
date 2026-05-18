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

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    bool empty() const;
    std::size_t size() const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    void push_front(const T& value);
    void push_back(const T& value);

    void pop_front();
    void pop_back();

    void clear();

private:
    Node* head_;
    std::size_t size_;
};



template<class T>
SinglyLinkedList<T>::SinglyLinkedList() : head_(nullptr), size_(0) {}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template<class T>
bool SinglyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<class T>
std::size_t SinglyLinkedList<T>::size() const {
    return size_;
}

template<class T>
T& SinglyLinkedList<T>::front() {
    if (empty())
        throw std::out_of_range("List empty");
    return head_->value;
}

template<class T>
const T& SinglyLinkedList<T>::front() const {
    if (empty())
        throw std::out_of_range("List empty");
    return head_->value;
}

template<class T>
T& SinglyLinkedList<T>::back() {
    if (empty())
        throw std::out_of_range("List empty");

    Node* cur = head_;
    while (cur->next != nullptr)
        cur = cur->next;

    return cur->value;
}

template<class T>
const T& SinglyLinkedList<T>::back() const {
    if (empty())
        throw std::out_of_range("List empty");

    Node* cur = head_;
    while (cur->next != nullptr)
        cur = cur->next;

    return cur->value;
}

template<class T>
void SinglyLinkedList<T>::push_front(const T& value) {
    head_ = new Node(value, head_);
    size_++;
}

template<class T>
void SinglyLinkedList<T>::push_back(const T& value) {

    Node* node = new Node(value);

    if (empty()) {
        head_ = node;
    } else {
        Node* cur = head_;
        while (cur->next != nullptr)
            cur = cur->next;

        cur->next = node;
    }

    size_++;
}

template<class T>
void SinglyLinkedList<T>::pop_front() {

    if (empty())
        throw std::out_of_range("List empty");

    Node* temp = head_;
    head_ = head_->next;

    delete temp;
    size_--;
}

template<class T>
void SinglyLinkedList<T>::pop_back() {

    if (empty())
        throw std::out_of_range("List empty");

    if (head_->next == nullptr) {
        delete head_;
        head_ = nullptr;
    } else {

        Node* cur = head_;

        while (cur->next->next != nullptr)
            cur = cur->next;

        delete cur->next;
        cur->next = nullptr;
    }

    size_--;
}

template<class T>
void SinglyLinkedList<T>::clear() {

    while (!empty())
        pop_front();
}

} // namespace dsa
