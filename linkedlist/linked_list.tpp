// LinkedList.tpp

#pragma once

#include "linked_list.h"



template <typename T>
LinkedList<T>::LinkedList() {
    length = 0;
    head = nullptr;
    tail = nullptr;
}


template <typename T>
LinkedList<T>::~LinkedList() = default;

// ########## Capacity ########## 
template <typename T>
bool LinkedList<T>::empty() const {
    return length == 0;
}

template <typename T>
size_t LinkedList<T>::size() const {
    return length;
}


// ########## Element Access ########## 
template <typename T>
T& LinkedList<T>::at(size_t index) {
    if (index >= length) throw std::out_of_range("Index out of bounds");
    return getNodeAt(index)->data;
}

template <typename T>
const T& LinkedList<T>::at(size_t index) const {
    if (index >= length) throw std::out_of_range("Index out of bounds");
    return getNodeAt(index)->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    if (!head) {
        throw std::out_of_range("LinkedList is empty");
    }
    return head->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    if (!tail) {
        throw std::out_of_range("LinkedList is empty");
    }
    return tail->data;
}


// ########## Modifiers ########## 
template <typename T>
void LinkedList<T>::push_back(const T& v) {
    if (!head) {
        head = std::make_unique<Node>(v);
        tail = head.get();
    } else {
        auto newTail = std::make_unique<Node>(v);
        tail->next = std::move(newTail);
        tail = tail->next.get();
    }
    length++;
}

template <typename T>
void LinkedList<T>::push_front(const T& v) {
    auto newHead = std::make_unique<Node>(v);

    if (head) {
        newHead->next = std::move(head);
    } else {
        tail = newHead.get();
    }
    head = std::move(newHead);
    length++;
}

template <typename T>
Status LinkedList<T>::insert(const T& v, size_t index) { 
    if (index > length) return Status::InsertionFailure;
    
    if (index == 0) {
        push_front(v);
    } else if (index == length) {  // allow inserting at end
        push_back(v);
    } else {
        auto node = std::make_unique<Node>(v);
        Node* current = head.get();
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next.get();
        }
        node->next = std::move(current->next);
        current->next = std::move(node);
        ++length;
    }
    
    return Status::Success;
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("LinkedList is empty");
    }
    if (length == 1) {
        head = nullptr;
        tail = nullptr;

    } else {
        Node* current = head.get();
        for (size_t i = 0; i < length - 2; ++i) {
            current = current->next.get();
        }
        current->next = nullptr;
        tail = current;
    }
    --length;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("LinkedList is empty");
    }
    head = std::move(head->next);
    --length;
    if (!head) {
        tail = nullptr;
    }
}


template <typename T>
void LinkedList<T>::erase(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0) {
        pop_front();
    } else if (index == length - 1) {
        pop_back();
    } else {
        Node* current = head.get(); 
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next.get();
        }
        std::unique_ptr<Node> nodeToRemove = std::move(current->next);
        current->next = std::move(nodeToRemove->next);
        nodeToRemove->next = nullptr;
        --length;
    }
}

template <typename T>
void LinkedList<T>::clear() {
    head.reset();
    length = 0;
}




// ########## Search ########## 
template <typename T>
int LinkedList<T>::index_of(const T& v) const {
    const Node* current = head.get();
    for (size_t i = 0; i < length; i++) {
        if (current->data == v) {
            return i;
        }
        current = current->next.get();
    }
    return -1;
}

// get at node at index
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(size_t index) {
    if (index >= length) return nullptr;

    Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    return current;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(size_t index) const {
    if (index >= length) return nullptr;

    const Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    return current;
}



