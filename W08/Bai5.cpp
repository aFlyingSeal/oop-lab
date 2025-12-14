#include<iostream>
#include<iomanip>
#include<vector>
#include<math.h>

#define PI 3.14159
#define SQRT_OF_THREE 1.73205

using namespace std;

class Hinh{
public:
    virtual void In(ostream& out) const = 0;

    friend ostream& operator<<(ostream& out, const Hinh& hinh){
        hinh.In(out);
        return out;
    }

    virtual ~Hinh(){}
};

class HinhHocPhang: public Hinh{
public:
    virtual float tinhChuVi() const = 0;
    virtual float tinhDienTich() const = 0;

    virtual void In(ostream& out) const{
        out << fixed << setprecision(2)
            << "[P = " << tinhChuVi() << ", S = " << tinhDienTich() << "]";
    }
};

class HinhHocKhongGian: public Hinh{
public:
    virtual float tinhDTXungQuanh() const = 0;
    virtual float tinhTheTich() const = 0;

    virtual void In(ostream& out) const{
        out << fixed << setprecision(2)
            << "[Sxq = " << tinhDTXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

class HinhTron: public HinhHocPhang{
private:
    float banKinh;
public:
    HinhTron(float banKinh){
        this->banKinh = banKinh;
    }

    float tinhChuVi() const{
        return 2 * PI * banKinh;
    }
    float tinhDienTich() const{
        return PI * banKinh * banKinh;
    }

    void In(ostream& out) const{
        out << "Hinh Tron ";
        HinhHocPhang::In(out);
    }
};

class HinhTamGiacDeu: public HinhHocPhang{
private:
    float canh;
public:
    HinhTamGiacDeu(float canh){
        this->canh = canh;
    }

    float tinhChuVi() const{
        return 3 * canh;
    }
    float tinhDienTich() const{
        return canh * canh * SQRT_OF_THREE / 4;
    }

    void In(ostream& out) const{
        out << "Hinh Tam Giac Deu ";
        HinhHocPhang::In(out);
    }
};

class HinhChuNhat: public HinhHocPhang{
private:
    float chieuDai, chieuRong;
public:
    HinhChuNhat(float chieuDai, float chieuRong){
        this->chieuDai = chieuDai;
        this->chieuRong = chieuRong;
    }

    float tinhChuVi() const{
        return 2 * (chieuDai + chieuRong);
    }
    float tinhDienTich() const{
        return chieuDai * chieuRong;
    }

    void In(ostream& out) const{
        out << "Hinh Chu Nhat ";
        HinhHocPhang::In(out);
    }
};

class HinhVuong: public HinhHocPhang{
private:
    float canh;
public:
    HinhVuong(float canh){
        this->canh = canh;
    }

    float tinhChuVi() const{
        return 4 * canh;
    }
    float tinhDienTich() const{
        return canh * canh;
    }

    void In(ostream& out) const{
        out << "Hinh Vuong ";
        HinhHocPhang::In(out);
    }
};

class HinhCau: public HinhHocKhongGian{
private:
    float banKinh;
public:
    HinhCau(float banKinh){
        this->banKinh = banKinh;
    }

    float tinhDTXungQuanh() const{
        return 4 * PI * banKinh * banKinh;
    }
    float tinhTheTich() const{
        return 4 * PI * banKinh * banKinh * banKinh / 3;
    }

    void In(ostream& out) const{
        out << "Hinh Cau ";
        HinhHocKhongGian::In(out);
    }
};

class HinhLapPhuong: public HinhHocKhongGian{
private:
    float canh;
public:
    HinhLapPhuong(float canh){
        this->canh = canh;
    }

    float tinhDTXungQuanh() const{
        return 6 * canh * canh;
    }
    float tinhTheTich() const{
        return canh * canh * canh;
    }

    void In(ostream& out) const{
        out << "Hinh Lap Phuong ";
        HinhHocKhongGian::In(out);
    }
};

class HinhHop: public HinhHocKhongGian{
private:
    float chieuDai, chieuRong, chieuCao;
public:
    HinhHop(float chieuDai, float chieuRong, float chieuCao){
        this->chieuDai = chieuDai;
        this->chieuRong = chieuRong;
        this->chieuCao = chieuCao;
    }

    float tinhDTXungQuanh() const{
        return 2 * (chieuDai * chieuRong + chieuDai * chieuCao + chieuRong * chieuCao);
    }
    float tinhTheTich() const{
        return chieuDai * chieuRong * chieuCao;
    }

    void In(ostream& out) const{
        out << "Hinh Hop ";
        HinhHocKhongGian::In(out);
    }
};

class HinhTru: public HinhHocKhongGian{
private:
    float banKinhDay, chieuCao;
public:
    HinhTru(float banKinhDay, float chieuCao){
        this->banKinhDay = banKinhDay;
        this->chieuCao = chieuCao;
    }

    float tinhDTXungQuanh() const{
        return 2 * PI * banKinhDay * chieuCao;
    }
    float tinhTheTich() const{
        return PI * banKinhDay * banKinhDay * chieuCao;
    }

    void In(ostream& out) const{
        out << "Hinh Tru ";
        HinhHocKhongGian::In(out);
    }
};

class HinhNon: public HinhHocKhongGian{
private:
    float banKinhDay, duongSinh;
public:
    HinhNon(float duongSinh, float banKinhDay){
        this->banKinhDay = banKinhDay;
        this->duongSinh = duongSinh;
    }

    float tinhDTXungQuanh() const{
        return PI * banKinhDay * duongSinh;
    }
    float tinhTheTich() const{
        float chieuCao = sqrt(duongSinh * duongSinh - banKinhDay * banKinhDay);
        return PI * banKinhDay * banKinhDay * chieuCao;
    }

    void In(ostream& out) const{
        out << "Hinh Non ";
        HinhHocKhongGian::In(out);
    }
};

int main(){
    vector<Hinh*> dsHinh;
    dsHinh.push_back(new HinhTron(3.5));
    dsHinh.push_back(new HinhTamGiacDeu(8.5));
    dsHinh.push_back(new HinhChuNhat(3.7, 1.9));
    dsHinh.push_back(new HinhVuong(4.1));
    dsHinh.push_back(new HinhCau(13.5));
    dsHinh.push_back(new HinhLapPhuong(2.9));
    dsHinh.push_back(new HinhHop(1.2, 3.7, 6.3));
    dsHinh.push_back(new HinhTru(6.1, 4.9));
    dsHinh.push_back(new HinhNon(8.7, 3.2));

    for (int i = 0; i < dsHinh.size(); i++){
        cout << *dsHinh[i] << endl;
    }

    for (int i = 0; i < dsHinh.size(); i++){
        delete dsHinh[i];
    }

    cout << endl << endl;
    system("pause");
    return 0;
}