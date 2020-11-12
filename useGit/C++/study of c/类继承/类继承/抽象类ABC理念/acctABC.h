#ifndef  ACCTABC_H_
#define ACCTABC_H_

#include <iostream>
#include <string>

//ABC理念的核心是，抽象出一些类的基本特征，尽管这些类存在差异，就比如椭圆和圆，它们很像，但是难以彼此表示，于是抽象出他们的共通点
//至少使用一个纯虚韩函数的接口，从ABC类派生出的类，将根据派生类的基本特征，使用常规虚函数实现这种接口

//虚基类
class acctABC
{
private:
    std::string fullname;//名字全称
    long acctNum;//卡号
    double balance;//余额

protected:
    struct Formatting
    {
        std::ios_base::fmtflags flag;
        std::streamsize pr;
    };//描述cout标签的结构体
    
    //这里，通过两个保护函数，提供了对fullname和acctNum的只读访问
    //获取名字
    const std::string & FullName() const { return fullname; }
    //获取银行卡号
    long AcctNum() { return acctNum; }

    /**
     * 这个版本相比原本的继承的版本，解决了setFormate和reset函数与客户同名函数的区分的问题
     * 我们将其放入保护空间，使得他们只对基类和派生类可用，对其他类隐藏
    */

    Formatting setFormat() const;
    void RestoreFormat(Formatting & f ) const;

public:  
    acctABC(const std::string & name = "NullBody" , long an = -1 , double bal = 0.0 );
    //存款
    void Deposit(double amt);
    //取钱，纯虚函数
    virtual void Withdraw(double amt ) = 0;
    //获取余额
    double Balance() { return balance ;}
    //纯虚函数，获取账号
    virtual void ViewAcct() const=0;
    virtual ~acctABC();
};


//Brass Account
class Brass : public acctABC
{
public:
    Brass(const std::string & name = "NullBody" , long an = -1 , double bal = 0.0 ) : acctABC(name,an,bal){}

    virtual void Withdraw(double amt );

    virtual void ViewAcct() const;
    
    virtual ~Brass();
};


class BrassPlus : public acctABC
{
private:
    double maxLoan;
    double rate;
    double owesBank;
public:
    BrassPlus (const std::string & name = "NullBody" , long an = -1 , double bal = 0.0, double ml = 500 , double ra = 0.10);

    BrassPlus(const Brass & ba , double ml = 500 , double ra = 0.10);

    virtual void Withdraw(double amt );

    virtual void ViewAcct() const;

    void ResetMaxLoan (double m ) { maxLoan = m; }

    void resetRate (double ra ) { rate = ra; }  

    void resetOwesBank( ) { owesBank = 0;}

    ~BrassPlus ();
};


#endif