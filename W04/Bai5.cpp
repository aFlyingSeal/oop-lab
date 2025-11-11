#include "LinkedList.h"

class SoNguyenLon{
private:
    LinkedList<int> list;
    int size;

    void trimZero();
public:
    SoNguyenLon();
    SoNguyenLon(int x);
    SoNguyenLon(int x, int n);
    SoNguyenLon(const SoNguyenLon& other);

    bool operator>(const SoNguyenLon& other);
    SoNguyenLon& operator=(const SoNguyenLon& other);

    SoNguyenLon operator-(const SoNguyenLon& other);
    friend SoNguyenLon operator-(int x, const SoNguyenLon& snl2); 

    SoNguyenLon operator+(const SoNguyenLon& other);
    SoNguyenLon operator+(int x);

    friend SoNguyenLon operator*(const SoNguyenLon& snl1, const SoNguyenLon& snl2);

    friend ostream& operator<<(ostream& out, const SoNguyenLon& snl);

    ~SoNguyenLon();
};

void SoNguyenLon::trimZero(){
    while (size > 1 && list[0] == 0){
        list.RemoveHead();
        size--;
    }
}

SoNguyenLon::SoNguyenLon(){
    list.AddHead(0);
    size = 1;
}

SoNguyenLon::SoNguyenLon(int x){
    int tmp = x;
    if (x == 0){
        list.AddHead(0);
        size = 1;
    }
    else{
        size = 0;
        while (tmp > 0){
            list.AddHead(tmp % 10);
            tmp /= 10;
            size++;
        }
    }
}

SoNguyenLon::SoNguyenLon(int x, int n){
    size = n;
    for (int i = 1; i <= n; i++){
        list.AddTail(x);
    }
    trimZero();
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon& other){
    this->size = other.size;
    for (int i = 0; i < size; i++){
        this->list.AddTail(other.list[i]);
    }
}

bool SoNguyenLon::operator>(const SoNguyenLon& other){
    if (size > other.size)
        return true;
    if (size < other.size)
        return false;
    for (int i = 0; i < size; i++){
        if (list[i] > other.list[i])
            return true;
        if (list[i] < other.list[i])
            return false;
    }
    return false;
}

SoNguyenLon& SoNguyenLon::operator=(const SoNguyenLon& other){
    if (this != &other){
        list.~LinkedList<int>();
        list.~LinkedList<int>();
        size = other.size;
        for (int i = 0; i < size; i++){
            list.AddTail(other.list[i]);
        }
    }
    return *this;
}

SoNguyenLon SoNguyenLon::operator-(const SoNguyenLon& other){
    if (size < other.size){
        return SoNguyenLon(0);
    }
    SoNguyenLon res;
    res.list.RemoveHead();
    res.size = 0;

    int i = size - 1;
    int j = other.size - 1;
    int muon = 0;

    while (j >= 0){
        int hieu = list[i--] - other.list[j--] - muon;
        if (hieu < 0){
            hieu += 10;
            muon = 1;
        }
        else
            muon = 0;
        res.list.AddHead(hieu);
        res.size++;
    }

    while (i >= 0){
        int hieu = list[i--] - muon;
        if (hieu < 0){
            hieu += 10;
            muon = 1;
        }
        else
            muon = 0;
        res.list.AddHead(hieu);
        res.size++;
    }

    res.trimZero();
    return res;
}

SoNguyenLon operator-(int x, const SoNguyenLon& snl2){
    SoNguyenLon snl1(x);
    return snl1 - snl2;
}

SoNguyenLon SoNguyenLon::operator+(const SoNguyenLon& other){
    SoNguyenLon res;
    res.list.RemoveHead();
    res.size = 0;

    int i = size - 1;
    int j = other.size - 1;
    int muon = 0;

    while (i >= 0 || j >= 0 || muon > 0){
        int n1 = (i >= 0) ? list[i] : 0;
        int n2 = (j >= 0) ? other.list[j] : 0;
        int tong = n1 + n2 + muon;
        res.list.AddHead(tong % 10);
        res.size++;
        muon = tong / 10;
        if (i >= 0)
            i--;
        if (j >= 0)
            j--;
    }

    res.trimZero();
    return res;
}

SoNguyenLon SoNguyenLon::operator+(int x){
    SoNguyenLon other(x);
    return *this + other;
}

SoNguyenLon operator*(const SoNguyenLon& snl1, const SoNguyenLon& snl2){
    SoNguyenLon res;
    res.list.RemoveHead();
    res.size = 0;

    for (int i = 0; i < snl1.size + snl2.size; i++){
        res.list.AddTail(0);
        res.size++;
    }

    for (int i = snl1.size - 1; i >= 0; i--){
        int muon = 0;
        for (int j = snl2.size - 1; j >= 0; j--){
            int idx = (snl1.size - 1 - i) + (snl2.size - 1 - j);
            int tich = snl1.list[i] * snl2.list[j] + res.list[res.size - 1 - idx] + muon;
            muon = tich / 10;
            res.list[res.size - 1 - idx] = tich % 10;
        }
        if (muon > 0){
            int idx = (snl1.size - 1 - i) + snl2.size;
            res.list[res.size - 1 - idx] += muon;
        }
    }

    res.trimZero();
    return res;
}

ostream& operator<<(ostream& out, const SoNguyenLon& snl){
    for (int i = 0; i < snl.size; i++){
        out << snl.list[i];
    }
    return out;
}

SoNguyenLon::~SoNguyenLon(){
    list.~LinkedList<int>();
    size = 0;
}

int main(){
    SoNguyenLon snl1;
    SoNguyenLon snl2(44667733);
    SoNguyenLon snl3(5, 9);
    SoNguyenLon snl4(7, 30);
    SoNguyenLon snl5 = snl3 - snl2;
    SoNguyenLon snl6 = 1098765432 - snl2;
    SoNguyenLon snl7 = snl4 - snl3 + 123456789;
    SoNguyenLon snl8 = snl2 * snl3;

    cout << snl1 << endl << snl2 << endl << snl3 << endl;
    cout << snl4 << endl << snl5 << endl << snl6 << endl;
    cout << snl7 << endl << snl8 << endl;
    system("pause");
    return 0;
}