#include <iostream>
#include "/home/shenheng/c1/study of c/nameSpace/nameSP.h"

//这个文件提供头文件里的函数原型对应的定义
//由于在名称空间中定义的函数名的作用域在整个名称空间，因此定义和申明必须在同一个名称空间中
//我们通过导入头文件，导入名称空间，然后将两个定义添加进入名称空间中

namespace pers
{
    using std::cout;
    using std::cin;
    //这个被称为using申明，另一个是using编译，他们的主要的区别在于：using编译如果导入了一个在函数中申明过的名称，那么这个文件的局部
    //变量将会隐藏空间名，就像隐藏全局变量一样，而using申明不会
    //因此，建议使用前者以及解析运算符::

    void getPerson(Person & p)
    {
        cout<< "Enter the first name :";
        cin>>p.fname;
        cout<<"Enter the last name :";
        cin>>p.lname;
    }

    void showPerson(const Person & p)
    {
        std::cout<<p.lname<<p.fname;

    }
} // namespace per


namespace  debts
{
    void getDebt(Debt & d)
    {
        getPerson(d.name);//定义的时候将pers namespaces导入了，在后面定义函数的时候可以直接用！！！！
        std::cout<<"Enter a debet :";
        std::cin>>d.amount;
    }
    void showDebt(const Debt & d)
    {
        showPerson(d.name);
        std::cout<<" : $"<<d.amount<<std::endl;
        
    }

    double sumDebts(const Debt ar[] , int n)
    {
        double total = 0;
        for(int i = 0 ; i<n ; i++)
            total+= ar[i].amount;
        return total;
    }
} // namespace 
