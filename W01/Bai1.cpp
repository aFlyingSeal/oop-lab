#include<iostream>

using namespace std;

class Object{
private:
    int id;
public:
    Object(){
        id = 0;
        cout << "Object created with id: 0 (default)\n";
    }
    Object(int id){
        this->id = id;
        cout << "Object created with id: " << id << endl;
    }
    void getId(){
        cout << "Object (" << id << ")\n";
        return;
    }
    ~Object(){
        cout << "Object (" << id << ") destructed\n";
    }
};

void createObject(){
    Object obj1;
    Object obj2(2);
}

int main(){
    Object obj1;
    createObject();
    Object obj2(1);
}