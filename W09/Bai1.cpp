#include<iostream>
#include<vector>

using namespace std;

class Base{
public:
    virtual void Print(ostream& out) = 0;
    friend ostream& operator<<(ostream& out, Base& base){
        base.Print(out);
        return out;
    }
};

class Derived1: public Base{
private:
    int _ofD1;
public:
    Derived1(int v){
        _ofD1 = v;
    }

    void Print(ostream& out){
        out << "D1 - " << _ofD1;
    }
};

class Derived2: public Base{
private:
    int _ofD2;
public:
    Derived2(int v){
        _ofD2 = v;
    }

    void Print(ostream& out){
        out << "D 2- " << _ofD2;
    }
};

int main(){
    vector<Base*> ds;
    ds.push_back(new Derived1(13));
    ds.push_back(new Derived1(17));
    ds.push_back(new Derived2(24));
    ds.push_back(new Derived2(28));
    for (int i = 0; i < ds.size(); i++){
        cout << *ds[i] << endl;
    }

    cout << endl << endl;
    system("pause");
    return 0;
}