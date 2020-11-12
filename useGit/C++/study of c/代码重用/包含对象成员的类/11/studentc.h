#ifndef  STUDENTS_H_
#define STUDENTS_H_

#include <iostream>
#include <string>
#include <valarray>

//我们将其他人定义好的类和方法引入到自己定义的类的时候需要注意一些东西
//这个时候，要准备好使用其他对象成员
//1.studentc的成员函数可以通过String和Vaarray的公有接口来访问和修改，name和scope，但是在类外面的值只能通过studentc的公有接口来访问
//2.我们在一个类中包含其他对象，是一种has-a的关系：学生有姓名和很多科的学科成绩。在is-a的公有继承种，类可以继承接口，也可以继承实现（纯虚函数只提供接口
//          但是，使用has-a的组合，类就只能获得实现，而不能获得接口。eg. string可以通过+将两个字符串拼接，但是对于student来说没什么意义
//          不过有时候被包含的类的接口可能有着意义，比如使用string接口中的<将student对象按序排列，为此我们可以定义函数来使用他的接口

class studentc
{
private:
    typedef std::valarray<double>  ArraryDb;
    std::string name;
    ArraryDb scores;//一个可以进行计算的数组处理多科成绩

    //私有方法，用于成绩的输出
    //因为没有valvarray的实现，所以使用一个辅助函数来帮助实现student成绩的输出
    std::ostream & arr_out(std::ostream & os) const;
public:
    studentc() : name("Null Student") , scores() {}
    //防止从参数类型string到类类型的隐式转换
    explicit studentc(const std::string & s ) : name(s) , scores(){}

    /**防止从参数类型到类类型的隐式转换
     * 如果没有关键字，存在一种情况：studentc doh = ("HH" , 10 )  ; doh = 5        
     * 这时候因为键入的不是doh[0] = 5 ,所以会调用studentc(5) 把5转化为一个临时studentc变量，并将Nully设置为name的值，再用这个临时变量替换原来的doh
    */
    explicit studentc(int n ) : name("Null Student") , scores(n) {}

    //可以和继承的情况区分一下，继承的类声明构造函数时：后是基类名字；现在是包含了成员对象，这里就使用成员名
    studentc(const std::string & s , int n) : name(s)  , scores(n) {}
    studentc(const std::string & s , const ArraryDb & a) : name(s) , scores(a) {}

    //初始化顺序，哪怕name和scores互换位置，也是首先初始化name因为在定义中被先声明了
    studentc(const char* str , const double * pd , int n ) : name(str) , scores(pd , n ){}//可以用一个C风格字符串和一个double类型的数组来赋值，不过注意需要输入长度
    ~studentc() ;

    double Average() const;
    const std::string & Name() const;

    //允许使用[]来访问各项成绩
    double & operator [] ( int i );
    double operator[] ( int i ) const;


    //input
    friend std::istream & operator>>(std::istream & is , studentc & stu);
    friend std::istream & getline(std::istream & is , studentc & stu);

    //output
    friend std::ostream & operator<<(std::ostream & os , const studentc & stu);

};


#endif