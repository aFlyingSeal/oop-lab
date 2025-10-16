#include<iostream>
#include<iomanip>

using namespace std;

class ThoiGian{
private:
    int gio, phut, giay;
public:
    ThoiGian();
    ThoiGian(int giay);
    ThoiGian(int phut, int giay);
    ThoiGian(int gio, int phut, int giay);
    void Xuat();
    void chuanHoa();
    ~ThoiGian();
};

ThoiGian::ThoiGian(){
    gio = phut = giay = 0;
}

ThoiGian::ThoiGian(int giay){
    this->giay = (giay > 0) ? giay : 0;
    gio = phut = 0;
    chuanHoa();
}

ThoiGian::ThoiGian(int phut, int giay){
    this->giay = (giay > 0) ? giay : 0;
    this->phut = abs(phut);
    gio = 0;
    chuanHoa();
}

ThoiGian::ThoiGian(int gio, int phut, int giay){
    this->gio = abs(gio);
    this->phut = abs(phut);
    this->giay = (giay > 0) ? giay : 0;
    chuanHoa();
}

void ThoiGian::Xuat(){
    cout << setw(2) << setfill('0') << gio << ":"
         << setw(2) << setfill('0') << phut << ":"
         << setw(2) << setfill('0') << giay << endl;
}

void ThoiGian::chuanHoa(){
    if (giay >= 60){
        int phutDu = giay / 60;
        giay %= 60;
        phut += phutDu;
    }
    if (phut >= 60){
        int gioDu = phut / 60;
        phut %= 60;
        gio += gioDu;
    }
}

ThoiGian::~ThoiGian() {}

int main(){
    ThoiGian tg1;
    tg1.Xuat();
    ThoiGian tg2(1212);
    tg2.Xuat();
    ThoiGian tg3(125, 45);
    tg3.Xuat();
    ThoiGian tg4(12, 239, -78);
    tg4.Xuat();
}