#include<algorithm>
#include<iostream>

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
    SLList(){
        head = tail = nullptr;
        n = 0;
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

    void AddHead(T data){
        Node *node = createNode(data);
        if (head == nullptr){
            head = tail = node;
            n++;
            return;
        }
        node->next = head;
        head = node;
        n++;
    }
    void AddTail(T data){
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
    void RemoveHead(){
        if (head == nullptr){
            return;
        }
        Node *tmp = head;
        head = head->next;
        delete tmp;
        n--;
        if (head == nullptr){
            tail = nullptr;
        }
    }
    void RemoveTail(){
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
    void Clear(){
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

void fnAction(int val){
    cout << val << ", ";
}

void fnAction2(int& val){
    val *= 2;
}

bool fnPredict(int val){
    const int threshold = 3;
    return val > threshold;
}

int main(){
    SLList<int> l;
    l.AddTail(1);
    l.AddTail(1);
    l.AddTail(0);
    l.AddTail(4);
    l.AddTail(2);
    l.AddTail(5);
    for (SLList<int>::Iterator it = l.begin(); it != l.end(); ++it){
        cout << *it << ", ";
    }
    cout << endl;

    for_each(l.begin(), l.end(), fnAction2);
    for_each(l.begin(), l.end(), fnAction);
    cout << endl;

    replace_if(l.begin(), l.end(), fnPredict, 100);
    cout << l << endl;

    fill(l.begin(), l.end(), 123);
    cout << l << endl;

    l.Clear();

    system("pause");
    return 0;
}