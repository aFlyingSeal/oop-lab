#include<iostream>

using namespace std;

#define NOE 10

class A{
private:
    int info[NOE];
public:
    A();

    typedef int* indexOf;
    indexOf GetInfo(int idx);

    void Xuat(ostream& out);
};

A::A(){
    for (int i = 0; i < NOE; i++){
        info[i] = i + NOE;
    }
}

A::indexOf A::GetInfo(int idx){
    indexOf rt = info + idx;
    return rt;
}

void A::Xuat(ostream& out){
    for (int i = 0; i < NOE; i++){
        out << info[i] << ", ";
    }
    out << endl;
}

int main(){
    const int i = 7;
    A a;
    A::indexOf io = a.GetInfo(i);
    cout << *io << endl;
    *io = 10;
    a.Xuat(cout);

    system("pause");
    return 0;
}