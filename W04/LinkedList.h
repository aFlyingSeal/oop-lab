#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include<iostream>

using namespace std;

template<class T>
class Node{
public:
    T data;
    Node *next;
};

template<class T>
class LinkedList{
private:
    Node<T> *head, *tail;
    int n;
    static Node<T>* CreateNode(T data);
public:
    LinkedList();
    
    Node<T>* AddHead(T data);
    Node<T>* AddTail(T data);
    Node<T>* RemoveHead();
    Node<T>* RemoveTail();

    T& operator[](int idx);

    template<class T1>
    friend ostream& operator<<(ostream& out, const LinkedList<T1>& list);

    ~LinkedList();
};

template<class T>
Node<T>* LinkedList<T>::CreateNode(T data){
    Node<T> *node = new Node<T>;
    node->data = data;
    node->next = nullptr;
    return node;
}

template<class T>
LinkedList<T>::LinkedList(){
    head = tail = nullptr;
    n = 0;
}

template<class T>
Node<T>* LinkedList<T>::AddHead(T data){
    Node<T>* node = CreateNode(data);
    if (node == nullptr){
        return nullptr;
    }
    if (head == nullptr){
        head = tail = node;
        n++;
        return node;
    }
    node->next = head;
    head = node;
    n++;
    return node;
}

template<class T>
Node<T>* LinkedList<T>::AddTail(T data){
    Node<T>* node = CreateNode(data);
    if (node == nullptr){
        return nullptr;
    }
    if (tail == nullptr){
        head = tail = node;
        n++;
        return node;
    }
    tail->next = node;
    tail = node;
    n++;
    return node;
}

template<class T>
Node<T>* LinkedList<T>::RemoveHead(){
    if (head == nullptr){
        return nullptr;
    }
    Node<T>* tmp = head;
    head = head->next;
    n--;
    if (head == nullptr){
        tail = nullptr;
    }
    return tmp;
}

template<class T>
Node<T>* LinkedList<T>::RemoveTail(){
    if (tail == nullptr){
        return nullptr;
    }
    Node<T>* tmp = head;
    while (tmp->next != tail){
        tmp = tmp->next;
    }
    tail = tmp;
    n--;
    return tmp;
}

template<class T>
T& LinkedList<T>::operator[](int idx){
    if (idx < 0 || idx >= n){
        throw out_of_range("out of range");
    }
    Node<T>* p = head;
    while (idx--){
        p = p->next;
    }
    return p->data;
}

template<class T>
ostream& operator<<(ostream& out, const LinkedList<T>& ll){
    Node<T>* p = ll.head;
    while (p != nullptr){
        out << p->data << " ";
        p = p->next;
    }
    return out;
}

template<class T>
LinkedList<T>::~LinkedList(){
    Node<T>* p = head;
    while (head != nullptr){
        head = head->next;
        delete p;
        p = head;
    }
    n = 0;
}

#endif