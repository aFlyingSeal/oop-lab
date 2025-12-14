#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class NhanVien{
private:
    string hoTen, diaChi;
public:
    NhanVien(){
        hoTen = diaChi = "";
    }
    NhanVien(const string& hoTen, const string& diaChi){
        this->hoTen = hoTen;
        this->diaChi = diaChi;
    }
    ~NhanVien(){}

    virtual void Doc(istream& in){
        in >> hoTen >> diaChi;
    }
    virtual void In(ostream& out) const{
        out << hoTen << " [" << diaChi << "]";

    }

    friend istream& operator>>(istream& in, NhanVien& nv){
        nv.Doc(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const NhanVien& nv){
        nv.In(out);
        return out;
    }

    virtual string layLoaiNV(){ return ""; }
    virtual int laySoLieu(){ return 0; }
};

class NhanVienThuKy: public NhanVien{
private:
    string chungChiNgoaiNgu;
    int slBaoCao;
public:
    NhanVienThuKy(): NhanVien(){
        chungChiNgoaiNgu = "";
        slBaoCao = 0;
    }
    NhanVienThuKy(const string& hoTen, const string& diaChi, const string& chungChiNgoaiNgu, int slBaoCao):
    NhanVien(hoTen, diaChi){
        this->chungChiNgoaiNgu = chungChiNgoaiNgu;
        this->slBaoCao = slBaoCao;
    }
    ~NhanVienThuKy(){}

    void Doc(istream& in){
        NhanVien::Doc(in);
        in >> chungChiNgoaiNgu >> slBaoCao;
    }
    void In(ostream& out) const{
        NhanVien::In(out);
        out << " [" << chungChiNgoaiNgu << "] <" << slBaoCao << ">"; 
    }

    string layLoaiNV(){ return "nvtk"; }
    int laySoLieu(){ return slBaoCao; }
};

class NhanVienKyThuat: public NhanVien{
private:
    string chungChiNganh;
    int slSangKien;
public:
    NhanVienKyThuat(): NhanVien(){
        chungChiNganh = "";
        slSangKien = 0;
    }
    NhanVienKyThuat(const string& hoTen, const string& diaChi, const string& chungChiNganh, int slSangKien):
    NhanVien(hoTen, diaChi){
        this->chungChiNganh = chungChiNganh;
        this->slSangKien = slSangKien;
    }
    ~NhanVienKyThuat(){}

    void Doc(istream& in){
        NhanVien::Doc(in);
        in >> chungChiNganh >> slSangKien;
    }
    void In(ostream& out) const{
        NhanVien::In(out);
        out << " [" << chungChiNganh << "] <" << slSangKien << ">";
    }

    string layLoaiNV(){ return "nvkt"; }
    int laySoLieu(){ return slSangKien; }
};

class CongTy{
private:
    vector<NhanVien*> dsNhanVien;

    string layChuoiCon(string line, char startChar, char endChar){
        int begin = line.find(startChar) + 1;
        int end = line.find(endChar) - 1;
        return line.substr(begin, end - begin + 1);
    }
public:
    friend istream& operator>>(istream& in, CongTy& cty){
        NhanVien* nv = nullptr;
        string loai;
        in >> loai;
        if (loai == "nvtk"){
            nv = new NhanVienThuKy();
        }
        else{
            nv = new NhanVienKyThuat();
        }
        in >> *nv;
        cty.dsNhanVien.push_back(nv);
    }
    friend ostream& operator<<(ostream& out, const CongTy& cty){
        for (int i = 0; i < cty.dsNhanVien.size(); i++){
            out << *cty.dsNhanVien[i] << endl;
        }
    }

    void docFile(const string& filename){
        ifstream ifs(filename);
        string line;
        while (getline(ifs, line)){
            NhanVien* nv = nullptr;
            string loaiNV = line.substr(0, 4);
            string hoTen = line.substr(6, line.find("(") - 7);
            string diaChi = layChuoiCon(line, '(', ')');
            string chungChi = layChuoiCon(line, '[', ']');
            int soLieu = stoi(layChuoiCon(line, '<', '>'));

            if (loaiNV == "nvkt"){
                nv = new NhanVienKyThuat(hoTen, diaChi, chungChi, soLieu);
            }
            else{
                nv = new NhanVienThuKy(hoTen, diaChi, chungChi, soLieu);
            }
            dsNhanVien.push_back(nv);
        }
        ifs.close();
    }
    void ghiFile(const string& filename){
        ofstream ofs(filename);
        for (int i = 0; i < dsNhanVien.size(); i++){
            ofs << *dsNhanVien[i] << endl;
        }
        ofs.close();
    }

    void xuatNVXuatSac(){
        cout << "DS nhan vien xuat sac\n";
        for (int i = 0; i < dsNhanVien.size(); i++){
            if (dsNhanVien[i]->layLoaiNV() == "nvtk" && dsNhanVien[i]->laySoLieu() >= 12){
                cout << *dsNhanVien[i] << endl;
            }
            if (dsNhanVien[i]->layLoaiNV() == "nvkt" && dsNhanVien[i]->laySoLieu() >= 6){
                cout << *dsNhanVien[i] << endl;
            }
        }
    }

    ~CongTy(){
        for (int i = 0; i < dsNhanVien.size(); i++){
            delete dsNhanVien[i];
        }
    }
};

int main(){
    CongTy cty;
    cty.docFile("input.txt");
    cty.ghiFile("output.txt");
    cty.xuatNVXuatSac();
}