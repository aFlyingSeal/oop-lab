#ifndef _SLLIST_H_
#define _SLLIST_H_

#include<iostream>
#include<cstring>

using namespace std;

template<class T>
class SLList{
private:
    struct Node{
        T data;
        Node* next;
    };

    Node *head, *tail;
    int n;

    static Node* createNode(T data){
        Node* node = new Node{ data, nullptr };
        return node;
    }
public:
    class Iterator{
    public:
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
    private:
        Node* current_node;

        Iterator(Node *node): current_node(node){}

        friend class SLList<T>;
    public:
        Iterator(): current_node(nullptr){}
        reference operator*() const{
            if (!current_node){
                throw out_of_range("Deferencing end() or null iterator");
            }
            return current_node->data;
        }
        pointer operator->() const{
            if (!current_node){
                throw out_of_range("Accessing member via end() or null iterator");
            }
            return &(current_node->data);
        }
        Iterator& operator++(){ // prefix 
            if (current_node){
                current_node = current_node->next;
            }
            else{
                throw out_of_range("Incrementing end() or null iterator");
            }
            return *this;
        }
        Iterator operator++(int){ // postfix
            if (!current_node){
                throw out_of_range("Incrementing end() or null iterator");
            }
            Iterator temp = *this;
            current_node = current_node->next;
            return temp;
        }
        bool operator==(const Iterator& other) const{
            return current_node == other.current_node;
        }
        bool operator!=(const Iterator& other) const{
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(head);
    }
    Iterator end(){
        return Iterator(nullptr);
    }

    // constructors
    SLList(){
        head = tail = nullptr;
        n = 0;
    }
    SLList(const SLList& other) : head(nullptr), tail(nullptr), n(0) {
        Node* current = other.head;
        while (current != nullptr) {
            this->push_back(current->data);
            current = current->next;
        }
    }
    ~SLList(){
        Node *tmp = head;
        while (head != nullptr){
            tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        n = 0;
    }

    // operators
    SLList& operator=(const SLList& other) {
        if (this != &other) {
            this->clear(); 
            Node* current = other.head;
            while (current != nullptr) {
                this->push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    T operator[](int index) const{
        if (index < 0 || index >= n){
            throw out_of_range("Index out of range");
        }
        Node* cur = head;
        for (int i = 0; i < index; i++){
            cur = cur->next;
        }
        return cur->data;
    }

    // methods for adding element
    void insert(Iterator pos, T data){
        Node* node = createNode(data);
        if (pos.current_node == head || head == nullptr){
            node->next = head;
            head = node;
        }
        else{
            Node *cur = head;
            Node *pre = head;
            while (pre != nullptr && pre->next != pos.current_node){
                pre = pre->next;
            }
            if (pre == nullptr){
                throw out_of_range("Position out of range");
            }
            node->next = pos.current_node;
            pre->next = node;
            if (pre = tail){
                tail = node;
            }
        }
        n++;
    }
    void push_back(T data){
        Node *node = createNode(data);
        if (head == nullptr){
            head = tail = node;
            n++;
            return;
        }
        tail->next = node;
        tail = node;
        n++;
    }
    void pop_back(){
        if (tail == nullptr){
            return;
        }
        if (head == tail){
            delete head;
            head = tail = nullptr;
            n--;
            return;
        }
        Node *tmp = head;
        while (tmp->next != tail){
            tmp = tmp->next;
        }
        delete tail;
        tail = tmp;
        tail->next = nullptr;
        n--;
    }

    // getters
    int size() const{
        return n;
    }

    // clear
    void clear(){
        Node *tmp;
        while (head != nullptr){
            tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        n = 0;
    }

    template<class U>
    friend ostream& operator<<(ostream& out, const SLList<U>& ll);
};

template<class T>
ostream& operator<<(ostream& out, const SLList<T>& ll){
    typename SLList<T>::Node *cur = ll.head;
    while (cur != nullptr){
        out << cur->data << ", ";
        cur = cur->next;
    }
    return out;
}

#endif