#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>
#include<sstream>

using namespace std;

class HinhHocPhang{
public:
    HinhHocPhang(){}
    virtual ~HinhHocPhang(){}

    virtual void Doc(istream& in) = 0;
    virtual void In(ostream& out) const = 0;

    friend istream& operator>>(istream& in, HinhHocPhang& hhp){
        hhp.Doc(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhHocPhang& hhp){
        hhp.In(out);
        return out;
    }

    virtual float tinhChuVi() = 0;
    virtual float tinhDienTich() = 0;
};

class HinhChuNhat: public HinhHocPhang{
private:
    float chieuDai, chieuRong;
public:
    HinhChuNhat(){
        chieuDai = chieuRong = 0.0;
    }
    HinhChuNhat(float chieuDai, float chieuRong){
        this->chieuDai = chieuDai;
        this->chieuRong = chieuRong;
    }

    void Doc(istream& in){
        in >> chieuDai >> chieuRong;
    }
    void In(ostream& out) const{
        out << "hcn: " << chieuDai << " " << chieuRong;
    }

    float tinhChuVi(){
        return 2 * (chieuDai + chieuRong);
    }
    float tinhDienTich(){
        return chieuDai * chieuRong;
    }
};

#define PI 3.14159
class HinhTron: public HinhHocPhang{
private:
    float banKinh;
public:
    HinhTron(){
        banKinh = 0.0;
    }
    HinhTron(float banKinh){
        this->banKinh = banKinh;
    }

    void Doc(istream& in){
        in >> banKinh;
    }
    void In(ostream& out) const{
        out << "htr: " << banKinh;
    }

    float tinhChuVi(){
        return 2 * PI * banKinh;
    }
    float tinhDienTich(){
        return PI * banKinh * banKinh;
    }
};

class HinhTamGiac: public HinhHocPhang{
private:
    float canhA, canhB, canhC;
public:
    HinhTamGiac(){
        canhA = canhB = canhC = 0.0;
    }
    HinhTamGiac(float canhA, float canhB, float canhC){
        this->canhA = canhA;
        this->canhB = canhB;
        this->canhC = canhC;
    }

    void Doc(istream& in){
        in >> canhA >> canhB >> canhC;
    }
    void In(ostream& out) const{
        out << "htg: " << canhA << " " << canhB << " " << canhC;
    }

    float tinhChuVi(){
        return canhA + canhB + canhC;
    }
    float tinhDienTich(){
        float nuaChuVi = (canhA + canhB + canhC) / 2;
        return sqrt(nuaChuVi * (nuaChuVi - canhA) * (nuaChuVi - canhB) * (nuaChuVi - canhC));
    }
};

class HinhThangVuong: public HinhHocPhang{
private:
    float chieuCao, dayLon, dayBe;
public:
    HinhThangVuong(){
        chieuCao = dayLon = dayBe = 0.0;
    }
    HinhThangVuong(float chieuCao, float dayLon, float dayBe){
        this->chieuCao = chieuCao;
        this->dayLon = dayLon;
        this->dayBe = dayBe;
    }

    void Doc(istream& in){
        in >> chieuCao >> dayLon >> dayBe;
    }
    void In(ostream& out) const{
        out << "htv: " << chieuCao << " " << dayLon << " " << dayBe;
    }

    float tinhChuVi(){
        float dgCheo = sqrt(chieuCao * chieuCao + (dayLon - dayBe) * (dayLon - dayBe));
        return dgCheo + chieuCao + dayLon + dayBe;
    }
    float tinhDienTich(){
        return (dayLon + dayBe) * chieuCao / 2;
    }
};

class QuanLyHinhHocPhang{
private:
    vector<HinhHocPhang*> dsHinh;

    int slHinhChuNhat = 0;
    int slHinhTron = 0;
    int slHinhTamGiac = 0;
    int slHinhThangVuong = 0;

    float tongChuVi = 0;
    float tongDienTich = 0;

    void khoiTao(HinhHocPhang* &hhp, const string& loai){
        if (loai == "hcn"){
            hhp = new HinhChuNhat();
            slHinhChuNhat++;
        }
        else if (loai == "htr"){
            hhp = new HinhTron();
            slHinhTron++;
        }
        else if (loai == "htg"){
            hhp = new HinhTamGiac();
            slHinhTamGiac++;
        }
        else{
            hhp = new HinhThangVuong();
            slHinhThangVuong++;
        }
    }
public:
    friend istream& operator>>(istream& in, QuanLyHinhHocPhang& qlhhp){
        string loai;
        in >> loai;

        HinhHocPhang* hhp = nullptr;
        qlhhp.khoiTao(hhp, loai);
        in >> *hhp;

        qlhhp.tongChuVi += hhp->tinhChuVi();
        qlhhp.tongDienTich += hhp->tinhDienTich();
        
        qlhhp.dsHinh.push_back(hhp);
        return in;
    }
    friend ostream& operator<<(ostream& out, const QuanLyHinhHocPhang& qlhhp){
        for (int i = 0; i < qlhhp.dsHinh.size(); i++){
            out << *qlhhp.dsHinh[i] << endl;
        }
        return out;
    }

    void docFile(const string& filename){
        ifstream ifs(filename);
        string line;
        while (getline(ifs, line)){
            string loaiHinh = line.substr(0, line.find(":"));

            string soLieu = line.substr(line.find(":") + 2);
            replace(soLieu.begin(), soLieu.end(), ',', ' ');
            stringstream ss(soLieu);

            HinhHocPhang* hhp = nullptr;
            khoiTao(hhp, loaiHinh);
            ss >> *hhp;

            tongChuVi += hhp->tinhChuVi();
            tongDienTich += hhp->tinhDienTich();

            dsHinh.push_back(hhp);
        }
        ifs.close();
    }
    void ghiFile(const string& filename){
        ofstream ofs(filename);
        for (int i = 0; i < dsHinh.size(); i++){
            ofs << *dsHinh[i] << endl;
        }
        ofs.close();
    }

    void thongKe(){
        cout << "Tong chu vi: " << tongChuVi << endl
             << "Tong dien tich: " << tongDienTich << endl
             << "Thong ke so luong:\n";
        cout << "Hinh chu nhat: " << slHinhChuNhat << endl
             << "Hinh tron: " << slHinhTron << endl
             << "Hinh tam giac: " << slHinhTamGiac << endl
             << "Hinh thang vuong: " << slHinhThangVuong << endl;
    }

    ~QuanLyHinhHocPhang(){
        for (int i = 0; i < dsHinh.size(); i++){
            delete dsHinh[i];
        }
    }
};

int main(){
    QuanLyHinhHocPhang qlhhp;
    qlhhp.docFile("hhp.txt");
    qlhhp.ghiFile("output.txt");
    qlhhp.thongKe();
}