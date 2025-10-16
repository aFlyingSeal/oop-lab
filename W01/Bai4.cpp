#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

// class NgayThang
class NgayThang{
private:
    int ngay, thang, nam;
public:
    NgayThang();
    NgayThang(int ngay, int thang, int nam);
    NgayThang(const NgayThang& other);
    void Xuat();
    ~NgayThang();
};

NgayThang::NgayThang(){
    ngay = thang = nam = 1;
}

NgayThang::NgayThang(int ngay, int thang, int nam){
    this->ngay = abs(ngay);
    this->thang = abs(thang);
    this->nam = abs(nam);
}

NgayThang::NgayThang(const NgayThang& other){
    this->ngay = other.ngay;
    this->thang = other.thang;
    this->nam = other.nam;
}

void NgayThang::Xuat(){
    cout << "NgaySinh: ";
    cout << setw(2) << setfill('0') << ngay << "/"
         << setw(2) << setfill('0') << thang << "/"
         << setw(4) << setfill('0') << nam << endl;
}

NgayThang::~NgayThang() {}

// class SinhVien
class SinhVien{
private:
    string MSSV;
    string hoTen;
    double DLT, DTH;
    NgayThang ngaySinh;
public:
    SinhVien();
    SinhVien(const string& MSSV);
    SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH);
    SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH,
             int ngSinh, int tSinh, int nSinh);
    SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH, NgayThang ngaySinh);
    SinhVien(const SinhVien& other);
    void Xuat();
    ~SinhVien();
};

SinhVien::SinhVien(){
    MSSV = "xxxxxxx";
    hoTen = "xxxx";
    DLT = DTH = 10;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const string& MSSV){
    this->MSSV = MSSV;
    hoTen = "xxxx";
    DLT = DTH = 10;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH){
    this->MSSV = MSSV;
    this->hoTen = hoTen;
    this->DLT = DLT;
    this->DTH = DTH;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH,
                    int ngSinh, int tSinh, int nSinh){
    this->MSSV = MSSV;
    this->hoTen = hoTen;
    this->DLT = DLT;
    this->DTH = DTH;
    ngaySinh = NgayThang(ngSinh, tSinh, nSinh);
}

SinhVien::SinhVien(const string& MSSV, const string& hoTen, double DLT, double DTH, NgayThang ngaySinh){
    this->MSSV = MSSV;
    this->hoTen = hoTen;
    this->DLT = DLT;
    this->DTH = DTH;
    this->ngaySinh = ngaySinh;
}

SinhVien::SinhVien(const SinhVien& other){
    this->MSSV = other.MSSV;
    this->hoTen = other.hoTen;
    this->DLT = other.DLT;
    this->DTH = other.DTH;
    this->ngaySinh = other.ngaySinh;
}

void SinhVien::Xuat(){
    cout << "MSSV: " << MSSV << endl
         << "HoTen: " << hoTen << endl;
    ngaySinh.Xuat();
    cout << "DLT: " << DLT << endl
         << "DTH: " << DTH << endl;
}

SinhVien::~SinhVien() {}

int main(){
    SinhVien sv1;
    sv1.Xuat();
    SinhVien sv2("1363001");
    sv2.Xuat();
    SinhVien sv3("1363002", "Nguyen Van A", 7, 8.5);
    sv3.Xuat();
    SinhVien sv4("1363003", "Tran Thi B", 8, 9.5, 12, 3, 1996);
    sv4.Xuat();
    NgayThang n(30, 2, 1996);
    SinhVien sv5("1363004", "Ngo Van C", 5, 6, n);
    sv5.Xuat();
    SinhVien sv6(sv5);
    sv6.Xuat();
}