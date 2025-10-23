#include<iostream>
#include<iomanip>
#include<cstring>
#include<math.h>

using namespace std;

class HocSinh{
private:
    char *ten;
    char *MSSV;
    double diem_1, diem_2, diem_3, diem_TB;

    static int nextMSSV;
    
    static const HocSinh* maxDTB;

    void capNhatMaxDTB(){
        if (maxDTB == nullptr || diem_TB > maxDTB->layDTB()){
            maxDTB = this;
        }
    }
public:
    HocSinh();
    HocSinh(const char* _ten, double diem_1, double diem_2, double diem_3);

    double layDTB() const;

    void DatHoTen(const char* _ten);
    void GanDiem(double diem_1, double diem_2, double diem_3);

    static const HocSinh& HSDiemTBCaoNhat();
    void In(ostream& os) const;
    ~HocSinh();
};

HocSinh::HocSinh(){
    ten = new char[strlen("xxxxxxx") + 1];
    strcpy(ten, "xxxxxxx");
    MSSV = new char[9];
    sprintf(MSSV, "%d", nextMSSV);
    diem_1 = diem_2 = diem_3 = diem_TB = 0.0;
    capNhatMaxDTB();
    nextMSSV++;
}

HocSinh::HocSinh(const char* _ten, double diem_1, double diem_2, double diem_3){
    ten = new char[strlen(_ten) + 1];
    strcpy(ten, _ten);
    MSSV = new char[9];
    sprintf(MSSV, "%d", nextMSSV);
    this->diem_1 = fabs(diem_1);
    this->diem_2 = fabs(diem_2);
    this->diem_3 = fabs(diem_3);
    diem_TB = layDTB();
    capNhatMaxDTB();
    nextMSSV++;
}

double HocSinh::layDTB() const{
    return (diem_1 + diem_2 + diem_3) / 3;
}

void HocSinh::DatHoTen(const char* _ten){
    delete[] ten;
    ten = new char[strlen(_ten) + 1];
    strcpy(ten, _ten);
}

void HocSinh::GanDiem(double diem_1, double diem_2, double diem_3){
    this->diem_1 = fabs(diem_1);
    this->diem_2 = fabs(diem_2);
    this->diem_3 = fabs(diem_3);
    diem_TB = layDTB();
    capNhatMaxDTB();
}

const HocSinh& HocSinh::HSDiemTBCaoNhat(){
   return *maxDTB;
}

void HocSinh::In(ostream& os) const{
    os << "HS: " << ten << ", "
       << "MS: " << MSSV << ", "
       << "DTB: " << fixed << setprecision(2) << diem_TB;
}

HocSinh::~HocSinh(){
    delete[] ten;
    ten = nullptr;
    delete[] MSSV;
    MSSV = nullptr;
    diem_1 = diem_2 = diem_3 = 0.0;
}

int HocSinh::nextMSSV = 23120001;
const HocSinh* HocSinh::maxDTB = nullptr;

int main(){
    HocSinh hs1;
    hs1.DatHoTen("Nguyen Van A");
    hs1.GanDiem(7, 8, 10);
    HocSinh hs2("Tran Thi B", 5, 8, 4.5);
    HocSinh hs3("Hoang Thi C", -9.5, 8.5, 4.5);
    HocSinh hs4("Le Van D", 7.5, 9, -10);
    hs1.In(cout);
    cout << endl;
    hs2.In(cout);
    cout << endl;
    hs3.In(cout);
    cout << endl;
    hs4.In(cout);
    cout << endl;
    cout << "Hoc sinh co diem TB cao nhat:" << endl;
    HocSinh::HSDiemTBCaoNhat().In(cout);
    cout << endl;
    system("pause");
    return 0;
}