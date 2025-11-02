#include<iostream>
#include<cstring>

using namespace std;

class SoNguyenLon{
private:
    int size;
    char* str;

    static SoNguyenLon maxSNL;

    void capNhatSNLMax();
public:
    SoNguyenLon();
    SoNguyenLon(int n);
    SoNguyenLon(const SoNguyenLon& other);
    SoNguyenLon(int chuSo, int size);
    SoNguyenLon(char* x);

    bool operator>(const SoNguyenLon& other);

    SoNguyenLon operator-(const SoNguyenLon& other);
    friend SoNguyenLon operator-(int x, const SoNguyenLon& n);

    SoNguyenLon operator+(int x);

    static SoNguyenLon SNLMax();

    friend ostream& operator<<(ostream& out, const SoNguyenLon& n);

    ~SoNguyenLon();
};

void SoNguyenLon::capNhatSNLMax(){
    if (this != &maxSNL && *this > maxSNL){
        maxSNL = *this;
    }
}

SoNguyenLon::SoNguyenLon(){
    size = 1;
    str = new char[size + 1];
    strcpy(str, "0");
}

SoNguyenLon::SoNguyenLon(int n){
    int nCpy = n, count = 0;
    while (nCpy > 0){
        nCpy /= 10;
        count++;
    }
    size = count;
    str = new char[size + 1];
    for (int i = size - 1; i >= 0; i--){
        str[i] = char((n % 10) + '0');
        n /= 10;
    }
    str[size] = '\0';

    capNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon& other){
    size = other.size;
    str = new char[size + 1];
    strcpy(str, other.str);
}

SoNguyenLon::SoNguyenLon(int chuSo, int size){
    this->size = size;
    str = new char[size + 1];
    for (int i = 0; i < size; i++){
        str[i] = char(chuSo + '0');
    }
    str[size] = '\0';

    capNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(char* x){
    size = strlen(x);
    str = new char[size + 1];
    strcpy(str, x);

    capNhatSNLMax();
}

bool SoNguyenLon::operator>(const SoNguyenLon& other){
    if (size > other.size)
        return true;
    if (size < other.size)
        return false;
    for (int i = 0; i < size; i++){
        if (str[i] > other.str[i])
            return true;
        if (str[i] < other.str[i])
            return false;
    }
    return false;
}

SoNguyenLon SoNguyenLon::operator-(const SoNguyenLon& other){
    if (size < other.size){
        return SoNguyenLon();
    }

    int i, j, k = 0;
    char* tmp = new char[101];

    i = size - 1; j = other.size - 1;
    int muon = 0;

    while (j >= 0){
        int hieu = (str[i--] - '0') - (other.str[j--] - '0') - muon;
        if (hieu < 0){
            hieu += 10;
            muon = 1;
        }
        else
            muon = 0;
        tmp[k++] = char(hieu + '0');
    }
    
    while (i >= 0){
        int hieu = (str[i] - '0') - muon;
        if (hieu < 0){
            hieu += 10;
            muon = 1;
        }
        else
            muon = 0;
        tmp[k++] = char(hieu + '0');
        i--;
    }

    while (k > 1 && tmp[k - 1] == '0')
        k--;

    i = 0, j = k - 1;
    while (i < j){
        char buffer = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = buffer;
        i++; j--;
    }
    tmp[k] = '\0';

    SoNguyenLon res(tmp);
    delete[] tmp;
    return res;
}

SoNguyenLon operator-(int x, const SoNguyenLon& n){
    SoNguyenLon other(x);
    return other - n;
}

SoNguyenLon SoNguyenLon::operator+(int x){
    SoNguyenLon other(x);

    int i, j, k = 0;
    char *tmp = new char[101];

    i = size - 1; j = other.size - 1;
    int muon = 0;
    while (i >= 0 || j >= 0 || muon > 0){
        int n1 = (i >= 0) ? str[i] - '0' : 0;
        int n2 = (j >= 0) ? other.str[j] - '0' : 0;
        int tong = n1 + n2 + muon;
        tmp[k++] = char(tong % 10 + '0');
        muon = tong / 10;
        if (i >= 0)
            i--;
        if (j >= 0)
            j--;
    }

    i = 0, j = k - 1;
    while (i < j){
        char buffer = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = buffer;
        i++; j--;
    }
    tmp[k] = '\0';

    SoNguyenLon res(tmp);
    delete[] tmp;
    return res;
}

SoNguyenLon SoNguyenLon::SNLMax(){
    return maxSNL;
}

ostream& operator<<(ostream& out, const SoNguyenLon& n){
    out << n.str;
    return out;
}

SoNguyenLon::~SoNguyenLon(){
    size = 0;
    delete[] str;
    str = nullptr;
}

SoNguyenLon SoNguyenLon::maxSNL = SoNguyenLon();

int main(){
    SoNguyenLon snl1;
    SoNguyenLon snl2(1234567);
    SoNguyenLon snl3(3, 14);
    SoNguyenLon snl4(9, 20);
    SoNguyenLon snl5 = snl3 - snl2;
    SoNguyenLon snl6 = 45678910 - snl2;
    SoNguyenLon snl7 = snl4 - snl3 + 123456789;

    cout << snl1 << endl << snl2 << endl << snl3 << endl;
    cout << snl4 << endl << snl5 << endl << snl6 << endl;
    cout << snl7 << endl;

    cout << "SoNguyenLon Max:" << endl;
    cout << SoNguyenLon::SNLMax() << endl;
    system("pause");
    return 0;
}