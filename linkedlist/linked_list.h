#pragma once
#include "status.h"
#include <optional>
#include <memory>
#include <iostream>


/* TODO:
    - Move Semantics
    - Copy Semantics
    - Iterator Support
*/


// =========================
// LinkedList declaration
// =========================
template <typename T>
class LinkedList {
    
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    size_t length;
    std::unique_ptr<Node> head;
    Node* tail;
    
    Node* getNodeAt(size_t index);
    const Node* getNodeAt(size_t index) const;

public:
    // Constructors and Deconstructors
    LinkedList();
    ~LinkedList();

    // Capacity Functions
    bool empty() const;
    size_t size() const;

    // Element access
    T& at(size_t index);
    const T& at(size_t index) const;
    const T& front() const;
    const T& back() const;

    // Modifiers
    void push_back(const T& v);
    void push_front(const T& v);
    Status insert(const T& v, size_t index);    
    void pop_back();
    void pop_front();
    void erase(size_t index); 
    void clear();

    // Search
    int index_of(const T& v) const;

    // Overload print
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& ll) {
        os << '[';
        for (auto* cur = ll.root.get(); cur; cur = cur->next.get()) {
            os << cur->data;
            if (cur->next) os << ", ";
        }
        os << "]\n";
        return os;
    }

}; 


// =========================
// Include definitions
// =========================
#include "linked_list.tpp"