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
    NhanVien(string hoTen, string diaChi){
        this->hoTen = hoTen;
        this->diaChi = diaChi;
    }

    void capNhatThongTin(string hoTen, string diaChi){
        this->hoTen = hoTen;
        this->diaChi = diaChi;
    }

    string layHoTen() const{ return hoTen; }
    string layDiaChi() const{ return diaChi; }
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
    NhanVienThuKy(string hoTen, string diaChi, string chungChiNgoaiNgu, int slBaoCao): NhanVien(hoTen, diaChi){
        this->chungChiNgoaiNgu = chungChiNgoaiNgu;
        this->slBaoCao = slBaoCao;
    }

    friend istream& operator>>(istream& in, NhanVienThuKy& nvtk){
        string hoTen, diaChi;
        getline(in, hoTen);
        getline(in, diaChi);
        getline(in, nvtk.chungChiNgoaiNgu);
        in >> nvtk.slBaoCao;
        in.ignore(1);

        nvtk.capNhatThongTin(hoTen, diaChi);
        
        return in;
    }

    friend ostream& operator<<(ostream& out, const NhanVienThuKy& nvtk){
        out << nvtk.layHoTen() << " " << nvtk.layDiaChi() << " "
            << nvtk.chungChiNgoaiNgu << " " << nvtk.slBaoCao << endl;
        return out;
    }

    int laySLBaoCao(){ return slBaoCao; }
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
    NhanVienKyThuat(string hoTen, string diaChi, string chungChiNganh, int slSangKien): NhanVien(hoTen, diaChi){
        this->chungChiNganh = chungChiNganh;
        this->slSangKien = slSangKien;
    }

    friend istream& operator>>(istream& in, NhanVienKyThuat& nvkt){
        string hoTen, diaChi;
        getline(in, hoTen);
        getline(in, diaChi);
        getline(in, nvkt.chungChiNganh);
        in >> nvkt.slSangKien;
        in.ignore(1);

        nvkt.capNhatThongTin(hoTen, diaChi);
        
        return in;
    }

    friend ostream& operator<<(ostream& out, const NhanVienKyThuat& nvkt){
        out << nvkt.layHoTen() << " " << nvkt.layDiaChi() << " "
            << nvkt.chungChiNganh << " " << nvkt.slSangKien << endl;
        return out;
    }

    int laySLSangKien(){ return slSangKien; }
};

class CongTy{
private:
    vector<NhanVienThuKy> dsNVThuKy;
    vector<NhanVienKyThuat> dsNVKyThuat;

    string layChuoiCon(string line, char startChar, char endChar){
        int begin = line.find(startChar) + 1;
        int end = line.find(endChar) - 1;
        return line.substr(begin, end - begin + 1);
    }
public:
    void themNhanVien(){
        int choice;
        cout << "Nhap loai nhan vien (thu ky - 0, ky thuat - 1): "; cin >> choice;

        cin.ignore(1);

        switch (choice){
            case 0: {
                NhanVienThuKy nvtk;
                cin >> nvtk;
                dsNVThuKy.push_back(nvtk);
                break;
            }
            case 1: {
                NhanVienKyThuat nvkt;
                cin >> nvkt;
                dsNVKyThuat.push_back(nvkt);
                break;
            }
            default:
                cout << "Loai nhan vien khong ton tai!";
                break;
        }
        cout << endl;
    }

    void xuatNhanVien() const{
        cout << "Danh sach nhan vien\n";
        for (int i = 0; i < dsNVThuKy.size(); i++){
            cout << dsNVThuKy[i];
        }
        for (int i = 0; i < dsNVKyThuat.size(); i++){
            cout << dsNVKyThuat[i];
        }
    }

    void xuatNVXuatSac(){
        cout << "Danh sach nhan vien xuat sac\n";
        for (int i = 0; i < dsNVThuKy.size(); i++){
            if (dsNVThuKy[i].laySLBaoCao() >= 12){
                cout << dsNVThuKy[i];
            }
        }
        for (int i = 0; i < dsNVKyThuat.size(); i++){
            if (dsNVKyThuat[i].laySLSangKien() >= 6){
                cout << dsNVKyThuat[i];
            }
        }
    }

    friend istream& operator>>(istream& in, CongTy& cty){
        cty.themNhanVien();
        return in;
    }

    friend ostream& operator<<(ostream& out, const CongTy& cty){
        cty.xuatNhanVien();
        return out;
    }

    void docFile(string filename){
        ifstream ifs(filename);
        string line;
        while (getline(ifs, line)){
            string loaiNV = line.substr(0, 4);
            string hoTen = line.substr(6, line.find("(") - 7);
            string diaChi = layChuoiCon(line, '(', ')');
            string chungChi = layChuoiCon(line, '[', ']');
            int soLieu = stoi(layChuoiCon(line, '<', '>'));
            
            if (loaiNV == "nvkt"){
                NhanVienKyThuat nvkt(hoTen, diaChi, chungChi, soLieu);
                dsNVKyThuat.push_back(nvkt);
            }
            else if (loaiNV == "nvtk"){
                NhanVienThuKy nvtk(hoTen, diaChi, chungChi, soLieu);
                dsNVThuKy.push_back(nvtk);
            }
        }
        ifs.close();
    }

    void ghiFile(string filename){
        ofstream ofs(filename);

        for (int i = 0; i < dsNVKyThuat.size(); i++){
            ofs << dsNVKyThuat[i];
        }
        for (int i = 0; i < dsNVThuKy.size(); i++){
            ofs << dsNVThuKy[i];
        }

        ofs.close();
    }
};

int main(){
    CongTy cty;
    cty.docFile("input.txt");
    cty.ghiFile("output.txt");
    cty.xuatNVXuatSac();
}