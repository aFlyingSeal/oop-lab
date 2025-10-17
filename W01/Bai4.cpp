#include<iostream>
#include<iomanip>
#include<cstring>

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
    char* MSSV;
    char* hoTen;
    double DLT, DTH;
    NgayThang ngaySinh;
public:
    SinhVien();
    SinhVien(const char* _MSSV);
    SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH);
    SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH,
             int ngSinh, int tSinh, int nSinh);
    SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH, NgayThang ngaySinh);
    SinhVien(const SinhVien& other);
    void Xuat();
    ~SinhVien();
};

SinhVien::SinhVien(){
    MSSV = new char[strlen("xxxxxxx") + 1];
    strcpy(MSSV, "xxxxxxx");
    hoTen = new char[strlen("xxxx") + 1];
    strcpy(hoTen, "xxxx");
    DLT = DTH = 10;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const char* _MSSV){
    MSSV = new char[strlen(_MSSV) + 1];
    strcpy(MSSV, _MSSV);
    hoTen = new char[strlen("xxxx") + 1];
    strcpy(hoTen, "xxxx");
    DLT = DTH = 10;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH){
    MSSV = new char[strlen(_MSSV) + 1];
    hoTen = new char[strlen(_hoTen) + 1];
    strcpy(MSSV, _MSSV);
    strcpy(hoTen, _hoTen);
    this->DLT = DLT;
    this->DTH = DTH;
    ngaySinh = NgayThang();
}

SinhVien::SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH,
                    int ngSinh, int tSinh, int nSinh){
    MSSV = new char[strlen(_MSSV) + 1];
    hoTen = new char[strlen(_hoTen) + 1];
    strcpy(MSSV, _MSSV);
    strcpy(hoTen, _hoTen);
    this->DLT = DLT;
    this->DTH = DTH;
    ngaySinh = NgayThang(ngSinh, tSinh, nSinh);
}

SinhVien::SinhVien(const char* _MSSV, const char* _hoTen, double DLT, double DTH, NgayThang ngaySinh){
    MSSV = new char[strlen(_MSSV) + 1];
    hoTen = new char[strlen(_hoTen) + 1];
    strcpy(MSSV, _MSSV);
    strcpy(hoTen, _hoTen);
    this->DLT = DLT;
    this->DTH = DTH;
    this->ngaySinh = ngaySinh;
}

SinhVien::SinhVien(const SinhVien& other){
    MSSV = new char[strlen(other.MSSV) + 1];
    hoTen = new char[strlen(other.hoTen) + 1];
    strcpy(MSSV, other.MSSV);
    strcpy(hoTen, other.hoTen);
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

SinhVien::~SinhVien(){
    delete[] MSSV;
    MSSV = nullptr;
    delete[] hoTen;
    hoTen = nullptr;
}

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