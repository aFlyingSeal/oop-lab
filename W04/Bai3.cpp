#include<iostream>
#include<cstring>

using namespace std;

class CString{
private:
    char* arr;
public:
    CString();
    CString(const char* str);
    CString(const CString& other);

    CString& operator++();
    CString operator++(int);

    char& operator[](int idx);
    CString& operator=(const CString& other);
    friend ostream& operator<<(ostream& out, const CString& other);

    ~CString();
};

CString::CString(){
    arr = nullptr;
}

CString::CString(const char* str){
    int size = strlen(str);
    arr = new char[size + 1];
    strcpy(arr, str);
}

CString::CString(const CString& other): CString(other.arr){
}

CString& CString::operator++(){
    if (arr != nullptr){
        arr[strlen(arr) - 1]++;
    }
    return *this;
}

CString CString::operator++(int){
    CString tmp = *this;
    if (arr != nullptr){
        arr[strlen(arr) - 1]++;
    }
    return tmp;
}

char& CString::operator[](int idx){
    if (idx < 0 || idx >= strlen(arr)){
        throw out_of_range("out of range");
    }
    return arr[idx];
}

CString& CString::operator=(const CString& other){
    if (this != &other){
        delete[] arr;
        if (other.arr != nullptr){
            int size = strlen(other.arr);
            arr = new char[size + 1];
            strcpy(arr, other.arr);
        }
        else{
            arr = nullptr;
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, const CString& s){
    out << s.arr;
    return out;
}

CString::~CString(){
    if (arr != nullptr){
        delete[] arr;
        arr = nullptr;
    }
}

int main(){
    const int iN = 2;
    CString cs1("cs1_content");
    cout << cs1 << endl;
    cout << "cs1++: " << cs1++ << endl << cs1 << endl;
    cout << "++ ++cs1: " << ++ ++cs1 << endl << cs1 << endl;
    system("pause");
    return 0;
}