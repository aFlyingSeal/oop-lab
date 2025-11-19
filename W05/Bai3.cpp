#include "SLList.h"

class SoNguyenLon{
private:
    SLList<char> lCS;

    void Pow10(int n);
public:
    SoNguyenLon();
    SoNguyenLon(int cs, int scs);
    SoNguyenLon(long long n);
    SoNguyenLon(const SoNguyenLon& snl);
    SoNguyenLon(const char* s);
    ~SoNguyenLon();

    int SoCS() const;
    SoNguyenLon operator+(const SoNguyenLon& snl);
    SoNguyenLon operator-(const SoNguyenLon& snl);
    SoNguyenLon operator*(const SoNguyenLon& snl);
    bool operator>(const SoNguyenLon& snl);
    const SoNguyenLon& operator=(const SoNguyenLon& other);
    SoNguyenLon& operator+=(const SoNguyenLon& snl);
    friend SoNguyenLon operator+(int n, const SoNguyenLon& snl);
    friend SoNguyenLon operator-(int n, const SoNguyenLon& snl);
    friend ostream& operator<<(ostream& out, const SoNguyenLon& snl);
};

void SoNguyenLon::Pow10(int n){
    for (int i = 0; i < n; i++){
        lCS.insert(lCS.begin(), 0);
    }
}

SoNguyenLon::SoNguyenLon(){
    lCS.push_back(0);
}

SoNguyenLon::SoNguyenLon(int cs, int csc){
    int csR = cs;
    if (csR < cs){
        csR = 1;
    }
    if (csR > cs){
        csR = 9;
    }
    int soCS = abs(csc);
    if (soCS < 1){
        soCS = 1;
    }
    for (int i = 0; i < soCS; i++){
        lCS.push_back(csR);
    }
}

SoNguyenLon::SoNguyenLon(long long n){
    if (n == 0){
        lCS.push_back(0);
        return;
    }
    long long temp = n;
    while (temp > 0){
        lCS.push_back(temp % 10);
        temp /= 10;
    }
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon& snl){
    lCS = snl.lCS;
}

SoNguyenLon::SoNguyenLon(const char* s){
    int size = strlen(s);
    for (int i = 0; i < size; i++){
        lCS.push_back(s[i]);
    }
}

SoNguyenLon::~SoNguyenLon(){}

int SoNguyenLon::SoCS() const{
    return lCS.size();
}

bool SoNguyenLon::operator>(const SoNguyenLon& snl){
    if (lCS.size() > snl.lCS.size()){
        return true;
    }
    if (lCS.size() < snl.lCS.size()){
        return false;
    }
    for (int i = lCS.size() - 1; i >= 0; i--){
        if (lCS[i] == snl.lCS[i]){
            continue;
        }
        if (lCS[i] > snl.lCS[i]){
            return true;
        }
        return false;
    }
    return false;
}

const SoNguyenLon& SoNguyenLon::operator=(const SoNguyenLon& snl){
    lCS = snl.lCS;
    return *this;
}

SoNguyenLon& SoNguyenLon::operator+=(const SoNguyenLon& snl){
    *this = *this + snl;
    return *this;
}

SoNguyenLon SoNguyenLon::operator+(const SoNguyenLon& snl){
    SoNguyenLon snlKQ;
    snlKQ.lCS.clear();
    const SoNguyenLon* snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
    const SoNguyenLon* snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;
    int nho = 0, temp;
    for (int i = 0; i < snlSCSMin->SoCS(); i++){
        temp = lCS[i] + snl.lCS[i] + nho;
        snlKQ.lCS.push_back(temp % 10);
        nho = temp / 10;
    }
    for (int i = snlSCSMin->SoCS(); i < snlSCSMax->SoCS(); i++){
        temp = snlSCSMax->lCS[i] + nho;
        snlKQ.lCS.push_back(temp % 10);
        nho = temp / 10;
    }
    if (nho > 0){
        snlKQ.lCS.push_back(1);
    }
    return snlKQ;
}

SoNguyenLon SoNguyenLon::operator-(const SoNguyenLon& snl){
    if (lCS.size() < snl.lCS.size()){
        return SoNguyenLon((long long)0);
    }
    SoNguyenLon snlKQ;
    snlKQ.lCS.clear();
    int muon = 0, temp;
    int minSoCS = min(lCS.size(), snl.lCS.size());

    for (int i = 0; i < minSoCS; i++){
        temp = lCS[i] - snl.lCS[i] - muon;
        if (temp < 0){
            temp += 10;
            muon = 1;
        }
        else{
            muon = 0;
        }
        snlKQ.lCS.push_back(temp);
    }
    for (int i = minSoCS; i < lCS.size(); i++){
        temp = lCS[i] - muon;
        if (temp < 0){
            temp += 10;
            muon = 1;
        }
        else{
            muon = 0;
        }
        snlKQ.lCS.push_back(temp);
    }
    while (snlKQ.lCS.size() > 1 && snlKQ.lCS[snlKQ.lCS.size() - 1] == 0){
        snlKQ.lCS.pop_back();
    }
    return snlKQ;
}

SoNguyenLon SoNguyenLon::operator*(const SoNguyenLon& snl){
    SoNguyenLon snlKQ, *psnlTemp;
    const SoNguyenLon* snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
    const SoNguyenLon* snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;
    int nho = 0, temp;
    for (int i = 0; i < snlSCSMin->SoCS(); i++){
        psnlTemp = new SoNguyenLon;
        psnlTemp->lCS.clear();
        nho = 0;
        for (int j = 0; j < snlSCSMax->SoCS(); j++){
            temp = snlSCSMin->lCS[i] * snlSCSMax->lCS[j] + nho;
            psnlTemp->lCS.push_back(temp % 10);
            nho = temp / 10;
        }
        if (nho > 0){
            psnlTemp->lCS.push_back(nho);
        }
        psnlTemp->Pow10(i);
        snlKQ += *psnlTemp;
        delete psnlTemp;
    }
    return snlKQ;
}

SoNguyenLon operator+(int n, const SoNguyenLon& snl){
    SoNguyenLon snl_n(n);
    return snl_n + snl;
}

SoNguyenLon operator-(int n, const SoNguyenLon& snl){
    SoNguyenLon snl_n(n);
    return snl_n - snl;
}

ostream& operator<<(ostream& out, const SoNguyenLon& snl){
    for (int i = snl.lCS.size() - 1; i >= 0; i--){
        out << (int)snl.lCS[i];
    }
    return out;
}

int main(){
    const int iTest = 78912;
    SoNguyenLon snl1(123);
    SoNguyenLon snl2(40000);
    cout << snl1 << " + " << snl2 << " = ";
    cout << (snl1 + snl2) << endl;
    cout << snl1 << " * " << snl2 << " = ";
    cout << (snl1 * snl2) << endl;
    cout << snl1 << " - " << snl2 << " = ";
    cout << (snl1 - snl2) << endl;
    cout << snl2 << " - " << snl1 << " = ";
    cout << (snl2 - snl1) << endl;
    cout << iTest << " - " << snl2 << " = ";
    cout << (iTest - snl2) << endl;

    system("pause");
    return 0;
}