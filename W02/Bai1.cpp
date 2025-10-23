#include<iostream>

using namespace std;

class SoPhuc{
private:
    int thuc, ao;
    int sl;
    static int ssl;
public:
    SoPhuc();
    SoPhuc(int thuc, int ao);
    SoPhuc(const SoPhuc& other);

    SoPhuc cong(const SoPhuc& other);
    int SoLuongSP();
    static int SSoLuongSP();

    ~SoPhuc();
};

SoPhuc::SoPhuc(){
    thuc = ao = 0;
    sl++;
    ssl++;
}

SoPhuc::SoPhuc(int thuc, int ao){
    this->thuc = thuc;
    this->ao = ao;
    sl++;
    ssl++;
}

SoPhuc::SoPhuc(const SoPhuc& other){
    this->thuc = other.thuc;
    this->ao = other.ao;
    sl++;
    ssl++;
}

SoPhuc SoPhuc::cong(const SoPhuc& other){
    SoPhuc kq;
    kq.thuc = this->thuc + other.thuc;
    kq.ao = this->ao + other.ao;
    return kq;
}

int SoPhuc::SoLuongSP(){
    return sl;
}

int SoPhuc::SSoLuongSP(){
    return ssl;
}

SoPhuc::~SoPhuc(){
    sl--;
    ssl--;
}

int SoPhuc::ssl = 0;

int main(){
    SoPhuc sp1;
    SoPhuc sp2(5, 10);
    SoPhuc sp3(sp1);
    SoPhuc sp4 = sp2.cong(sp1);
    cout << SoPhuc::SSoLuongSP() << endl;
    {
        SoPhuc sp5;
        SoPhuc sp6 = sp2.cong(sp4);
    }
    cout << sp4.SoLuongSP() << endl;
    cout << SoPhuc::SSoLuongSP() << endl;

    system("pause");
}