#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

class HinhHocPhang{
public:
};

class HinhChuNhat: public HinhHocPhang{
private:
    double chieuDai, chieuRong;
public:
    HinhChuNhat(){
        chieuDai = chieuRong = 0.0;
    }
    HinhChuNhat(double chieuDai, double chieuRong){
        this->chieuDai = chieuDai;
        this->chieuRong = chieuRong;
    }

    double tinhChuVi(){
        double res = 2 * (chieuDai + chieuRong);
        return res;
    }
    double tinhDienTich(){
        double res = chieuDai * chieuRong;
        return res;
    }

    friend istream& operator>>(istream& in, HinhChuNhat& hcn){
        in >> hcn.chieuDai >> hcn.chieuRong;
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhChuNhat& hcn){
        out << "hcn: " << hcn.chieuDai << " " << hcn.chieuRong << endl;
        return out;
    }
};

class HinhTron: public HinhHocPhang{
private:
    double banKinh;
public:
    HinhTron(){
        banKinh = 0.0;
    }
    HinhTron(double banKinh){
        this->banKinh = banKinh;
    }

    double tinhChuVi(){
        double res = 2 * 3.14 * banKinh;
        return res;
    }
    double tinhDienTich(){
        double res = 3.14 * banKinh * banKinh;
        return res;
    }

    friend istream& operator>>(istream& in, HinhTron& ht){
        in >> ht.banKinh;
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhTron& ht){
        out << "ht: " << ht.banKinh << endl;
        return out;
    }
};

class HinhTamGiac: public HinhHocPhang{
private:
    double canhA, canhB, canhC;
public:
    HinhTamGiac(){
        canhA = canhB = canhC = 0.0;
    }
    HinhTamGiac(double canhA, double canhB, double canhC){
        this->canhA = canhA;
        this->canhB = canhB;
        this->canhC = canhC;
    }

    double tinhChuVi(){
        double res = canhA + canhB + canhC;
        return res;
    }
    double tinhDienTich(){
        double nuaChuVi = (canhA + canhB + canhC) / 2;
        double res = sqrt(nuaChuVi * (nuaChuVi - canhA) * (nuaChuVi - canhB) * (nuaChuVi - canhC));
        return res;
    }

    friend istream& operator>>(istream& in, HinhTamGiac& htg){
        in >> htg.canhA >> htg.canhB >> htg.canhC;
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhTamGiac& htg){
        out << "htg: " << htg.canhA << " " << htg.canhB << " " << htg.canhC << endl;
        return out;
    }
};

class HinhThangVuong: public HinhHocPhang{
private:
    double dayLon, dayBe, chieuCao;
public:
    HinhThangVuong(){
        dayLon = dayBe = chieuCao = 0.0;
    }
    HinhThangVuong(double dayLon, double dayBe, double chieuCao){
        this->dayLon = dayLon;
        this->dayBe = dayBe;
        this->chieuCao = chieuCao;
    }

    double tinhChuVi(){
        double dgCheo = sqrt(chieuCao * chieuCao + (dayLon - dayBe) * (dayLon - dayBe));
        double res = dayLon + dayBe + chieuCao + dgCheo;
        return res;
    }
    double tinhDienTich(){
        double res = (dayLon + dayBe) * chieuCao / 2;
        return res;
    }

    friend istream& operator>>(istream& in, HinhThangVuong& htv){
        in >> htv.dayLon >> htv.dayBe >> htv.chieuCao;
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhThangVuong& htv){
        out << "htv: " << htv.dayLon << " " << htv.dayBe << " " << htv.chieuCao << endl;
        return out;
    }
};

class QuanLyHinhHocPhang{
private:
    vector<HinhChuNhat> dsHCN;
    vector<HinhTron> dsHT;
    vector<HinhTamGiac> dsHTG;
    vector<HinhThangVuong> dsHTV;

    double tongDienTich;
    double tongChuVi;
public:
    QuanLyHinhHocPhang(){
        tongChuVi = tongDienTich = 0.0;
    }

    void themHinh(istream& in){
        int choice;
        cout << "0 - hinh chu nhat, 1 - hinh tron, 2 - hinh tam giac, 3 - hinh thang vuong\n";
        cout << "Nhap loai hinh: "; cin >> choice;
        switch (choice){
            case 0:{
                HinhChuNhat hcn;
                in >> hcn;
                dsHCN.push_back(hcn);
                break;
            }
            case 1:{
                HinhTron ht;
                in >> ht;
                dsHT.push_back(ht);
                break;
            }
            case 2:{
                HinhTamGiac htg;
                in >> htg;
                dsHTG.push_back(htg);
                break;
            }
            case 3:{
                HinhThangVuong htv;
                in >> htv;
                dsHTV.push_back(htv);
                break;
            }
        }
        cout << endl;
    }

    friend istream& operator>>(istream& in, QuanLyHinhHocPhang& qlhhp){
        qlhhp.themHinh(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const QuanLyHinhHocPhang& qlhhp){
        for (int i = 0; i < qlhhp.dsHCN.size(); i++){
            out << qlhhp.dsHCN[i];
        }
        for (int i = 0; i < qlhhp.dsHT.size(); i++){
            out << qlhhp.dsHT[i];
        }
        for (int i = 0; i < qlhhp.dsHTG.size(); i++){
            out << qlhhp.dsHTG[i];
        }
        for (int i = 0; i < qlhhp.dsHTV.size(); i++){
            out << qlhhp.dsHTV[i];
        }
        return out;
    }

    void docFile(string filename){
        ifstream ifs(filename);
        string line;
        while (getline(ifs, line)){
            string loaiHinh = line.substr(0, line.find(":"));
            
            string soLieu = line.substr(line.find(":") + 2);
            replace(soLieu.begin(), soLieu.end(), ',', ' ');
            stringstream ss(soLieu);

            if (loaiHinh == "hcn"){
                double chieuDai, chieuRong;
                ss >> chieuDai >> chieuRong;
                HinhChuNhat hcn(chieuDai, chieuRong);
                dsHCN.push_back(hcn);
            }
            else if (loaiHinh == "htr"){
                double banKinh;
                ss >> banKinh;
                HinhTron ht(banKinh);
                dsHT.push_back(ht);
            }
            else if (loaiHinh == "htg"){
                double A, B, C;
                ss >> A >> B >> C;
                HinhTamGiac htg(A, B, C);
                dsHTG.push_back(htg);
            }
            else if (loaiHinh == "hthv"){
                double dayLon, dayBe, chieuCao;
                ss >> dayLon >> dayBe >> chieuCao;
                HinhThangVuong htv(dayLon, dayBe, chieuCao);
                dsHTV.push_back(htv);
            }
        }
        ifs.close();
    }

    void xuatThongTin(){
        for (int i = 0; i < dsHCN.size(); i++){
            tongChuVi += dsHCN[i].tinhChuVi();
            tongDienTich += dsHCN[i].tinhDienTich();
        }
        for (int i = 0; i < dsHT.size(); i++){
            tongChuVi += dsHT[i].tinhChuVi();
            tongDienTich += dsHT[i].tinhDienTich();
        }
        for (int i = 0; i < dsHTG.size(); i++){
            tongChuVi += dsHTG[i].tinhChuVi();
            tongDienTich += dsHTG[i].tinhDienTich();
        }
        for (int i = 0; i < dsHTV.size(); i++){
            tongChuVi += dsHTV[i].tinhChuVi();
            tongDienTich += dsHTV[i].tinhDienTich();
        }
        cout << "Tong chu vi: " << tongChuVi << endl
             << "Tong dien tich: " << tongDienTich << endl
             << "Thong ke so luong:\n";
        cout << "Hinh chu nhat: " << dsHCN.size() << endl
             << "Hinh tron: " << dsHT.size() << endl
             << "Hinh tam giac: " << dsHTG.size() << endl
             << "Hinh thang vuong: " << dsHTV.size() << endl;
    }
};

int main(){
    QuanLyHinhHocPhang qlhhp;
    qlhhp.docFile("hhp.txt");
    qlhhp.xuatThongTin();
}