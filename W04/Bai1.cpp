#include<iostream>
#include<cstring>

using namespace std;

class CString{
private:
    char* arr;
public:
    CString();
    CString(const char* str);
    
    char& operator[](int idx);
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

char& CString::operator[](int idx){
    if (idx < 0 || idx >= strlen(arr)){
        throw out_of_range("out of range");
    }
    return arr[idx];
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
    cout << "cs1[" << iN << "] = " << cs1[iN] << endl;
    cs1[iN] = 'N';
    system("pause");
    return 0;
}