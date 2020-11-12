#include <iostream>
#include "/home/shenheng/c1/study of c/basicClass/stock00.cpp"

//使用对象时的内存分配：每个对象有自己的一块内存，其中有自己的内部变量和类成员
//但是，所有对象的方法共享一个内存块，只是传递不同的数据
const int STK = 4;

int main(){
    {
    Stock company1 ;
    company1.acquire("SisiLimited",1000,18.9);
    company1.show();
    company1.buy(100,20);
    // //能够影响到里面的cout
    // std::cout.setf(std::ios_base::fixed);
    // std::cout.precision(3);
    company1.show();
    company1.sell(300 , 17.8);
    company1.show();

    const Stock company2  {"abcd",800,11};//列表初始化
    company2.show();

    //Stock company2 = new Stock("abcd", 800, 11);没有指针构造函数，这个是错误的
    company1 = Stock("HengHeng", 1000 , 1.8);//没有一个重载的指针构造函数，重新赋值不能使用new动态存储
    //重新赋值后，内存被释放,有趣的是，在赋值后才调用的析构函数
    company1.show();
    }

    Stock com[STK] ={
        Stock(),//默认构造函数
        Stock("Shanghai", 8000,10),
        Stock("Nono",1902,10.2),
        Stock("HE",900,11)
    };
    com[0].show();
    com[1].show();
    com[2].show();
    com[3].show();

}