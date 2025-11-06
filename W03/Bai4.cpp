#include<iostream>

using namespace std;

class Ngay{
private:
    int ngay, thang, nam;

    static int mangNgay[13];
    static bool laNamNhuan(int nam);

    void chuanHoa();
public:
    Ngay();
    Ngay(int soNgay);
    Ngay(int ngay, int thang, int nam);

    Ngay operator+(const Ngay& other);
    Ngay operator+(int soNgay);
    friend Ngay operator+(int soNgay, const Ngay& n);

    Ngay operator-(const Ngay& other);
    Ngay operator-(int soNgay);
    friend Ngay operator-(int soNgay, const Ngay& n);

    bool operator>(const Ngay& other);

    friend ostream& operator<<(ostream& out, const Ngay& n);
};

int Ngay::mangNgay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Ngay::laNamNhuan(int nam){
    return (nam % 400 == 0) || (nam % 100 != 0 && nam % 4 == 0);
}

void Ngay::chuanHoa(){
    ngay = abs(ngay);
    thang = abs(thang);
    nam = abs(nam);

    if (ngay == 0) ngay = 1;
    if (thang == 0) thang = 1;
    if (nam == 0) nam = 1;

    while (thang > 12){
        thang -= 12;
        nam++;
    }

    int ngayTrongThang;
    if (thang == 2 && laNamNhuan(nam))
        ngayTrongThang = 29;
    else
        ngayTrongThang = mangNgay[thang];

    while (ngay > ngayTrongThang){
        ngay -= ngayTrongThang;
        thang++;
        if (thang > 12){
            thang = 1;
            nam++;
        }
        if (thang == 2 && laNamNhuan(nam))
            ngayTrongThang = 29;
        else
            ngayTrongThang = mangNgay[thang];
    }
}

Ngay::Ngay(){
    ngay = thang = nam = 1;
}

Ngay::Ngay(int soNgay){
    ngay = abs(soNgay);
    if (ngay == 0) ngay = 1;
    thang = nam = 1;

    chuanHoa();
}

Ngay::Ngay(int ngay, int thang, int nam){
    this->ngay = ngay;
    this->thang = thang;
    this->nam = nam;

    chuanHoa();
}

Ngay Ngay::operator+(const Ngay& other){
    Ngay kq(this->ngay + other.ngay,
            this->thang + other.thang,
            this->nam + other.nam);
    return kq;
}

Ngay Ngay::operator+(int soNgay){
    Ngay kq(this->ngay + soNgay, this->thang, this->nam);
    return kq;
}

Ngay operator+(int soNgay, const Ngay& n){
    Ngay kq(soNgay + n.ngay, n.thang, n.nam);
    return kq;
}

Ngay Ngay::operator-(const Ngay& other){
    Ngay kq(this->ngay - other.ngay,
            this->thang - other.thang,
            this->nam - other.nam);
	return kq;
}	

Ngay Ngay::operator-(int soNgay){
    Ngay kq(this->ngay - soNgay, this->thang, this->nam);
	return kq;
}

Ngay operator-(int soNgay, const Ngay& n){
    Ngay kq(soNgay - n.ngay, n.thang, n.nam);
	return kq;
}

bool Ngay::operator>(const Ngay& other){
    if (this->nam != other.nam){
        return this->nam > other.nam;
    }
    if (this->thang != other.thang){
        return this->thang > other.thang;
    }
    return this->ngay > other.ngay;
}

ostream& operator<<(ostream& out, const Ngay& n){
    out << n.ngay << "/" << n.thang << "/" << n.nam;
	return out;
}

int main(){
    Ngay n1;
    Ngay n2(2, 10, 2014);
    Ngay n3(-10, 16, 2000);
    Ngay n4(1000);
    Ngay n5 = n2 + n3;
    Ngay n6 = n1 + 5000;
    Ngay n7 = 1234 + n4;
    Ngay n8 = 190 + n6 + n7;
    Ngay n9 = n8 - n6;
    Ngay n10 = 12000 - n9;
    if (n10 > n6){
        n10 = n2 - 1000 + n6;
    }
    cout << n1 << endl << n2 << endl << n3 << endl << n4 << endl;
    cout << n5 << endl << n6 << endl << n7 << endl << n8 << endl;
    cout << n9 << endl << n10 << endl;
    system("pause");
    return 0;
}