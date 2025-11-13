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

    char& operator[](int idx);
    CString& operator=(const CString& other);
    friend ostream& operator<<(ostream& out, const CString& s);

    ~CString();
};

CString::CString(){
    arr = nullptr;
}

CString::CString(const char* str): CString(){
    if (str != nullptr){
        int size = strlen(str);
        arr = new char[size + 1];
        strcpy(arr, str);
    }
}

CString::CString(const CString& other): CString(other.arr){
    cout << "The copy constructor was called." << endl;
}

char& CString::operator[](int idx){
    if (idx < 0 || idx >= strlen(arr)){
        throw out_of_range("out of range");
    }
    return arr[idx];
}

CString& CString::operator=(const CString& other){
    cout << "The operator= was called." << endl;
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
    cout << "cs2(cs1)" << endl;
    CString cs2(cs1);
    cs2[iN] = '2';
    cout << "cs3 = cs1" << endl;
    CString cs3 = cs1;
    cs3[iN] = '3';
    cout << cs1 << endl << cs2 << endl << cs3 << endl;
    cout << "cs3 = cs2" << endl;
    cs3 = cs2;
    cout << cs3 << endl;
    system("pause");
    return 0;
}