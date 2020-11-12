#ifndef    MYTIME_H_
#define   MYTIME_H_

#include <iostream>

class Time
{
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h , int m =0);
    void addMim(int m);
    void addHour(int h);
    void Reset(int h = 0 , int m =0)  ;
    /**
     * 运算符重载，重载了+，注意！！
     * 返回值为一个Time对象类型，将另一个Time作为参数传递，关键在于其中直接调用private其是调用了一个Time对象
     * @param t : 传入一个Time对象用于计算
    */
    Time operator+(const Time & t) const;
    Time operator-(const Time & t) const;
    Time operator*(double d) const;

    //友元函数的声明必须放在类中，但注意，它其是本质上是一个外部函数，只不过可以访问内部变量
    //因为这一点，友元已经身在了类之中被其控制，所以，并不违背OOP思想
    //最好不要定义上面那个*号了，因为会出现二义性，最好就选择一个
    friend Time operator*(double m, const Time & t) ;

    //<<运算符实际上被重载过多次很了，因为cout可以及其智能的时别各种类型的数据，并将其合适的输出，所以，对于我们的这个变量，我们也可以将其重载
    //这个也是友元最常用的方式
    //friend void operator<<(std::ostream &os , const Time & t);

    //更合适的办法，原理就是：cout<<x<<y   ==  (cout<<x)<<y
    friend std::ostream & operator<<(std::ostream &os , const Time & t);

    void show() const;

    ~Time();

};


#endif 
