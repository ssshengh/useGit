
//私有继承，基类的公有成员和保护成员将会变成继承类的私有成员，意味着基类方法不会成为派生类对象公有接口的一部分，但可以在派生类成员函数种使用他们
//使用公有继承，基类的公有方法成为派生类的公有方法，——>派生类将继承基类接口
//使用私有继承，基类的公有方法成为派生类的私有办法，——>派生类不继承接口
//和has-a关系一样，获得实现，但不获得接口
//子对象——>通过继承或包含添加的对象


//注意和另一个studentc类对象
#ifndef  STUDENTB_H_
#define STUDENTB_H_

#include <iostream>
#include <valarray>
#include <string>

class studentb : private std::string , private std::valarray<double> //注意这里就限定了类型
{
private:
    typedef std::valarray<double>  ArraryDb;
    std::ostream & arr_out(std::ostream & os) const;
    //第一个和包含对象的区分，不需要使用定义一个对象来在里面调用string和valarry的接口
public:
    studentb() : std::string("Null Student") , ArraryDb(){}

    //第二个区分:在进行构造函数的声明时，成员初始化列表直接使用基类的类名
    explicit studentb(const std::string & s ) : std::string(s) , ArraryDb(){}
    explicit studentb(int n ) : std::string("Null Student ") , ArraryDb(n){}

    studentb(const std::string & s , int n ) : std::string(s) , ArraryDb(n) {}
    studentb(const std::string & s , const ArraryDb & a) : std::string(s) , ArraryDb(a){}
    studentb(const char * str , const double * pd , int n ) : std::string(str) , ArraryDb(pd , n ){}

    ~studentb() {}


    //要让基类方法在派生类可用有两个办法
    //一、声明一个一样的办法，重载。二、使用using重新定义访问权限
    double sum() const;
    //注意，using声明时只能有成员名，不能有圆括号、函数特征标和返回类型
    //这种方法只有继承可用
    using std::valarray<double>::max;

    double Average() const;
    const std::string & Name() const;
    double & operator [] ( int i );
    double operator[] ( int i ) const;    

    //input
    friend std::istream & operator>>(std::istream & is , studentb & stu);
    friend std::istream & getline(std::istream & is , studentb & stu);

    //output
    friend std::ostream & operator<<(std::ostream & os , const studentb & stu);   
};


double studentb::sum() const{
    return std::valarray<double>::sum();
}

//私有继承中调用基类接口通过作用域解析符
double studentb::Average() const{
    if(ArraryDb::size() > 0)
        return ArraryDb::sum()/ArraryDb::size();
    else
        return 0;
}

//没有了name，如何访问基类的对象呢？ 使用强制类型转换！
const std::string & studentb::Name() const {
    return (const std::string &) *this;//通过this指针调用studengtb对象，再强制将这个对象转变为string，则得到的就是student内的string
}


//如何访问友元函数呢
//但是即使这个时公有继承也需要显示转换，一是，不使用的话 os<<stu 将和函数原型匹配，递归了
//二是，这个类是多继承，编译器无法确定具体是应该变为哪个基类，如果两个基类都提供了operator<<
std::ostream & operator<<(std::ostream & os , const studentb & stu){
    os << "Scores for " << (const std::string &)stu << ":\n";//显示的转换为string，进而调用了  operator<<(ostream & , const string &)  !!!!!!!!
    stu.arr_out(os);
    return os;
}


double & studentb :: operator[](int i ) 
{
    return ArraryDb::operator[](i);//注意是这么调的
}


std::istream & getline(std::istream & is , studentb & stu){
    getline(is , (std::string &) stu);
    return is;
}


//何时使用包含，何时使用私有继承来处理包含成员对象的类呢？
//关键再与是否需要访问保护成员或者重载虚函数，如果是的话，那就是私有继承，否则都是包含

//保护继承
//保护继承是私有继承的变体，和私有继承类似，保护继承将基类的公有成员和保护成员均视为保护成员，基类的接口在派生类中也可以使用
//最大的区别在于第三代类，私有继承的第三代类不能访问基类的接口，但是保护继承可以

//特征                                                          公有继承                                                    私有继承                                                        保护继承
//公有成员变成                                  派生类公有成员                                      派生类私有成员                                             派生类保护成员   
//保护————                                  ————保护                                          ————私有                                                  ————保护
//私有————                                 只能通过基类接口访问——————————————————————————————
//能否隐式向上转换                                  是                                                                  否                                                             是（但只能在派生类中）

#endif