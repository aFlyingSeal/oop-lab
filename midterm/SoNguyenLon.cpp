#include "SLList.h"

class ListSNL{
public:
    class SoNguyenLon{
    private:
        SLList<int> arr;
    public:
        int SLChuSo() const{
            return arr.Size();
        }

        SoNguyenLon(){
            arr.AddHead(0);
        }
        SoNguyenLon(long long num){
            if (num == 0){
                arr.AddHead(0);
                return;
            }
            while (num > 0){
                arr.AddTail(num % 10);
                num /= 10;
            }
        }
        SoNguyenLon(int chuSo, int slChuSo){
            for (int i = 0; i < slChuSo; i++){
                arr.AddTail(chuSo);
            }
        }
        SoNguyenLon(const char* num){
            int size = strlen(num);
            for (int i = size - 1; i >= 0; i--){
                arr.AddTail(num[i] - '0');
            }
        }
        SoNguyenLon(const SoNguyenLon& other){
            arr = other.arr;
        }
        ~SoNguyenLon(){}

        SoNguyenLon operator+(const SoNguyenLon& other){
            SoNguyenLon kq;
            kq.arr.Clear();
            int lenMax = (SLChuSo() > other.SLChuSo()) ? SLChuSo() : other.SLChuSo();
            int lenMin = (!(SLChuSo() > other.SLChuSo())) ? SLChuSo() : other.SLChuSo();
            int nho = 0, temp;
            for (int i = 0; i < lenMin; i++){
                temp = arr[i] + other.arr[i] + nho;
                kq.arr.AddTail(temp % 10);
                nho = temp / 10;
            }
            for (int i = lenMin; i < lenMax; i++){
                if (SLChuSo() == lenMax){
                    temp = arr[i] + nho;
                }
                else{
                    temp = other.arr[i] + nho;
                }
                kq.arr.AddTail(temp % 10);
                nho = temp / 10;
            }
            if (nho > 0){
                kq.arr.AddTail(1);
            }
            return kq;
        }
        friend SoNguyenLon operator+(const SoNguyenLon& snl1, const SoNguyenLon& snl2){
            return snl1 + snl2;
        }
        friend SoNguyenLon operator+(long long num, const SoNguyenLon& snl){
            SoNguyenLon snl_num(num);
            return snl_num + snl;
        }

        SoNguyenLon operator-(const SoNguyenLon& other){
            if (SLChuSo() < other.SLChuSo()){
                return SoNguyenLon((long long)0);
            }
            SoNguyenLon kq;
            kq.arr.Clear();
            int muon = 0, temp;
            for (int i = 0; i < other.SLChuSo(); i++){
                temp = arr[i] - other.arr[i] - muon;
                if (temp < 0){
                    temp += 10;
                    muon = 1;
                }
                else{
                    muon = 0;
                }
                kq.arr.AddTail(temp);
            }
            for (int i = other.SLChuSo(); i < SLChuSo(); i++){
                temp = arr[i] - muon;
                if (temp < 0){
                    temp += 10;
                    muon = 1;
                }
                else{
                    muon = 0;
                }
                kq.arr.AddTail(temp);
            }
            while (kq.SLChuSo() > 0 && kq.arr[kq.SLChuSo() - 1] == 0){
                kq.arr.RemoveTail();
            }
            return kq;
        }
        friend SoNguyenLon operator-(const SoNguyenLon& snl1, const SoNguyenLon& snl2){
            return snl1 - snl2;
        }
        friend SoNguyenLon operator-(long long num, const SoNguyenLon& snl){
            ListSNL::SoNguyenLon snl_num(num);
            return snl_num - snl;
        }

        SoNguyenLon& operator++(){
            int lastIdx = SLChuSo() - 1;
            arr[lastIdx]++;
            return *this;
        }
        SoNguyenLon operator++(int){
            SoNguyenLon temp = *this;
            int lastIdx = SLChuSo() - 1;
            arr[lastIdx]++;
            return temp;
        }

        friend ostream& operator<<(ostream& out, const SoNguyenLon& snl){
            for (int i = snl.SLChuSo() - 1; i >= 0; i--){
                out << snl.arr[i];
            }
            return out;
        }
    };
private:
    SLList<SoNguyenLon> data;
public:
    ListSNL(){}

    void AddTail(SoNguyenLon snl){
        data.AddTail(snl);
    }

    friend ostream& operator<<(ostream& out, const ListSNL& list){
        out << list.data;
        return out;
    }
};

int main(){
    ListSNL list;
    ListSNL::SoNguyenLon snl1(1234), snl2(5, 4), snl3("9999");

    list.AddTail(snl1);
    list.AddTail(snl2);
    list.AddTail(snl3);
    cout << "List: " << list << endl;

    list.AddTail(snl1 + snl2);
    list.AddTail(snl1 + 1111);
    list.AddTail(2222 + snl3);
    cout << "List: " << list << endl;

    list.AddTail(snl1 - snl2);
    list.AddTail(snl2 - snl1);
    list.AddTail(9999 - snl3);
    cout << "List: " << list << endl;
}