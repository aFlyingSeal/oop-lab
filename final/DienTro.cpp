#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class MyException: public runtime_error{
private:
    string errorDescription;
    int errorCode;
public:
    MyException(int errCode, const string& errDesc): runtime_error(BuildErrorMessage(errCode, errDesc)){
        errorDescription = errDesc;
        errorCode = errCode;
    }
    string& GetErrorDescription(){
        return errorDescription;
    }
    int GetErrorCode(){
        return errorCode;
    }
private:
    static const string BuildErrorMessage(int errCode, const string& errorDesc){
        string message = "";
        message = message + "Error code: " + to_string(errCode);
        message = message + " - Description: " + errorDesc;
        return message;
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

class MachDien{
protected:
    string maSo;
public:
    MachDien(string maSo){
        if (maSo == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->maSo = maSo;
    }
    virtual ~MachDien(){}

    virtual float tinhDienTro() = 0;
    virtual float tinhTriGia() = 0;

    virtual void inThongTin(ostream& out, int depth) = 0;

    string layMaSo(){ return maSo; }
};

class MachDon: public MachDien{
private:
    float dienTro, triGia;
public:
    MachDon(string maSo, float dienTro, float triGia): MachDien(maSo){
        if (dienTro <= 0 || triGia <= 0){
            throw InvalidDataException(4, "Argument must not be negative");
        }
        this->dienTro = dienTro;
        this->triGia = triGia;
    }

    float tinhDienTro(){
        return dienTro;
    }
    float tinhTriGia(){
        return triGia;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[MachDon] " << maSo << endl;
        out << indent << "DienTro: " << dienTro << ", ";
        out << "TriGia: " << triGia << endl;
    }
};

class MachPhuc: public MachDien{
protected:
    vector<MachDien*> dsMachCon;
public:
    MachPhuc(string maSo): MachDien(maSo){}
    ~MachPhuc(){
        for (MachDien* md: dsMachCon){
            delete md;
        }
    }

    void themMachCon(MachDien* mdc){
        if (mdc == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsMachCon.push_back(mdc);
    }
};

class MachNoiTiep: public MachPhuc{
public:
    MachNoiTiep(string maSo): MachPhuc(maSo){}

    float tinhDienTro(){
        float tongTro = 0.0;
        for (MachDien* md: dsMachCon){
            tongTro += md->tinhDienTro();
        }
        return tongTro;
    }
    float tinhTriGia(){
        float tongTriGia = 0.0;
        for (MachDien* md: dsMachCon){
            tongTriGia += md->tinhTriGia();
        }
        return tongTriGia;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[MachNoiTiep] " << maSo << endl;
        out << indent << "DienTro: " << tinhDienTro() << ", ";
        out << "TriGia: " << tinhTriGia() << endl;
        for (MachDien* md: dsMachCon){
            md->inThongTin(out, depth + 1);
        }
    }
};

class MachSongSong: public MachPhuc{
public:
    MachSongSong(string maSo): MachPhuc(maSo){}

    float tinhDienTro(){
        float tongTro = 0.0;
        for (MachDien* md: dsMachCon){
            tongTro += 1.0/(md->tinhDienTro());
        }
        return 1.0/tongTro;
    }
    float tinhTriGia(){
        float tongTriGia = 0.0;
        for (MachDien* md: dsMachCon){
            tongTriGia += md->tinhTriGia();
        }
        return 1.1 * tongTriGia;
    }

    void inThongTin(ostream& out, int depth){
        string indent = string(4 * depth, ' ');
        out << indent << "[MachSongSong] " << maSo << endl;
        out << indent << "DienTro: " << tinhDienTro() << ", ";
        out << "TriGia: " << tinhTriGia() << endl;
        for (MachDien* md: dsMachCon){
            md->inThongTin(out, depth + 1);
        }
    }
};

class BoMach{
private:
    string tenBoMach;
    vector<MachDien*> dsMachDien;

    static string layMaSo(const string& s){
        int left = s.find('(');
        int right = s.find(')');
        if (left == string::npos || right == string::npos || left >= right){
            throw IndexOutOfRangeException(2, "Index out of range");
        }
        return s.substr(left + 1, right - left - 1);
    }
public:
    BoMach(const string& tenBoMach){
        if (tenBoMach == ""){
            throw InvalidDataException(4, "Argument must not be empty");
        }
        this->tenBoMach = tenBoMach;
    }
    ~BoMach(){
        for (MachDien* md: dsMachDien){
            delete md;
        }
    }

    void themMachDien(MachDien* md){
        if (md == nullptr){
            throw NullReferenceException(1, "Argument must not be null");
        }
        dsMachDien.push_back(md);
    }

    void inThongTin(ostream& out){
        out << tenBoMach << endl;
        for (MachDien* md: dsMachDien){
            md->inThongTin(out, 1);
        }
    }

    static BoMach docFile(const string& filename){
        ifstream ifs(filename);

        if (!ifs){
            throw FileNotFoundException(3, filename + " is not found");
        }

        string line;
        getline(ifs, line);

        string tenBoMach = line.substr(7);
        BoMach bm(tenBoMach);
        
        vector<MachPhuc*> stack;

        while (getline(ifs, line)){
            if (line.find("MachDon") != string::npos){
                string maSo = layMaSo(line);
                float dienTro, triGia;
                ifs >> dienTro >> triGia;
                ifs.ignore();
                MachDon* md = new MachDon(maSo, dienTro, triGia);
                if (!stack.empty()){
                    stack.back()->themMachCon(md);
                }
                else{
                    throw IndexOutOfRangeException(2, "Index out of range");
                }
            }
            else if (line.find("MachNoiTiep") != string::npos){
                string maSo = layMaSo(line);
                getline(ifs, line);
                getline(ifs, line);
                MachNoiTiep* mnt = new MachNoiTiep(maSo);
                if (!stack.empty()){
                    stack.back()->themMachCon(mnt);
                }
                else{
                    bm.themMachDien(mnt);
                }
                stack.push_back(mnt);
            }
            else if (line.find("MachSongSong") != string::npos){
                string maSo = layMaSo(line);
                getline(ifs, line);
                getline(ifs, line);
                MachSongSong* mss = new MachSongSong(maSo);
                if (!stack.empty()){
                    stack.back()->themMachCon(mss);
                }
                else{
                    bm.themMachDien(mss);
                }
                stack.push_back(mss);
            }
            else{
                if (stack.empty()){
                    throw IndexOutOfRangeException(2, "Index out of range");
                }
                if (line == stack.back()->layMaSo()){
                    stack.pop_back();
                }
            }
        }
        return bm;
    }
};

int main(){
    try{
        BoMach bm = BoMach::docFile("data/data1.txt");
        bm.inThongTin(cout);
    }
    catch (const MyException& e){
        cout << "Custom error: " << e.what() << endl;
    }
}

