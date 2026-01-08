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
        message = message + "error code: " + to_string(errCode);
        message = message + ", error description: " + errDesc;
        return message;
    }
public:
    MyException(float errCode, const string& errDesc): runtime_error(BuildErrorMessage(errCode, errDesc)){
        errorDescription = errDesc;
        errorCode = errCode;
    }
};

class NullReferenceException: public MyException{
public:
    NullReferenceException(float errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class IndexOutOfRangeException: public MyException{
public:
    IndexOutOfRangeException(float errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class FileNotFoundException: public MyException{
public:
    FileNotFoundException(float errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class InvalidDataException: public MyException{
public:
    InvalidDataException(float errCode, const string& errDesc): MyException(errCode, errDesc){}
};

class TaiNguyen{
protected:
    string maSo;
public:
    TaiNguyen(const string& maSo){
        if (maSo == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->maSo = maSo;
    }
    virtual ~TaiNguyen(){}

    virtual float tinhDungLuong() = 0;
    virtual float tinhSoLanTruyCap() = 0;
    virtual float tinhChiPhiLuuTru() = 0;

    virtual int demTapTin() = 0;

    virtual void inThongTin(ostream& out, float depth) = 0;

    string layMaSo(){ return maSo; }
};

class TapTin: public TaiNguyen{
private:
    float dungLuong, soLanTruyCap, chiPhiLuuTru;
public:
    TapTin(const string& maSo, float dungLuong, float soLanTruyCap, float chiPhiLuuTru): TaiNguyen(maSo){
        if (dungLuong <= 0 || soLanTruyCap <= 0 || chiPhiLuuTru <= 0){
            throw InvalidDataException(4, "Argument must not be negative");
        }
        this->dungLuong = dungLuong;
        this->soLanTruyCap = soLanTruyCap;
        this->chiPhiLuuTru = chiPhiLuuTru;
    }

    float tinhDungLuong(){
        return dungLuong;
    }
    float tinhSoLanTruyCap(){
        return soLanTruyCap;
    }
    float tinhChiPhiLuuTru(){
        return chiPhiLuuTru;
    }

    int demTapTin(){
        return 1;
    }

    void inThongTin(ostream& out, float depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[TapTin] " << maSo << endl;
        out << indent << "DungLuong: " << dungLuong << endl;
        out << indent << "SLTruyCap: " << soLanTruyCap << ", ChiPhi: " << chiPhiLuuTru << endl;
    }
};

class ThuMuc: public TaiNguyen{
protected:
    vector<TaiNguyen*> dsTaiNguyen;
public:
    ThuMuc(const string& maSo): TaiNguyen(maSo){}
    ~ThuMuc(){
        for (TaiNguyen* tn: dsTaiNguyen){
            delete tn;
        }
    }

    int demTapTin(){
        int count = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            count += tn->demTapTin();
        }
        return count;
    }

    void themTapTin(TaiNguyen* tn){
        if (tn == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsTaiNguyen.push_back(tn);
    }

    vector<TaiNguyen*> layDSTaiNguyen(){ return dsTaiNguyen; }
};

class ThuMucThuong: public ThuMuc{
public:
    ThuMucThuong(const string& maSo): ThuMuc(maSo){}

    float tinhDungLuong(){
        float tongDungLuong = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            tongDungLuong += tn->tinhDungLuong();
        }
        return tongDungLuong;
    }
    float tinhSoLanTruyCap(){
        float soLanTruyCap = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            soLanTruyCap += tn->tinhSoLanTruyCap();
        }
        return soLanTruyCap;
    }
    float tinhChiPhiLuuTru(){
        float tongChiPhi = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            tongChiPhi += tn->tinhChiPhiLuuTru();
        }
        return tongChiPhi;
    }

    void inThongTin(ostream& out, float depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[ThuMucThuong] " << maSo << endl;
        out << indent << "DungLuong: " << tinhDungLuong() << endl;
        out << indent << "SLTruyCap: " << tinhSoLanTruyCap() << ", ChiPhi: " << tinhChiPhiLuuTru() << endl;
        for (TaiNguyen* tn: dsTaiNguyen){
            tn->inThongTin(out, depth + 1);
        } 
    }
};

class ThuMucBackUp: public ThuMuc{
public:
    ThuMucBackUp(const string& maSo): ThuMuc(maSo){}

    float tinhDungLuong(){
        float tongDungLuong = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            tongDungLuong += tn->tinhDungLuong();
        }
        return 1.1 * tongDungLuong;
    }
    float tinhSoLanTruyCap(){
        float soLanTruyCap = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            soLanTruyCap += tn->tinhSoLanTruyCap();
        }
        return soLanTruyCap;
    }
    float tinhChiPhiLuuTru(){
        float tongChiPhi = 0;
        for (TaiNguyen* tn: dsTaiNguyen){
            tongChiPhi += tn->tinhChiPhiLuuTru();
        }
        return 1.2 * tongChiPhi;
    }

    void inThongTin(ostream& out, float depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[ThuMucBackUp] " << maSo << endl;
        out << indent << "DungLuong: " << tinhDungLuong() << endl;
        out << indent << "SLTruyCap: " << tinhSoLanTruyCap() << ", ChiPhi: " << tinhChiPhiLuuTru() << endl;
        for (TaiNguyen* tn: dsTaiNguyen){
            tn->inThongTin(out, depth + 1);
        }
    }
};

class HeThong{
private:
    string tenHeThong;
    vector<TaiNguyen*> dsTaiNguyen;

    static string parseTenTaiNguyen(const string& s){
        int left = s.find("(");
        int right = s.find(")");
        if (left == string::npos || right == string::npos || left >= right){
            throw IndexOutOfRangeException(2, "Invalid file format");
        }
        return s.substr(left + 1, right - left - 1);
    }
public:
    HeThong(const string& tenHeThong){
        if (tenHeThong == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->tenHeThong = tenHeThong;
    }
    ~HeThong(){
        for (TaiNguyen* tn: dsTaiNguyen){
            delete tn;
        }
    }

    vector<TaiNguyen*> layDSTaiNguyen(){ return dsTaiNguyen; }

    void themTaiNguyen(TaiNguyen* tn){
        if (tn == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsTaiNguyen.push_back(tn);
    }

    friend ostream& operator<<(ostream& out, const HeThong& ht){
        out << ht.tenHeThong << endl;
        for (TaiNguyen* tn: ht.dsTaiNguyen){
            tn->inThongTin(out, 1);
        }
        return out;
    }

    static TaiNguyen* taoTaiNguyen(ifstream& ifs, const string& line, const string& tenTaiNguyen, bool& laThuMuc){
        float dl, sltc, cptc;
        ifs >> dl >> sltc >> cptc;
        ifs.ignore(1, '\n');

        laThuMuc = false;
        if (line.find("TapTin") != string::npos){
            return new TapTin(tenTaiNguyen, dl, sltc, cptc);
        }
        laThuMuc = true;
        if (line.find("ThuMucThuong") != string::npos)
            return new ThuMucThuong(tenTaiNguyen);
        if (line.find("ThuMucBackup") != string::npos)
            return new ThuMucBackUp(tenTaiNguyen);
        return nullptr;
    }

    static HeThong* docFile(const string& filename){
        ifstream ifs(filename);
        if (!ifs){
            throw FileNotFoundException(3, filename + " was not found");
        }

        string line;
        getline(ifs, line);
        string tenHeThong = line.substr(8);

        HeThong* ht = new HeThong(tenHeThong);
        vector<ThuMuc*> st;

        while (getline(ifs, line)){
            if (!st.empty() && line == st.back()->layMaSo()){
                st.pop_back();
                continue;
            }
            if (line.find("(") != string::npos){
                string tenTaiNguyen = HeThong::parseTenTaiNguyen(line);
                bool laThuMuc = false;

                TaiNguyen* tn = taoTaiNguyen(ifs, line, tenTaiNguyen, laThuMuc);
                if (tn == nullptr){
                    throw InvalidDataException(4, "Invalid file format");
                }

                if (!st.empty())
                    st.back()->themTapTin(tn);
                else
                    ht->themTaiNguyen(tn);
            
                if (laThuMuc)
                    st.push_back(static_cast<ThuMuc*>(tn));
            }
        }
        return ht;
    }

    void timMaxBackup(TaiNguyen* tn, ThuMucBackUp*& maxBackup, int& maxTT){
        ThuMucBackUp* tmbp = dynamic_cast<ThuMucBackUp*>(tn);
        if (tmbp){
            int soLuong = tmbp->demTapTin();
            if (soLuong > maxTT){
                maxTT = soLuong;
                maxBackup = tmbp;
            }
        }
        ThuMuc* tm = dynamic_cast<ThuMuc*>(tn);
        if (tm){
            for (TaiNguyen* tmc: tm->layDSTaiNguyen()){
                timMaxBackup(tmc, maxBackup, maxTT);
            }
        }
    }
};

int main(){
    try{
        HeThong* ht = HeThong::docFile("data/data3.txt");
        cout << *ht;

        ThuMucBackUp* tmb = nullptr;
        int maxTT = -1;
        for (TaiNguyen* tn: ht->layDSTaiNguyen()){
            ht->timMaxBackup(tn, tmb, maxTT);
        }
        if (tmb){
            cout << "ThuMucBackup voi max TapTin: " << tmb->layMaSo() << endl;
            cout << "So luong TapTin: " << maxTT << endl;
        }
        else{
            cout << "Khong tim thay ThuMucBackup thoa man\n";
        }
        
        delete ht;
    }
    catch (const MyException& e){
        cout << "Custom error: " << e.what() << endl;
    }
    return 0;
}