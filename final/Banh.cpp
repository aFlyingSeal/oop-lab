#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class MyException: public runtime_error{
private:
    string errorDescription;
    int errorCode;

    static const string BuildErrorMessage(int errCode, const string& errDesc){
        string message = "";
        message = message + " error code: " + to_string(errCode);
        message = message + ", error description: " + errDesc;
        return message; 
    }
public:
    MyException(int errCode, const string& errDesc): runtime_error(BuildErrorMessage(errCode, errDesc)){
        errorDescription = errDesc;
        errorCode = errCode;
    }
};

class NullReferenceException: public MyException{
public:
    NullReferenceException(int errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class IndexOutOfRangeException: public MyException{
public:
    IndexOutOfRangeException(int errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class FileNotFoundException: public MyException{
public:
    FileNotFoundException(int errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class InvalidDataException: public MyException{
public:
    InvalidDataException(int errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class NguyenLieu{
protected:
    string tenNguyenLieu;
public:
    NguyenLieu(const string& tenNguyenLieu){
        if (tenNguyenLieu == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->tenNguyenLieu = tenNguyenLieu;
    }
    virtual ~NguyenLieu(){};

    virtual float tinhKhoiLuong() = 0;
    virtual float tinhHamLuongBeo() = 0;
    virtual float tinhLuongDuong() = 0;

    virtual int demNguyenLieuDon() = 0;

    virtual void inThongTin(ostream& out, int depth) = 0 ;

    friend ostream& operator<<(ostream& out, NguyenLieu& nl){
        nl.inThongTin(out, 0);
        return out;
    }

    string layTenNguyenLieu(){ return tenNguyenLieu; }
};

class NguyenLieuDon: public NguyenLieu{
private:
    float khoiLuong, hamLuongBeo, luongDuong;
public:
    NguyenLieuDon(const string& tenNguyenLieu, float khoiLuong, float hamLuongBeo, float luongDuong): NguyenLieu(tenNguyenLieu){
        if (khoiLuong <= 0 || hamLuongBeo <= 0 || luongDuong <= 0){
            throw InvalidDataException(4, "Argument must be a positive number");
        }
        this->khoiLuong = khoiLuong;
        this->hamLuongBeo = hamLuongBeo;
        this->luongDuong = luongDuong;
    }

    float tinhKhoiLuong(){
        return khoiLuong;
    }
    float tinhHamLuongBeo(){
        return hamLuongBeo;
    }
    float tinhLuongDuong(){
        return luongDuong;
    }

    int demNguyenLieuDon(){
        return 1;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[NLDon] " << tenNguyenLieu << endl;
        out << indent << "KhoiLuong: " << khoiLuong << endl;
        out << indent << "HamLuongBeo: " << hamLuongBeo << ", LuongDuong: " << luongDuong << endl;
    }
};

class NguyenLieuHonHop: public NguyenLieu{
protected:
    vector<NguyenLieu*> dsNguyenLieu;
public:
    NguyenLieuHonHop(const string& tenNguyenLieu): NguyenLieu(tenNguyenLieu){}
    ~NguyenLieuHonHop(){
        for (NguyenLieu* nl: dsNguyenLieu){
            delete nl;
        }
    }

    int demNguyenLieuDon(){
        int count = 0;
        for (NguyenLieu* nl: dsNguyenLieu){
            count += nl->demNguyenLieuDon();
        }
        return count;
    }

    void themNguyenLieu(NguyenLieu* nl){
        if (nl == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsNguyenLieu.push_back(nl);
    }

    vector<NguyenLieu*> layDSNguyenLieu() const{
        return dsNguyenLieu;
    }
};

class NguyenLieuHonHopDac: public NguyenLieuHonHop{
public:
    NguyenLieuHonHopDac(const string& tenNguyenLieu): NguyenLieuHonHop(tenNguyenLieu){}

    float tinhKhoiLuong(){
        float tongKhoiLuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongKhoiLuong += nl->tinhKhoiLuong();
        }
        return tongKhoiLuong;
    }
    float tinhHamLuongBeo(){
        float tongHamLuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongHamLuong += nl->tinhHamLuongBeo();
        }
        return tongHamLuong * 0.4;
    }
    float tinhLuongDuong(){
        float tongLuongDuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongLuongDuong += nl->tinhLuongDuong();
        }
        return tongLuongDuong * 0.4;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[NLHHDac] " << tenNguyenLieu << endl;
        out << indent << "KhoiLuong: " << tinhKhoiLuong() << endl;
        out << indent << "HamLuongBeo: " << tinhHamLuongBeo() << ", LuongDuong: " << tinhLuongDuong() << endl;
        for (NguyenLieu* nl: dsNguyenLieu){
            nl->inThongTin(out, depth + 1);
        }
    }
};

class NguyenLieuHonHopLong: public NguyenLieuHonHop{
public:
    NguyenLieuHonHopLong(const string& tenNguyenLieu): NguyenLieuHonHop(tenNguyenLieu){}

    float tinhKhoiLuong(){
        float tongKhoiLuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongKhoiLuong += nl->tinhKhoiLuong();
        }
        return tongKhoiLuong * 0.25;
    }
    float tinhHamLuongBeo(){
        float tongHamLuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongHamLuong += nl->tinhHamLuongBeo();
        }
        return tongHamLuong;
    }
    float tinhLuongDuong(){
        float tongLuongDuong = 0.0;
        for (NguyenLieu* nl: dsNguyenLieu){
            tongLuongDuong += nl->tinhLuongDuong();
        }
        return tongLuongDuong;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[NLHHLong] " << tenNguyenLieu << endl;
        out << indent << "KhoiLuong: " << tinhKhoiLuong() << endl;
        out << indent << "HamLuongBeo: " << tinhHamLuongBeo() << ", LuongDuong: " << tinhLuongDuong() << endl;
        for (NguyenLieu* nl: dsNguyenLieu){
            nl->inThongTin(out, depth + 1);
        }
    }
};

class Banh{
private:
    string tenBanh;
    vector<NguyenLieu*> dsNguyenLieu;

    static const string parseTenNguyenLieu(const string& s){
        int left = s.find("(");
        int right = s.find(")");
        if (left == string::npos || right == string::npos || left >= right){
            throw IndexOutOfRangeException(2, "Invalid input file format");
        } 
        return s.substr(left + 1, right - left - 1);
    }
public:
    Banh(const string& tenBanh){
        if (tenBanh == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->tenBanh = tenBanh;
    }
    ~Banh(){
        for (NguyenLieu* nl: dsNguyenLieu){
            delete nl;
        }
    }

    void themNguyenLieu(NguyenLieu* nl){
        if (nl == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsNguyenLieu.push_back(nl);
    }

    friend ostream& operator<<(ostream& out, const Banh& banh){
        out << banh.tenBanh << endl;
        for (NguyenLieu* nl: banh.dsNguyenLieu){
            nl->inThongTin(out, 1);
        }
        return out;
    }

    static NguyenLieu* taoNguyenLieu(ifstream& ifs, const string& ten, const string& line, bool& laNLHH){
        float kl, hlb, ld;
        ifs >> kl >> hlb >> ld;
        ifs.ignore(1);

        laNLHH = false;
        if (line.find("NguyenLieuDon") != string::npos){
            return new NguyenLieuDon(ten, kl, hlb, ld);
        }
        laNLHH = true;
        if (line.find("NguyenLieuHonHopDac") != string::npos)
            return new NguyenLieuHonHopDac(ten);
        if (line.find("NguyenLieuHonHopLong") != string::npos)
            return new NguyenLieuHonHopLong(ten);
        
        return nullptr;
    }

    static Banh* docFile(const string& filename){
        ifstream ifs(filename);
        if (!ifs){
            throw FileNotFoundException(3, filename + " was not found");
        }

        string line;
        getline(ifs, line);

        string tenBanh = line.substr(5);
        Banh* banh = new Banh(tenBanh);
        vector<NguyenLieuHonHop*> st;

        while (getline(ifs, line)){
            if (!st.empty() && line == st.back()->layTenNguyenLieu()){
                st.pop_back();
                continue;
            }
            if (line.find("(") != string::npos){
                string tenNguyenLieu = parseTenNguyenLieu(line);
                bool laNLHH = false;
                NguyenLieu* nl = taoNguyenLieu(ifs, tenNguyenLieu, line, laNLHH);
                if (nl == nullptr){
                    throw NullReferenceException(1, "Invalid input file format");
                }

                if (!st.empty())
                    st.back()->themNguyenLieu(nl);
                else
                    banh->themNguyenLieu(nl);

                if (laNLHH)
                    st.push_back(static_cast<NguyenLieuHonHop*>(nl));
            }
        }
        return banh;
    }

    void timMaxNLDon(NguyenLieu* nl, NguyenLieuHonHop*& nlhhMax, int& slNLDMax){
        NguyenLieuHonHop* p = dynamic_cast<NguyenLieuHonHop*>(nl);
        if (p){
            if (p->demNguyenLieuDon() > slNLDMax){
                slNLDMax = p->demNguyenLieuDon();
                nlhhMax = p;
            }
            for (NguyenLieu* q: p->layDSNguyenLieu()){
                timMaxNLDon(q, nlhhMax, slNLDMax);
            }
        }
    }

    vector<NguyenLieu*> layDSNguyenLieu() const{ return dsNguyenLieu; }
};

int main(){
    try{
        Banh* banh = Banh::docFile("data/data2.txt");
        cout << *banh;

        NguyenLieuHonHop* nlhhMax = nullptr;
        int slNLDMax = -1;
        for (NguyenLieu* nl: banh->layDSNguyenLieu()){
            banh->timMaxNLDon(nl, nlhhMax, slNLDMax);
        }

        cout << endl;

        if (nlhhMax){
            cout << "NguyenLieuHonHop voi max NguyenLieuDon\n";
            cout << *nlhhMax;
            cout << "So luong NguyenLieuDon: " << slNLDMax << endl;
        }   
        else{
            cout << "Khong tim thay NguyenLieuHonHop thoa man\n";
        }

        delete banh;
    }
    catch (const MyException& e){
        cout << "Custom error: " << e.what() << endl;
    }
}