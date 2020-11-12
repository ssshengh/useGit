#include "/home/shenheng/c1/study of c/类继承/继承中的动态内存分配/dma.cpp"
#include <iostream>

int main ()        {
    baseDma shirt ("popora" , 8);
    lacksDma ballon ("red" , "biLiwang" , 4);
    hasDma map ("Mecra" , "buffKey" , 5);

    std::cout <<shirt << '\n';
    std::cout <<ballon << '\n';
    std::cout <<map << '\n';

    std::cout << "尝试一下复制构造函数 "<<'\n';
    lacksDma ballon1(ballon);
    std::cout <<ballon1<<'\n';

    std::cout <<"尝试一下赋值符号" <<'\n';
    hasDma map2;
    map2 = map;
    std::cout <<map2<<'\n';

    std::cout <<"将派生类赋值给基类对象，调用运算符左边类型所对应的赋值运算符，即基类的赋值运算符号"<<'\n';
    shirt = map;
    std::cout <<shirt<<'\n';//可以看到，调用了基类的赋值运算符，因为基类的赋值函数参数中，引用的是基类对象可以使得继承类对象向上转换，因此就忽略了继承类的特有数据
    //相反的操作不被允许，除非有一个函数：lacksDma(const baseDma &)

    //同样的，转换构造函数也可以接受一个类型为基类的参数和其他参数，条件是其他参数有默认值：BrassPlus(const Brass & ba , double ml = 500 , double r = 0.1);
    //BrassPlus & BrassPlus :: operator = (const Brass &){   }

}