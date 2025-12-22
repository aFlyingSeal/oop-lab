#include<iostream>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

class ChiTietMay{
private:
    string maSo;
public:
    ChiTietMay(const string& maSo){
        this->maSo = maSo;
    }
    
    virtual double LayTrongLuong() const = 0;
    virtual double LayGiaThanh() const = 0;

    virtual void In(ostream& out) const = 0;

    string LayMaSo() const{ return maSo; }

    virtual ~ChiTietMay(){}
};

class ChiTietDon: public ChiTietMay{
private:
    double trongLuong, giaThanh;
public:
    ChiTietDon(const string& maSo, double trongLuong, double giaThanh): ChiTietMay(maSo){
        this->trongLuong = trongLuong;
        this->giaThanh = giaThanh;
    }

    double LayTrongLuong() const{
        return trongLuong;
    }
    double LayGiaThanh() const{
        return giaThanh;
    }

    void In(ostream& out) const{
        out << fixed << setprecision(1)
            << "Chi tiet don: " << ChiTietMay::LayMaSo() << endl
            << "Trong luong: " << LayTrongLuong() << endl
            << "Gia thanh: " << LayGiaThanh() << endl;
        out << endl;
    }
};

class ChiTietPhuc: public ChiTietMay{
private:
    vector<ChiTietMay*> dsChiTiet;
public:
    ChiTietPhuc(const string& maSo): ChiTietMay(maSo){}

    void ThemChiTiet(ChiTietMay* ctm){
        dsChiTiet.push_back(ctm);
    }

    double LayTrongLuong() const{
        double trongLuong = 0.0;
        for (int i = 0; i < dsChiTiet.size(); i++){
            trongLuong += dsChiTiet[i]->LayTrongLuong();
        }
        return trongLuong * 1.1;
    }
    double LayGiaThanh() const{
        double giaThanh = 0.0;
        for (int i = 0; i < dsChiTiet.size(); i++){
            giaThanh += dsChiTiet[i]->LayGiaThanh();
        }
        return giaThanh * 1.2;
    }

    void In(ostream& out) const{
        out << fixed << setprecision(1)
            << "Chi tiet phuc: " << ChiTietMay::LayMaSo() << endl
            << "Trong luong: " << LayTrongLuong() << endl
            << "Gia thanh: " << LayGiaThanh() << endl
            << "Danh sach cac chi tiet con:\n";
        for (int i = 0; i < dsChiTiet.size(); i++){
            dsChiTiet[i]->In(out);
        }
    }

    ~ChiTietPhuc(){
        for (int i = 0; i < dsChiTiet.size(); i++){
            delete dsChiTiet[i];
        }
    }
};

class CoMay{
private:
    vector<ChiTietMay*> dsChiTiet;
public:
    CoMay(){}

    void ThemChiTietMay(ChiTietMay* ctm){
        dsChiTiet.push_back(ctm);
    }

    double TrongLuong() const{
        double trongLuong = 0.0;
        for (int i = 0; i < dsChiTiet.size(); i++){
            trongLuong += dsChiTiet[i]->LayTrongLuong();
        }
        return trongLuong;
    }
    double GiaThanh() const{
        double giaThanh = 0.0;
        for (int i = 0; i < dsChiTiet.size(); i++){
            giaThanh += dsChiTiet[i]->LayGiaThanh();
        }
        return giaThanh;
    }

    friend ostream& operator<<(ostream& out, const CoMay& cm){
        for (int i = 0; i < cm.dsChiTiet.size(); i++){
            cm.dsChiTiet[i]->In(out);
        }
        return out;
    }

    ~CoMay(){
        for (int i = 0; i < dsChiTiet.size(); i++){
            delete dsChiTiet[i];
        }
    }
};

int main(){
    CoMay* pcm = new CoMay();
    pcm->ThemChiTietMay(new ChiTietDon("CTD001", 120, 350000));

    ChiTietMay* pctm = new ChiTietPhuc("CTP001");
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD002", 50, 1280000));
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD003", 20, 10000));

    ChiTietMay* pctm1 = new ChiTietPhuc("CTP002");
    ((ChiTietPhuc*)pctm1)->ThemChiTiet(new ChiTietDon("CTD004", 80, 170000));

    ((ChiTietPhuc*)pctm)->ThemChiTiet(pctm1);

    pcm->ThemChiTietMay(pctm);
    pcm->ThemChiTietMay(new ChiTietDon("CTD005", 210, 2350000));
    pcm->ThemChiTietMay(new ChiTietDon("CTD006", 40, 50000));

    cout << "Thong tin co may: " << endl << *pcm << endl;

    cout << "Trong luong: " << pcm->TrongLuong() << endl;

    cout << "Gia thanh: " << pcm->GiaThanh() << endl;

    cout << endl << endl;
    system("pause");
    return 0;
}