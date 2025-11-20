#include "SLList.h"

class ListDHTT{
public:
    class DongHoTT{
    private:
        int min, sec, msec;

        void chuanHoa(){
            if (msec > 1000){
                sec += msec / 1000;
                msec %= 1000;
            }
            if (sec > 60){
                min += sec / 60;
                sec %= 60;
            }
        }
    public:
        DongHoTT(){
            min = sec = msec = 0;
        }
        DongHoTT(int min, int sec, int msec){
            this->min = min;
            this->sec = sec;
            this->msec = abs(msec);

            chuanHoa();
        }
        DongHoTT(int sec, int msec){
            min = 0;
            this->sec = sec;
            this->msec = msec;

            chuanHoa();
        }
        DongHoTT(int msec){
            min = 0;
            sec = 0;
            this->msec = msec;

            chuanHoa();
        }
        DongHoTT(const char* tg){
            char *tgCpy = new char[strlen(tg) + 1];
            strcpy(tgCpy, tg);
            char *split = strtok(tgCpy, ":");
            min = atoi(split);
            split = strtok(nullptr, ":");
            sec = atoi(split);
            split = strtok(nullptr, ":");
            msec = atoi(split);

            chuanHoa();
            delete[] tgCpy;
        }
        DongHoTT(const DongHoTT& other){
            this->min = other.min;
            this->sec = other.sec;
            this->msec = other.msec;

            chuanHoa();
        }

        bool operator>(const DongHoTT& other){
            if (this->min != other.min){
                return this->min > other.min;
            }
            if (this->sec != other.sec){
                return this->sec > other.sec;
            }
            return this->msec > other.msec;
        }

        friend DongHoTT operator+(const DongHoTT& dhtt1, const DongHoTT& dhtt2){
            ListDHTT::DongHoTT res(dhtt1.min + dhtt2.min,
                                dhtt1.sec + dhtt2.sec,
                                dhtt1.msec + dhtt2.msec);
            return res;
        }
        friend DongHoTT operator+(int msec, const DongHoTT& dhtt){
            ListDHTT::DongHoTT dhttOther(msec);
            return dhttOther + dhtt;
        }

        DongHoTT& operator++(){
            msec += 1;
            chuanHoa();
            return *this;
        }
        DongHoTT operator++(int){
            DongHoTT temp = *this;
            msec += 1;
            chuanHoa();
            return temp;
        }

        friend ostream& operator<<(ostream& out, const DongHoTT& dhtt){
            out << setw(3) << setfill('0') << dhtt.min << ":"
                << setw(2) << setfill('0') << dhtt.sec << ":"
                << setw(3) << setfill('0') << dhtt.msec;
            return out;
        }

        int getMin() const{ return min; }
    };
private:
    SLList<DongHoTT> data;
public:
    ListDHTT(){}

    using Iterator = SLList<DongHoTT>::Iterator;
    Iterator begin(){
        return data.begin();
    }
    Iterator end(){
        return data.end();
    }

    void AddTail(DongHoTT dhtt){
        data.AddTail(dhtt);
    }

    friend ostream& operator<<(ostream& out, const ListDHTT& list){
        out << list.data;
        return out;
    }
};


bool funcCountIf(const ListDHTT::DongHoTT& dhtt){
    return dhtt.getMin() >= 60;
}

int main() {
    ListDHTT list;
    ListDHTT::DongHoTT dhtt1(20, 70, -2076), dhtt2("37:87:194"), dhtt3(200, 8060), dhtt4(40001);

    cout << "dhtt1: " << dhtt1 << endl; // format: 000:00:000
    cout << "dhtt2: " << dhtt2 << endl;

    list.AddTail("1:2:3");
    list.AddTail(dhtt3 + dhtt2);
    list.AddTail(10000 + dhtt4);

    list.AddTail(10000 + ++dhtt1++ + dhtt2++);
    cout << "List:\n" << list << endl;

    int nCI = count_if(list.begin(), list.end(), funcCountIf);
    cout << "So DHTT co phut >= 60: " << nCI << endl;

    ListDHTT::DongHoTT dhttMax = *list.begin();
    for_each(list.begin(), list.end(), [&dhttMax](ListDHTT::DongHoTT dhtt) {
        if (dhtt > dhttMax)
            dhttMax = dhtt;
    });

    cout << "DHTT Lon Nhat: " << dhttMax << endl;

    // TODO: Add .hours() to ListDHTT::DongHoTT
}