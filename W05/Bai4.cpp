#include "SLList.h"

class MyString{
private:
    char *arr;
    int size;
public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);
    friend MyString operator+(const char* s, const MyString& ms);
    friend MyString operator+(const MyString& ms1, const MyString& ms2);

    friend ostream& operator<<(ostream& out, const MyString& ms);

    SLList<MyString> Split(SLList<char> delimeters, bool removeEmpty);
};

MyString::MyString(){
    arr = nullptr;
    size = 0;
}

MyString::MyString(const char* s){
    int nSize = strlen(s);
    arr = new char[nSize + 1];
    strcpy(arr, s);
    size = nSize;
}

MyString::MyString(const MyString& other){
    size = other.size;
    arr = new char[size + 1];
    strcpy(arr, other.arr);
}

MyString::~MyString(){
    delete[] arr;
    arr = nullptr;
    size = 0;
}

MyString& MyString::operator=(const MyString& other){
    if (this != &other){
        delete[] arr;
        size = other.size;
        arr = new char[size + 1];
        strcpy(arr, other.arr);
    }
    return *this;
}

MyString operator+(const char* s, const MyString& ms){
    int size_s = strlen(s);
    int size_ms = ms.size;
    char* resStr = new char[size_s + size_ms + 1];
    strcpy(resStr, s);
    strcat(resStr, ms.arr);
    MyString res(resStr);
    delete[] resStr;
    return res;
}

MyString operator+(const MyString& ms1, const MyString& ms2){
    int size_ms1 = ms1.size;
    int size_ms2 = ms2.size;
    char* resStr = new char[size_ms1 + size_ms2 + 1];
    strcpy(resStr, ms2.arr);
    strcat(resStr, ms1.arr);
    MyString res(resStr);
    delete[] resStr;
    return res;
}

SLList<MyString> MyString::Split(SLList<char> delimeters, bool removeEmpty){
    SLList<MyString> res;

    // put all delimeters in an array
    int deliCount = delimeters.size();
    char* delimeter = new char[deliCount + 1];
    for (int i = 0; i < deliCount; i++){
        delimeter[i] = delimeters[i];
    }
    delimeter[deliCount] = '\0';

    // processing logic
    if (!removeEmpty){
        int start = 0;
        for (int i = 0; i < size; i++){
            bool isDelimeter = false;
            if (i < size){
                char cur = arr[i];
                for (int j = 0; j < deliCount; j++){
                    if (cur == delimeter[j]){
                        isDelimeter = true;
                        break;
                    }
                }
            }
            if (i == size || isDelimeter){
                int len = i - start;
                if (len > 0 || (len == 0 && !removeEmpty)){
                    char* split = new char[len + 1];
                    for (int j = 0; j < len; j++){
                        split[j] = arr[start + j];
                    }
                    split[len] = '\0';
                    res.push_back(MyString(split));
                    delete[] split;
                }
                start = i + 1;
            }
        }
    }
    else{
        char* arrCpy = new char[size + 1];
        strcpy(arrCpy, arr);

        char* split = strtok(arrCpy, delimeter);
        while (split != nullptr){
            res.push_back(MyString(split));
            split = strtok(nullptr, delimeter);
        }
        delete[] arrCpy;
    }

    delete[] delimeter;
    return res;
}

ostream& operator<<(ostream& out, const MyString& ms){
    for (int i = 0; i < ms.size; i++){
        out << ms.arr[i];
    }
    return out;
}

int main(){
    MyString ms1("abcdsf");
    MyString ms2 = "____" + ms1;
    MyString ms3 = ms1 + ms2;
    cout << "ms1 = " << ms1 << endl;
    cout << "ms2 = " << ms2 << endl;
    cout << "ms3 = " << ms3 << endl << endl;
    MyString ms = "a,b,c;d.r;.h;e,w__u,t.f;j_..";
    SLList<char> arrChar;
    arrChar.push_back(',');
    arrChar.push_back('.');
    arrChar.push_back(';');
    SLList<MyString> vMs = ms.Split(arrChar, false);
    cout << "Split:" << endl;
    for (SLList<MyString>::Iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
    {
        cout << *itMS << " ";
    }
    cout << endl << "size= " << vMs.size() << endl << endl;
    vMs = ms.Split(arrChar, true);
    cout << "Split co loai bo empty:" << endl;
    for (SLList<MyString>::Iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
    {
        cout << *itMS << " ";
    }
    cout << endl << "size= " << vMs.size() << endl << endl;

    system("pause");
    return 0;
}