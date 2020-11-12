#ifndef  BRASS_H_
#define BRASS_H_
#include<string>
#include <iostream>

class Brass
{
private:
    std::string fullName;//持户人姓名
    long    acctNum;//账号
    double balance;//当前节余

public:
    Brass(const std::string &s = "NullName" , long an = -1 , double bal = 0.0);
    //存款
    void Deposit(double amt);
    //取款
    virtual void WithDraw(double amt);
    double GetBalance() const ;
    //查看账户
    virtual void viewAcct() const;
    virtual ~Brass() {std::cout <<"Bye~~~"<<'\n';}
};


//多态的关键是：方法的具体使用随着调用的对象而改变
//两个办法：在字类的重新定义方法，或者使用虚方法
class BrassPlus : public Brass
{
private:
    double maxLoan;//透支上限
    double rate;//利率
    double owsBank;
public:
    BrassPlus (const std::string &s = "NullName" , long an = -1 , double bal = 0.0,
                            double ml = 500 , double r = 0.11125);
    BrassPlus(const Brass & ba , double ml = 500 , double r = 0.11125);

    virtual void viewAcct() const;
    //余额
    virtual void WithDraw(double amt);
    void resetMaxLoan(double m) {maxLoan = m;}
    void resetRate(double r) { rate = r;}
    void resetOwes() { owsBank = 0;}
};
//两个类的virtual方法，其实是不同的，通过对象类型来确定
//但具体的使用：如果是使用对象，那么点作用符就会调用其对应的方法
//如果是使用指针或者引用，没有virtual的时候，那是根据指针或者引用的类型来判断
//如果是virtual的话，那么是根据指针或引用指向的地址种的对象的类型来判断

//在这里，有一个关键的是，基类中的析构变成了virtual 方便以正确的方式释放内存

#endif