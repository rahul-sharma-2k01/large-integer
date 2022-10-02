#include "BigInteger.h"
using namespace std;
int main(){
    BigInteger num1("123");
    BigInteger num2("-23");
    cout<<string(-num2)<<"\n";
    return 0;
}