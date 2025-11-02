#include<iostream>
#include<iomanip>

using namespace std;

class ThoiGian{
private:
    int gio, phut, giay;

    void chuanHoa();
public:
    ThoiGian();
    ThoiGian(int soGiay);
    ThoiGian(int soPhut, int soGiay);
    ThoiGian(int soGio, int soPhut, int soGiay);

    ThoiGian operator+(const ThoiGian& other);
    ThoiGian operator+(int soGiay);
    friend ThoiGian operator+(int soGiay, const ThoiGian& tg2);

    ThoiGian operator-(const ThoiGian& other);
    friend ThoiGian operator-(int soGiay, const ThoiGian& tg2);

    bool operator<=(const ThoiGian& other);
    friend bool operator<=(int soGiay, const ThoiGian& tg2);

    friend ostream& operator<<(ostream& out, const ThoiGian& tg);
};

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
    if (gio >= 24){
        gio %= 24;
    }
}

ThoiGian::ThoiGian(){
    gio = phut = giay = 0;
}

ThoiGian::ThoiGian(int soGiay){
    gio = phut = 0;
    giay = (soGiay > 0) ? soGiay : 0;

    chuanHoa();
}

ThoiGian::ThoiGian(int soPhut, int soGiay){
    gio = 0;
    phut = abs(soPhut);
    giay = (soGiay > 0) ? soGiay : 0;

    chuanHoa();
}

ThoiGian::ThoiGian(int soGio, int soPhut, int soGiay){
    gio = abs(soGio);
    phut = abs(soPhut);
    giay = abs(soGiay);

    chuanHoa();
}

ThoiGian ThoiGian::operator+(const ThoiGian& other){
    return ThoiGian(this->gio + other.gio,
                    this->phut + other.phut,
                    this->giay + other.giay);
}

ThoiGian ThoiGian::operator+(int soGiay){
    ThoiGian other(soGiay);
    return ThoiGian(this->gio + other.gio,
                    this->phut + other.phut,
                    this->giay + other.giay);
}

ThoiGian operator+(int soGiay, const ThoiGian& tg2){
    ThoiGian tg1(soGiay);
    return ThoiGian(tg1.gio + tg2.gio,
                    tg1.phut + tg2.phut,
                    tg1.giay + tg2.giay);
}

ThoiGian ThoiGian::operator-(const ThoiGian& other){
    int t1 = gio * 3600 + phut * 60 + giay;
    int t2 = other.gio * 3600 + other.phut * 60 + other.giay;
    int delta = t1 - t2;
    if (delta < 0)
        delta = 0;
    return ThoiGian(delta);
}

ThoiGian operator-(int soGiay, const ThoiGian& tg2){
    ThoiGian tg1(soGiay);
    return tg1 - tg2;
}

bool ThoiGian::operator<=(const ThoiGian& other){
    if (gio != other.gio) return gio < other.gio;
    if (phut != other.phut) return phut < other.phut;
    return this->giay <= other.giay;
}

inline bool operator<=(int soGiay, const ThoiGian& tg2){
    ThoiGian tg1(soGiay);
    return tg1 <= tg2;
}

ostream& operator<<(ostream& out, const ThoiGian& tg){
    out << setw(2) << setfill('0') << tg.gio << ":"
        << setw(2) << setfill('0') << tg.phut << ":"
        << setw(2) << setfill('0') << tg.giay;
    return out;
}

int main(){
    ThoiGian tg1;
    ThoiGian tg2(1212);
    ThoiGian tg3(125, 45);
    ThoiGian tg4(12, 239, -78);
    ThoiGian tg5 = tg2 + tg3;
    ThoiGian tg6 = 5000 + tg2;
    ThoiGian tg7 = tg4 - tg6;
    ThoiGian tg8 = 12300 - tg4;
    ThoiGian tg9, tg10;
    if (tg8 <= tg3){
        tg9 = tg1 + tg2 + 36000;
    }
    if (tg5 <= 12345){
        tg10 = tg5 + 12345;
    }
    cout << tg1 << endl << tg2 << endl << tg3 << endl << tg4 << endl;
    cout << tg5 << endl << tg6 << endl << tg7 << endl << tg8 << endl;
    cout << tg9 << endl << tg10 << endl;
}