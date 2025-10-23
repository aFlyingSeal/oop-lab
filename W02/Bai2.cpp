#include<iostream>

using namespace std;

class Ngay{
private:
    int ngay, thang, nam;
    static int mangNgay[12];
    static bool laNamNhuan(int nam);
public:
    Ngay();
    Ngay(int soNgay);
    void Xuat(ostream& os);
    ~Ngay();
};

int Ngay::mangNgay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Ngay::laNamNhuan(int nam){
    return (nam % 400 == 0) || (nam % 100 != 0 && nam % 4 == 0);
}

Ngay::Ngay(){
    ngay = thang = nam = 1;
}

Ngay::Ngay(int soNgay){
    ngay = abs(soNgay);
    thang = nam = 1;
    if (ngay == 0){
        ngay = 1;
        return;
    }
	while (true){
		int ngayTrongNam = laNamNhuan(nam) ? 366 : 365;
		if (soNgay > ngayTrongNam){
			soNgay -= ngayTrongNam;
			nam++;
		}
		else
			break;
	}
	if (laNamNhuan(nam))
		mangNgay[1] = 29;
	while (soNgay > mangNgay[thang]){
		soNgay -= mangNgay[thang];
		thang++;
	}
	ngay = soNgay;
}

void Ngay::Xuat(ostream& os){
    os << ngay << "-" << thang << "-" << nam; 
}

Ngay::~Ngay() {}


int main(){
    Ngay n1;
    Ngay n2(1000);
    Ngay n3(2000);
    Ngay n4(3000);
    Ngay n5(4000);
    n1.Xuat(cout);
    cout << endl;
    n2.Xuat(cout);
    cout << endl;
    n3.Xuat(cout);
    cout << endl;
    n4.Xuat(cout);
    cout << endl;
    n5.Xuat(cout);
    cout << endl;

    system("pause");
}