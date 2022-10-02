#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include<bits/stdc++.h>
#define MAX 10000 //for strings
using namespace std;

class BigInteger{
    private:
        string number;
        bool sign;
    public:
        //Constructors
        BigInteger();  //Empty Constructor intializes to zero
        BigInteger(string s);  //string constructor
        BigInteger(string s, bool sin);  //string constructor with sign
        BigInteger(int n);  //Int constructor

        void setNumber(string s); //Setting number from a string
        const string& getNumber(); //Retrieving the number
        void setSign(bool s); //Setting sign
        const bool& getSign(); //Retrieving sign

        BigInteger absolute(); //Return the Absolute value

        //Operators
        BigInteger operator + (BigInteger b);
        BigInteger operator - (BigInteger b);
        BigInteger operator * (BigInteger b);
        BigInteger operator / (BigInteger b);
        BigInteger operator % (BigInteger b);
        
        BigInteger& operator ++(); //Prefix increment overloading
        BigInteger operator ++(int); //Postfix increment overloading
        BigInteger& operator --(); //Prefix decrement overloading
        BigInteger operator --(int); //Postfix decrement overloading
        BigInteger operator -(); //Unary minus

        void operator =(BigInteger b);
        BigInteger& operator += (BigInteger b);
        BigInteger& operator -= (BigInteger b);
        BigInteger& operator *= (BigInteger b);
        BigInteger& operator /= (BigInteger b);
        BigInteger& operator %= (BigInteger b);

        bool operator ==(BigInteger b);
        bool operator !=(BigInteger b);
        bool operator >(BigInteger b);
        bool operator <(BigInteger b);
        bool operator >=(BigInteger b);
        bool operator <=(BigInteger b);

        BigInteger& operator [](int n);//Array index operator
        operator string(); //for converting fron BigInteger to string

    private:
        bool equals(BigInteger n1, BigInteger n2);
        bool less(BigInteger n1, BigInteger n2);
        bool greater(BigInteger n1, BigInteger n2);

        string add(string number1, string number2);
        string subtract(string number1, string number2);
        string multiply(string number1, string number2);
        pair<string, long long> divide(string n, long long den);

        string toString(long long n);
        long long toInt(string n);
};

//----------------Constructors-------------------
//Empty Constructor(set number to zero)
BigInteger::BigInteger(){
    number="0";
    sign=false;
}

//Constructing by string
BigInteger::BigInteger(string s){
    if(isdigit(s[0])){//+ve case
        setNumber(s);
        sign=false;
    }
    else{
        setNumber(s.substr(1));
        sign=(s[0]=='-');
    }
}

//Constructing by string and sign
BigInteger::BigInteger(string s, bool sin){
    setNumber(s);
    setSign(sin);
}

//Constructing by integer
BigInteger::BigInteger(int n){
    stringstream ss;
    string s;
    ss<<n;
    ss>>s;

    if(isdigit(s[0])){
        setNumber(s);
        setSign(false);
    }
    else{
        setNumber(s.substr(1));
        setSign(s[0]=='-');
    }
}


//------------------Set-Get Functions---------------------
void BigInteger::setNumber(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]<'0' || s[i]>'9'){
            throw "Not a number";
        }
    }
    number=s;
}

const string& BigInteger::getNumber(){
    return number;
}

void BigInteger::setSign(bool s){
    sign=s;
}

const bool& BigInteger::getSign(){
    return sign;
}

//Returning without sign
BigInteger BigInteger::absolute(){
    return BigInteger(getNumber());
}


//----------------Operators-------------------

//-----Arithmatic Operators----- 
BigInteger BigInteger::operator + (BigInteger b){
    BigInteger addition;

    //If Signs are same
    if(getSign()==b.getSign()){
        addition.setNumber(add(getNumber(), b.getNumber()));
        addition.setSign(getSign());
    }

    //if Signs are different
    else{
        if(absolute()>b.absolute()){
            addition.setNumber(subtract(getNumber(), b.getNumber()));
            addition.setSign(getSign());
        }
        else{
            addition.setNumber(subtract(b.getNumber(), getNumber()));
            addition.setSign(b.getSign());
        }
    }

    //If resultant is -0
    if(addition.getNumber()=="0") addition.setSign(false);
    return addition;
}

BigInteger BigInteger::operator - (BigInteger b){
    //Coverting subtraction to addition
    b.setSign(!b.getSign());//Because +(-)=- && -(-)=+
    return (*this)+b;
}

BigInteger BigInteger::operator * (BigInteger b){
    BigInteger mul;

    mul.setNumber(multiply(getNumber(), b.getNumber()));
    mul.setSign(getSign()!=b.getSign());

    //If resultant is -0
    if(mul.getNumber()=="0") mul.setSign(false);
    return mul;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"(Limitation)
BigInteger BigInteger::operator / (BigInteger b){
    long long den=toInt(b.getNumber());
    BigInteger div;

    div.setNumber(divide(getNumber(), den).first);
    div.setSign(getSign()!=b.getSign());

    //If resultant is -0
    if(div.getNumber()=="0") div.setSign(false);
    return div;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger:: operator %(BigInteger b){
    long long den=toInt(b.getNumber());

    BigInteger rem;
    long long rem_int=divide(number, den).second;
    rem.setNumber(toString(rem_int));
    rem.setSign(getSign()!=b.getSign());

    //If resultant is -0
    if(rem.getNumber()=="0") rem.setSign(false);
    return rem;
}

//-----------Unary Minus Operator--------------
BigInteger BigInteger::operator - (){
    return (*this)*-1;
}

//-----Increment/Decrement Operator-----
//Reference to be returned(where possible)(We can't return reference of a local variable)
BigInteger& BigInteger::operator ++(){
    (*this)=(*this)+1;
    return (*this);
}

BigInteger BigInteger::operator ++(int){
    BigInteger before=(*this);
    (*this)=(*this)+1;
    return before;
}

BigInteger& BigInteger::operator --(){
    (*this)=(*this)-1;
    return (*this);
}

BigInteger BigInteger::operator --(int){
    BigInteger before=(*this);
    (*this)=(*this)-1;
    return before;
}

//-----Assignment Operators-----
//Reference to be returned
void BigInteger::operator = (BigInteger b){
    setNumber(b.getNumber());
    setSign(b.getSign());
}

BigInteger& BigInteger::operator +=(BigInteger b){
    (*this)=(*this)+b;
    return (*this);
}

BigInteger& BigInteger::operator -= (BigInteger b) {
    (*this) = (*this) - b;
    return (*this);
}

BigInteger& BigInteger::operator *= (BigInteger b) {
    (*this) = (*this) * b;
    return (*this);
}

BigInteger& BigInteger::operator /= (BigInteger b) {
    (*this) = (*this) / b;
    return (*this);
}

BigInteger& BigInteger::operator %= (BigInteger b) {
    (*this) = (*this) % b;
    return (*this);
}


//-----Relational Operators-----
bool BigInteger::operator == (BigInteger b){
    return equals((*this), b);
}

bool BigInteger::operator != (BigInteger b){
    return !equals((*this), b);
}
bool BigInteger::operator > (BigInteger b){
    return greater((*this), b);
}
bool BigInteger::operator < (BigInteger b){
    return less((*this), b);
}
bool BigInteger::operator >= (BigInteger b){
    return equals((*this), b) || greater((*this), b);
}
bool BigInteger::operator <= (BigInteger b){
    return equals((*this), b) || less((*this), b);
}

// ------------Array Index Operator--------------
BigInteger& BigInteger::operator [](int n){
    return *(this+(n*sizeof(BigInteger)));
}

//-----------For converting to string-------
BigInteger::operator string(){
    string signedString=(getSign())?"-":"";
    signedString+=number;
    return signedString;
}

//--------------------Private Function(used inside)-----------
bool BigInteger::equals(BigInteger n1, BigInteger n2){
    return (n1.getNumber()==n2.getNumber())&&(n1.getSign()==n2.getSign());
}

bool BigInteger::less(BigInteger n1, BigInteger n2){
    bool sign1=n1.getSign();
    bool sign2=n2.getSign();

    //n1 is -ve(definitely less)
    if(sign1 && !sign2) return true;

    //n2 is -ve(definitely greater)
    else if(!sign1 && sign2) return false;

    //Both positive
    else if(!sign1 && !sign2){
        if(n1.getNumber().length()<n2.getNumber().length()) return true;
        if(n1.getNumber().length()>n2.getNumber().length()) return false;
        return n1.getNumber()<n2.getNumber();
    }
    
    //Both Negative
    else{
        if(n1.getNumber().length()>n2.getNumber().length()) return true;
        if(n1.getNumber().length()<n2.getNumber().length()) return false;
        return n1.getNumber()>n2.getNumber();
    }
}

bool BigInteger::greater(BigInteger n1, BigInteger n2){
    return !equals(n1, n2) && !less(n1, n2);
}

string BigInteger::add(string number1, string number2){
    //Making result string of maximum length
    string add=(number1.length()>number2.length())?number1:number2;
    char carry='0';
    int differenceLength=abs((int)(number1.length()-number2.length()));

    //Making both string of equal lengths
    if(number1.length()>number2.length()){
        number2.insert(0, differenceLength, '0');
    }
    else{
        number1.insert(0, differenceLength, '0');
    }

    //Performing addition
    for(int i=number1.length()-1;i>=0;i--){
        add[i]=((carry-'0')+(number1[i]-'0')+(number2[i]-'0'))+'0';

        if(add[i]>'9'){
            add[i]-=10;
            carry='1';
        }
        else carry='0';
    }
    if(carry=='1') add.insert(0,1,'1');
    return add;
}

string BigInteger::subtract(string number1,string number2){

    //Making subtraction string of maximum length
    string sub=(number1.length()>number2.length())?number1:number2;
    int differenceLength=abs((int)(number1.length()-number2.length()));

    //Making both number strings of equal length
    if(number1.size()>number2.size())
        number2.insert(0, differenceLength, '0');
    else
        number1.insert(0, differenceLength, '0');
    
    //Performing subtraction
    for(int i=number1.length()-1;i>=0;i--){
        if(number1[i]<number2[i]){
            number1[i]+=10;
            number1[i-1]--;
        }
        sub[i]=((number1[i]-'0')-(number2[i]-'0'))+'0';
    }

    //Removing leading zeroes
    while(sub[0]=='0' && sub.length()!=1){
        sub.erase(0,1);
    }
    return sub;
}

string BigInteger::multiply(string n1, string n2){

    //To assure n2 is greater than n2
    if(n1.length()>n2.length()) n1.swap(n2);
    string res="0";

    //Multiplying one by one digit of n1 to n2 and increasing one 0 at last each time
    for(int i=n1.length()-1;i>=0;i--){
        string temp=n2;
        int currentDigit=n1[i]-'0';
        int carry=0;
        for(int j=temp.length()-1;j>=0;j--){
            temp[j]=((temp[j]-'0')*currentDigit)+carry;
            if(temp[j]>9){
                carry=(temp[j]/10);
                temp[j]%=10;
            }
            else carry=0;
            temp[j]+='0';
        }

        //Handling remaining carry
        if(carry>0){
            temp.insert(0,1,(carry+'0'));
        }

        //Appending 0 like in real multiplication
        temp.append((n1.length()-i-1), '0');

        //Adding towards making final answer
        res=add(res,temp);
    }

    //Removing leading zeroes
    while(res[0]=='0' && res.length()!=1){
        res.erase(0,1);
    }

    return res;
}

//For divide and modulus 
pair<string, long long> BigInteger::divide(string n, long long den){
    long long rem=0;
    string result;
    int len=n.length();
    result.resize(len);

    for(int i=0;i<len;i++){
        rem=(rem*10)+(n[i]-'0');
        result[i]=rem/den+'0';
        rem%=den;
    }

    //Removing leading 0's
    while(result[0]=='0' && result.length()!=1)
        result.erase(0,1);
    
    //If den is greater than n
    if(result.length()==0){
        result="0";
    }
    return {result, rem};
}

//Converting integer to string (upto long long range)
string BigInteger::toString(long long n){
    stringstream ss;
    string temp;
    ss<<n;
    ss>>temp;
    return temp;
}

//Coverting string to integer(upto long long range)
long long BigInteger::toInt(string s){
    long long sum=0;
    for(int i=0;i<s.length();i++){
        sum=(sum*10)+(s[i]-'0');
    }
    return sum;
}

#endif
