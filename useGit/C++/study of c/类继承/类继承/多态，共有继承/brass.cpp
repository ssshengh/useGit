#include "/home/shenheng/c1/study of c/类继承/类继承/多态，共有继承/brass.h"    
#include <iostream>
using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;

//设置输出流为科学计数法与定点计数
format setFormat();

/**设置输出流模式以及精度
 * @param f    输出流模式
 * @param p   设置精度
*/
void restore(format f , precis p);

Brass :: Brass(const std::string &s  , long an , double bal){
    fullName = s;
    acctNum = an;
    balance = bal;
}

//放贷
void Brass::Deposit(double amt) {
    if(amt < 0)
        cout<<"负数的账户是不存在的；"
                <<"存款失败～\n";
    else
        balance += amt;
}

void Brass::WithDraw(double amt){
    //设置为###.##的模式
    format initialState = setFormat();
    precis prec = cout.precision(2);

    if(amt<0)
        cout<<"负数的取钱是不存在的;"
                <<"取款失败～\n";
    else if(amt <= balance)
        balance -= amt;
    else
        cout<<"取款金额￥"<<amt<<" 超过您的账户余额，取款失败"<<"\n";
    restore(initialState , prec);//重新设置一遍，不太清楚为什么
}

double Brass::GetBalance() const {
    return balance;
}

void Brass::viewAcct() const{
        //设置为###.##的模式
    format initialState = setFormat();
    precis prec = cout.precision(2);
    
    cout<<"用户："<<fullName<<'\n'
            <<"账户号："<<acctNum<<'\n'
            <<"余额：￥"<<balance<<endl;
    restore(initialState , prec);       
}

//继承类方法
BrassPlus::BrassPlus(const std::string &s  , long an  , double bal ,
                            double ml  , double r ) : Brass(s, an , bal)
{
    maxLoan = ml;
    owsBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba , double ml , double r )
                        : Brass(ba)
{
    maxLoan = ml;
    rate = r;
    owsBank = 0.0;
}

void BrassPlus::viewAcct() const {
    //设置为###.##的模式
    format initialState = setFormat();
    precis prec = cout.precision(2);

    Brass::viewAcct();
    cout<<"最大可贷款：￥"<<maxLoan<<endl;
    cout<<"属于银行的金额：￥"<<owsBank<<endl;
    cout.precision(3);
    cout<<"贷款利率："<<100*rate<<"%\n";
    restore(initialState , prec); 
}
void BrassPlus::WithDraw(double amt) {
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = GetBalance();

    if(amt<=bal)
        Brass::WithDraw(amt);//这里使用作用域限定符因为有一个和它一样的函数
    else if( amt<=bal + maxLoan - owsBank )
    {
        double advance = amt - bal;
        owsBank += advance*(1.0 + rate);
        cout<<"银行给你付的：￥"<<advance<<endl;
        cout<<"财务费 ：￥"<<advance*rate<<endl;
        Deposit(advance);
        Brass::WithDraw(amt);
    }
    else    
        cout<<"信用透支，银行无法为您处理。事务取消！"<<endl;
    restore(initialState , prec); 
}








format setFormat(){
    return cout.setf(std::ios_base::fixed , std::ios_base::floatfield);
}
void restore(format f , precis p){
    cout.setf(f,std::ios_base::floatfield);
    cout.precision(p);
}