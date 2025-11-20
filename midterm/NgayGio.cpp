#include "SLList.h"

class ListNG{
public:
    class NgayGio{
    private:
        int thang, ngay, gio;

        void chuanHoa(){
            if (gio > 24){
                ngay += gio / 24;
                gio %= 24;
            }
            if (ngay > 30){
                thang += ngay / 30;
                ngay %= 30;
            }
        }
    public:
        NgayGio(){
            thang = ngay = gio = 0;
        }
        NgayGio(int thang, int ngay, int gio){
            this->thang = thang;
            this->ngay = ngay;
            this->gio = abs(gio);

            chuanHoa();
        }
        NgayGio(int ngay, int gio){
            thang = 0;
            this->ngay = ngay;
            this->gio = gio;

            chuanHoa();
        }
        NgayGio(int gio){
            thang = 0;
            ngay = 0;
            this->gio = gio;

            chuanHoa();
        }
        NgayGio(const char* ng){
            char* ngCpy = new char[strlen(ng) + 1];
            strcpy(ngCpy, ng);
            char* split = strtok(ngCpy, "/-");
            thang = atoi(split);
            split = strtok(nullptr, "/-");
            ngay = atoi(split);
            split = strtok(nullptr, "/-");
            gio = atoi(split);

            chuanHoa();
        }
        NgayGio(const NgayGio& other){
            this->thang = other.thang;
            this->ngay = other.ngay;
            this->gio = other.gio;

            chuanHoa();
        }
        
        bool operator>(const NgayGio& other){
            if (this->thang != other.thang){
                return this->thang > other.thang;
            }
            if (this->ngay != other.ngay){
                return this->ngay > other.ngay;
            }
            return this->gio > other.gio;
        }

        friend NgayGio operator+(const NgayGio& ng1, const NgayGio& ng2){
            ListNG::NgayGio res(ng1.thang + ng2.thang,
                                ng1.ngay + ng2.ngay,
                                ng1.gio + ng2.gio);
            return res;
        }
        NgayGio operator+(int soGio){
            gio += soGio;
            chuanHoa();
            return *this;
        }
        friend NgayGio operator+(int soGio, const NgayGio& ng){
            ListNG::NgayGio ngOther(soGio);
            return ngOther + ng;
        }

        NgayGio& operator++(){
            gio += 1;
            chuanHoa();
            return *this;
        }
        NgayGio operator++(int){
            NgayGio temp = *this;
            gio += 1;
            chuanHoa();
            return temp;
        }

        friend ostream& operator<<(ostream& out, const NgayGio& ng){
            out << setw(3) << setfill('0') << ng.thang << "/"
                << setw(2) << setfill('0') << ng.ngay << "-"
                << setw(2) << setfill('0') << ng.gio;
            return out;
        }       
    
        int getThang() const{ return thang; }
    };
private:
    SLList<NgayGio> data;
public:
    ListNG(){}

    using Iterator = SLList<NgayGio>::Iterator;
    Iterator Begin(){
        return data.begin();
    }
    Iterator End(){
        return data.end();
    }

    void PushBack(NgayGio ng){
        data.AddTail(ng);
    }

    friend ostream& operator<<(ostream& out, const ListNG& list){
        out << list.data;
        return out;
    }
};

bool funcFindIf(const ListNG::NgayGio& ng){
    return ng.getThang() > 11;
}

int main(){
    ListNG list;
    ListNG::NgayGio ng1(20, 30, -2113), ng2("13/9-63"), ng3(56, 762), ng4(4864);

    cout << "ng1: " << ng1 << endl;
    cout << "ng2: " << ng2 << endl;
    cout << "ng3: " << ng3 << endl;
    cout << "ng4: " << ng4 << endl;

    list.PushBack("1/2-3");
    list.PushBack(ng1);
    list.PushBack(ng2);
    list.PushBack(ng3);
    list.PushBack(ng4);
    cout << "List:\n" << list << endl;

    list.PushBack(ng1 + ng2);
    list.PushBack(ng3 + 12345);
    list.PushBack(10000 + ng4);
    cout << "List:\n" << list << endl;

    list.PushBack(10000 + ++ng1 + ng2++);
    list.PushBack(10000 + ng1++ + ++ng2);
    cout << "ng1: " << ng1 << endl;
    cout << "ng2: " << ng2 << endl;
    cout << "List:\n" << list << endl;

    ListNG::Iterator it = find_if(list.Begin(), list.End(), funcFindIf);
    cout << "ng co thang > 11: " << *it << endl;

    ListNG::NgayGio ngMin = *list.Begin();
    for_each(list.Begin(), list.End(), [&ngMin](ListNG::NgayGio ng){
        if (ngMin > ng){
            ngMin = ng;
        }
    });
    cout << "ng nho nhat: " << ngMin << endl;
}