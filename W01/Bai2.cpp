#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Ngay{
private:
    int ngay, thang, nam;
public:
    Ngay();
    Ngay(int ngay, int thang, int nam);
    Ngay(int ngay);
    Ngay(const string& s);
    void Xuat();
    void chuanHoa();
    ~Ngay();
};

Ngay::Ngay(){
    ngay = thang = nam = 1;
}

Ngay::Ngay(int ngay, int thang, int nam){
    this->ngay = abs(ngay);
    this->thang = abs(thang);
    this->nam = abs(nam);
    chuanHoa();
}

Ngay::Ngay(int ngay){
    this->ngay = abs(ngay);
    thang = nam = 1;
    chuanHoa();
}

Ngay::Ngay(const string& s){
    char delimeter = '-';
    stringstream ss(s);
    string token;
    getline(ss, token, delimeter); ngay = stoi(token);
    getline(ss, token, delimeter); thang = stoi(token);
    getline(ss, token, delimeter); nam = stoi(token);
    chuanHoa();
}

void Ngay::Xuat(){
    cout << ngay << "/" << thang << "/" << nam;
}

void Ngay::chuanHoa(){
    if (ngay > 30){
        int thangDu = ngay / 30;
        ngay = ngay % 30;
        thang += thangDu;
    }
    if (thang > 12){
        int namDu = thang / 12;
        thang = thang % 12;
        nam += namDu; 
    }
}

Ngay::~Ngay() {}

int main(){
    Ngay n1;
    n1.Xuat();
    cout << endl;
    Ngay n2(2, 10, 2024);
    n2.Xuat();
    cout << endl;
    Ngay n3(-100, 16, 1990);
    n3.Xuat();
    cout << endl;
    Ngay n4(1403);
    n4.Xuat();
    cout << endl;
    Ngay n5("12-12-2012");
    n5.Xuat();
    cout << endl << endl;

    system("pause");
}