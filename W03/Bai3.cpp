#include<iostream>

using namespace std;

class SoPhuc{
private:
    int thuc, ao;
public:
    SoPhuc();
    SoPhuc(int n);
    SoPhuc(int thuc, int ao);
    
    friend SoPhuc operator+(int n, const SoPhuc& sp);
    friend ostream& operator<<(ostream& out, const SoPhuc& sp);
};

SoPhuc::SoPhuc(){
    thuc = ao = 0;
}

SoPhuc::SoPhuc(int n): SoPhuc(){
    thuc = n;
}

SoPhuc::SoPhuc(int thuc, int ao){
    this->thuc = thuc;
    this->ao = ao;
}

SoPhuc operator+(int n, const SoPhuc& sp){
    return SoPhuc(n + sp.thuc, sp.ao);
}

ostream& operator<<(ostream& out, const SoPhuc& sp){
    out << sp.thuc;
    if (sp.ao != 0){
        if (sp.ao > 0){
            out << " + " << sp.ao << "i\n";
        }
        else{
            out << " - " << sp.ao << "i\n";
        }
    }
    return out;
}

int main(){
    SoPhuc sp1(3, 5);
    SoPhuc sp2 = 10 + sp1;
    cout << sp1 << endl;
    cout << sp2 << endl;
    system("pause");
    return 0;
}