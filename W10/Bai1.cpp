#include<iostream>
#include<math.h>

using namespace std;

class CA{
private:
    double _value;
public:
    CA(double v){ _value = v; }

    double GetTest(){
        return this->_value;
    }
};

class Level1{
public:
    // static double RunTest1(CA *pCA){
    //     double rs = pCA->GetTest();
    //     return sqrt(rs);
    // }

    static double RunTest2(CA* pCA){
        if (pCA == nullptr){
            return -1;
        }
        double rs = pCA->GetTest();
        return sqrt(rs);
    }
};

class Level2{
public:
    static double RunTest1(){
        CA* pCA = nullptr;
        double dRS = Level1::RunTest2(pCA);
        if (dRS == -1){
            return -1;
        }
        return sqrt(dRS);
    }
};

int main(){
    // cout << Level1::RunTest1(nullptr) << endl;
    // system("pause");
    // return 0;

    // cout << Level1::RunTest2(nullptr) << endl;
    // system("pause");
    // return 0;

    cout << Level2::RunTest1() << endl;
    system("pause");
    return 0;
}