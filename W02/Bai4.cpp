#include<iostream>
#include<cstring>

using namespace std;

class SoNguyenLon{
private:
    int size;
    char* n;

    static SoNguyenLon maxSNL;

    void capNhatSNLMax(){
        if (*this > maxSNL){
            maxSNL = *this;
        }
    }
public:
    SoNguyenLon();
    SoNguyenLon(const char* x);
    SoNguyenLon(const SoNguyenLon& other);
    SoNguyenLon(int d, int size);
    SoNguyenLon(int x);

    bool operator > (const SoNguyenLon& other);
    SoNguyenLon& operator = (const SoNguyenLon& other);

    SoNguyenLon Tru(const SoNguyenLon& other);
    SoNguyenLon Cong(int hangSo);

    static SoNguyenLon HieuVoiHangSo(int hangSo, const SoNguyenLon& snl);
    static SoNguyenLon SNLMax();

    void In(ostream& out);

    ~SoNguyenLon();
};

SoNguyenLon::SoNguyenLon(){
    size = 1;
    n = new char[size + 1];
    strcpy(n, "0");

    capNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(const char* x){
    size = strlen(x);
    n = new char[size + 1];
    strcpy(n, x);

    capNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon& other){
    size = other.size;
    n = new char[size + 1];
    strcpy(n, other.n);
}

SoNguyenLon::SoNguyenLon(int d, int size){
    this->size = size;
    n = new char[size + 1];
    for (int i = 0; i < size; i++){
        n[i] = char(d + '0');
    }
    n[size] = '\0';

    capNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(int x){
    int xCpy = x, count = 0;
    while (xCpy > 0){
        xCpy /= 10;
        count++;
    }
    size = count;
    n = new char[size + 1];
    for (int i = size - 1; i >= 0; i--){
        n[i] = char((x % 10) + '0');
        x /= 10;
    }
    n[size] = '\0';

    capNhatSNLMax();
}

bool SoNguyenLon::operator > (const SoNguyenLon& other){
    if (size > other.size)
        return true;
    if (size < other.size)
        return false;
    for (int i = 0; i < size; i++){
        if (n[i] > other.n[i])
            return true;
        if (n[i] < other.n[i])
            return false;
    }
    return false;
}

SoNguyenLon& SoNguyenLon::operator = (const SoNguyenLon& other){
    if (this != &other){
        delete[] n;
        size = other.size;
        n = new char[size + 1];
        strcpy(n, other.n);
    }
    return *this;
}

SoNguyenLon SoNguyenLon::Tru(const SoNguyenLon& other){
    if (size < other.size){
        return SoNguyenLon();
    }

    int i, j, k = 0;
    char* tmp = new char[101];

    i = size - 1; j = other.size - 1;
    int muon = 0;

    while (j >= 0){
        int hieu = (n[i--] - '0') - (other.n[j--] - '0') - muon;
        if (hieu < 0){
            hieu += 10;
            muon = 1;
        }
        else
            muon = 0;
        tmp[k++] = char(hieu + '0');
    }
    
    while (i >= 0){
        // if (n[i] == '0' && muon > 0){
        //     tmp[k++] = '9';
        //     i--;
        //     continue;
        // }
        // int hieu = (n[i] - '0') - muon;
        // if (hieu > 0 || muon > 0){
        //     tmp[k++] = char(hieu + '0');
        // }
        // muon = 0;
        // i--;
        int hieu = (n[i] - '0') - muon;
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

SoNguyenLon SoNguyenLon::Cong(int hangSo){
    SoNguyenLon other(hangSo);

    int i, j, k = 0;
    char *tmp = new char[101];

    i = size - 1; j = other.size - 1;
    int muon = 0;
    while (i >= 0 || j >= 0 || muon > 0){
        int n1 = (i >= 0) ? n[i] - '0' : 0;
        int n2 = (j >= 0) ? other.n[j] - '0' : 0;
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

SoNguyenLon SoNguyenLon::HieuVoiHangSo(int hangSo, const SoNguyenLon& snl){
    SoNguyenLon hs(hangSo);
    SoNguyenLon res(snl);
    return hs.Tru(res);
}

SoNguyenLon SoNguyenLon::SNLMax(){
    return maxSNL;
}

void SoNguyenLon::In(ostream& out){
    out << n;
}

SoNguyenLon::~SoNguyenLon(){
    size = 0;
    delete[] n;
    n = nullptr;
}

SoNguyenLon SoNguyenLon::maxSNL("0");

int main(){
    SoNguyenLon snl1;
    SoNguyenLon snl2("1234567");
    SoNguyenLon snl3(3, 14);
    SoNguyenLon snl4(9, 20);
    SoNguyenLon snl5 = snl3.Tru(snl2);
    SoNguyenLon snl6 = SoNguyenLon::HieuVoiHangSo(45678910, snl2);
    SoNguyenLon snl7 = snl4.Tru(snl3).Cong(123456789);
    snl1.In(cout);
    cout << endl;
    snl2.In(cout);
    cout << endl;
    snl3.In(cout);
    cout << endl;
    snl4.In(cout);
    cout << endl;
    snl5.In(cout);
    cout << endl;
    snl6.In(cout);
    cout << endl;
    snl7.In(cout);
    cout << endl;

    cout << "SoNguyenLon Max:" << endl;
    SoNguyenLon::SNLMax().In(cout);
    cout << endl;
    system("pause");
    return 0;
}