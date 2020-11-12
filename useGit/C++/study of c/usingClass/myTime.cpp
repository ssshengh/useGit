#include "/home/shenheng/c1/study of c/usingClass/mytime1.h"
#include <iostream>


    Time::Time()
    {
        hours = minutes = 0;
    }

    Time::Time(int h , int m ){//不用写出来m=0
        hours = h;
        minutes = m;
    }

    void Time::addMim(int m){
        minutes += m;
        hours += minutes/60;
        minutes = minutes%60;
    }

    void Time::addHour(int h){
        hours += h;
        if(hours > 12)
            hours -= 12;
    }

    void Time::Reset(int h , int m){
        hours = h;
        minutes = m;
    }


    Time Time::operator+(const Time & t ) const {
        Time sum;
        sum.minutes = minutes+t.minutes;
        sum.hours = hours + t.hours + sum.minutes/60;
        sum.minutes %= 60;
        if(sum.hours >12)   
            sum.hours -= 12;
        
        return sum;
    }

    void Time::show() const{
        std::cout << hours << "Hours ,"<<minutes << " minutes.";
    }

    Time Time::operator-(const Time & t) const
    {
        Time diff;
        int tol1 , tol2;
        tol1 = t.minutes + 60*t.hours;
        tol2 = minutes + 60*hours;
        diff.minutes = (tol1 + tol2) % 60;
        diff.hours = (tol1 + tol2) / 60;
        return diff ;
    }

    Time Time::operator*(double d) const{

        Time Result;
        long totalMin = hours*d*60 + minutes * 60;
        Result.hours = totalMin /60;
        Result.minutes = totalMin % 60;
        return Result;
    }

    Time operator*(double m ,  const Time & t){
        //注意，在定义函数的时候，就不用time::了，它并不算是类中的函数
        /*****
        Time Result;
        long totalMin = t.hours*d*60 + t.minutes * 60;
        Result.hours = totalMin /60;
        Result.minutes = totalMin % 60;
        return Result;
        ***/
       return t*m;//这是最好的办法，将友元变成了非友元了，完成了对数据的封闭
        //经常用于使用不想让重载的运算符第一个为那个默认的对象
    }

    // void operator<<(std::ostream &os , const Time & t){
    //     os<< t.hours << "Hours , "<< t.minutes << " Mins" <<'\n';
    // }
    //这种就不太行，虽然它的确实现了，能够cout<<Time，但是并不能完成cout<<Time<<"aaaa"
    //这里也可以看出乐<<的本质，其实是一个ostream对象调用了.operator<<()函数
    //我们应该使用cout本身而不是其值的拷贝，因此使用引用

    Time::~Time(){
        std::cout<<"Bye Bye~~~~~~~~~~"<<std::endl;
    }

    
    std::ostream & operator<<(std::ostream &os , const Time & t){
        os<<t.hours << " Hours," <<t.minutes<< " Mins. ";
        return os;
    }