#include<iostream>

using namespace std;

class MangSoNguyen{
private:
    int *ptr;
    int size;
public:
    MangSoNguyen();
    MangSoNguyen(int size);
    MangSoNguyen(int *arr, int size);
    MangSoNguyen(const MangSoNguyen& other);
    void Xuat();
    ~MangSoNguyen();
};

MangSoNguyen::MangSoNguyen(){
    ptr = nullptr;
    size = 0;
}

MangSoNguyen::MangSoNguyen(int size){
    this->size = size;
    ptr = new int[size];
    for (int i = 0; i < size; i++){
        ptr[i] = 0;
    }
}

MangSoNguyen::MangSoNguyen(int *arr, int size){
    this->size = size;
    ptr = new int[size];
    for (int i = 0; i < size; i++){
        ptr[i] = arr[i];
    }
}

MangSoNguyen::MangSoNguyen(const MangSoNguyen& other){
    this->size = other.size;
    this->ptr = new int[size];
    for (int i = 0; i < size; i++){
        ptr[i] = other.ptr[i];
    }
}

void MangSoNguyen::Xuat(){
    if (ptr == nullptr){
        cout << "Mang rong\n";
        return;
    }
    for (int i = 0; i < size; i++)
        cout << ptr[i] << " ";
    cout << endl;
}

MangSoNguyen::~MangSoNguyen(){
    size = 0;
    delete[] ptr;
    ptr = nullptr;
}

int main(){
    MangSoNguyen msn1;
    msn1.Xuat();
    MangSoNguyen msn2(5);
    msn2.Xuat();
    int arr[10];
    for (int i = 0; i < 8; i++){
        arr[i] = i * i;
    }
    MangSoNguyen msn3(arr, 8);
    msn3.Xuat();
    MangSoNguyen msn4(msn3);
    msn4.Xuat();
}