#include<iostream>

using namespace std;

class SoPhuc{
private:
    int thuc, ao;
public:
    SoPhuc();
    SoPhuc(int n);
    SoPhuc(int thuc, int ao);
    SoPhuc(const SoPhuc& other);

    SoPhuc operator+(const SoPhuc& other);
    SoPhuc operator+(int n);

    void operator<<(ostream& out);
};

SoPhuc::SoPhuc(){
    thuc = ao = 0;
}

SoPhuc::SoPhuc(int n): SoPhuc(){
    cout << "using...";
    thuc = n;
}

SoPhuc::SoPhuc(int thuc, int ao){
    this->thuc = thuc;
    this->ao = ao;
}

SoPhuc::SoPhuc(const SoPhuc& other){
    this->thuc = other.thuc;
    this->ao = other.ao;
}

SoPhuc SoPhuc::operator+(const SoPhuc& other){
    SoPhuc kq;
    kq.thuc = this->thuc + other.thuc;
    kq.ao = this->ao + other.ao;
    return kq;
}

SoPhuc SoPhuc::operator+(int n){
    SoPhuc kq;
    kq.thuc = thuc + n;
    kq.ao = ao;
    return kq;
}

void SoPhuc::operator<<(ostream& out){
    out << thuc;
    if (ao != 0){
        if (ao < 0){
            out << " - " << ao << "i";
            return;
        }
        out << " + " << ao << "i";
    }
}

int main(){
    SoPhuc sp1(3, 5);
    SoPhuc sp3 = sp1 + 10;
    sp1.operator<<(cout);
    cout << endl;
    sp3.operator<<(cout);
    cout << endl;
    system("pause");
    return 0;
}