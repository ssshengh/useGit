#ifndef  STRINGBAD_H_
#define STRINGBAD_H_
#include <iostream>

//初始的stringBad类不是一个完美的设计，但我们会慢慢的将其变好，注意原本的stringBad和之后所作的改变的差异
class StringBad
{
private:
//原本的不够好的内容

    //利用指针指向一个内存块，记录姓名，便于利用构造函数为其分配内存空间
    //这将在，运行时分配内存，而不是编译时，这很关键
    char * str;
    int len;
    //声明为静态有一个好的特点，就是无论多少个对象，他们都只有一个静态内存块
    //即一个家中的成员共享一部座机
    static int num_strings;

//加一个静态量
    static const int CINLIM = 80;
public:
//原本不够好的内容
    StringBad(const char * ch);
    StringBad();
    ~StringBad();
    friend std::ostream & operator<<(std::ostream & os , const StringBad & st);

//更新构造函数，默认复制，赋值函数，以及完善功能：
    //默认复制函数
    StringBad(const StringBad & st);
    //默认赋值函数
    //注意三个点：一是为了连等，使用了返回一个类对象的引用；二是由于被赋值对象内存内可能有东西所以要先释放；三是要避免赋值给自身
    StringBad & operator = (const StringBad & st);

    //我们的赋值函数只能对一个对象使用，但是我们希望能够直接传入一个常规的c字符串，因此：
    StringBad & operator= (const char * ch);

    int length() const {return len;}
    friend bool operator>(const StringBad & s1, const StringBad & s2);
    friend bool operator<(const StringBad & s1, const StringBad & s2);
    friend bool operator==(const StringBad & s1, const StringBad & s2);
    friend std::istream & operator>>(std::istream & s1,  StringBad & s2);

    //返回值是char&类型的 []()运算，可以使得基本的调用：opera[4] == opera.operator[](4)    
    //如果不是返回值char& 而是重载运算符的StringBad ：那将不能给特定元素赋值：
    //同样的：means("might") ;     means[0] = 'r'      等价于    means.operator[](0) = means.str[0] = "r"
    char & operator [] (int i);
    //非const的使得字符串可读可写，const的只可读
    const char & operator [] (int i) const;

    //静态访问函数只能和静态数据成员相关联，调用时只能使用类不能使用对象甚至this
    static int HowMany(){return num_strings ; };

};

//"love" == answer    等价于    operator==("love" , answer)    等价于  operator==(String("love") ,answer);

//关于返回对象：
//返回指向const对象的引用   eg：const Vector & Max(const Vector &v1 , const Vector &v2)
//三点：两个形参为const，那么返回值为这两个中的某个时，必须返回const;
//              如果没有&，将调用复制构造函数，但是返回引用不会
//              引用指向的对象，应该在调用函数执行时存在

//返回指向非const对象的引用
//重载<<  和>> 时 必须返回ostream或者istream的&，和库里的接轨

//返回对象
//重载+法时，两个被加的数应该在其中保持不变，所以const，但是需要一个局部变量
//因此不能使用引用返回它，因为局部变量在函数执行完毕调用析构，但是引用则不会，控制权回到调用函数时，他就不存在了

//返回const对象
//像上面的+法，返回非const的就可以： c = a+b;   a +b = c ;     cout<<(a+b).cont()
//如果是const那只有第一个可形

#endif