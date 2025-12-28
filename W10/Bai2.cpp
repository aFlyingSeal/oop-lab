#include<iostream>
#include<math.h>
#include<stdexcept>

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
    static double RunTest3(CA* pCA){
        if (pCA == nullptr){
            throw runtime_error("Argument must not be null");
        }
        double rs = pCA->GetTest();
        return sqrt(rs);
    }
};

class Level2{
public:
    static double RunTest2(){
        CA* pCA = nullptr;
        double dRS = Level1::RunTest3(pCA);
        return sqrt(dRS);
    }
};

int main(){
    // cout << Level1::RunTest3(nullptr) << endl;
    // system("pause");
    // return 0;

    try{
        cout << Level2::RunTest2() << endl;
    }
    catch (const exception& ex){
        cout << "error: " << ex.what() << endl;
    }

    system("pause");
    return 0;
}