#include "/home/shenheng/c1/study of c/类和动态内存分配/StringBad.cpp"
#include <iostream>

void callMe1(StringBad & rsb){
    std::cout <<"String passed by reference :\n";
    std::cout <<"           \""<<rsb<<"\" \n";
}
void callMe2(StringBad sb){
    std::cout <<"String passed by value : \n";
    std::cout <<"          \""<<sb<<"\" \n";
}

int main(){
    {
        std::cout <<"在一个代码块中开始：\n";
        StringBad headline1("午夜的风雨交加");
        StringBad headline2("中午的明媚阳光");
        StringBad sports("一起打球吧！！");
        std::cout <<"headline1 is :"<<headline1<<'\n';
        std::cout <<"headline2 is :"<<headline2<<'\n';
        std::cout <<"sports is :"<<sports<<'\n';

        //到这里，代码看起来还是很正常
        callMe1(headline1);
        std::cout <<"headline1 is :" <<headline1<<'\n';
        //第一个严重问题出现了，这里我们按值传递了headline2，可以从结果看见析构函数被调用了，而且还调用了复制构造函数初始化其形参
        callMe2(headline2);
        //因此这里就不再有headline2了,因此，虽然按值传递可以避免原始参数被修改，但是函数使得字符串无法被时别，在下面也就出现了一些非标准的字符
        std::cout <<"headline2 is : "<<headline2<<'\n';

        //问题出现了
        std::cout <<"将sports赋值给另一个对象\n";
        //这里调用了一个隐藏的函数：StringBad (const StringBad &)   因此下面这一句等效于：sailor = StringBad(sports)
        StringBad sailor = sports;//由于隐藏的复制构造函数按照值传递，因此等价于sailor.str = sports.str
        //第二个关键，这里只是把str的地址传递了过去！！！
        //所以delete[]的时候，其释放了指向str的内存，所以在释放knot和sailor的时候，其是已经把headline1和so=ports的内存释放了
        //我们释放了两次内存，有的系统上会程序终止

        std::cout <<"sailor is :"<<sailor<<'\n';
        std::cout <<"Assign one object to another :\n";
        StringBad knot ;
        std::cout <<"the default knot is :"<<knot<<'\n';
        //这里调用了一个隐藏的默认赋值运算符
        knot = headline1;//这种又不同于上一种，headline1还被复制了knot，析构的时候是c++
        std::cout <<"我们把knot用headline1赋值，后面的析构也出现了问题，现在的knot是："<<knot<<'\n';
        std::cout <<"end block\n"; 

        //析构的调用和创建是反过来的，可以通过它，还有计数器的结果来查看问题
        //正常来说，计数器是每一次构造加1，析构减1，但是出现了-2的值，这说明了，我们没有利用构造函数的创建了两个对象！！！

    }

    //这里不是为了str私有变量分配内存，而是为了对象分配，在对象的内存里又分给私有变量
    //但是并不给晶态变量，因为静态变量同一存在一个地方
    StringBad * stt = new StringBad("sisi大笨蛋！！");
    stt->HowMany();
    std::cout<<*stt;
    delete stt;//需要手动delete，才会调用析构
}

//笔记：
//c++类中提供了默认构造函数，但有可能具有二义性：
//klunk(){ct = 0}
//klunk(int n = o){ct = n}这就有了二义性，因为由默认值的构造函数等同于默认构造函数

//复制构造函数，关键在于知道它的存在，在创建一个对象并用另一个对象复制给他的时候调用,也就是说，只要存在创建了一个对象的副本，就会调用
//且！！！！上面的按值传递对象的callMe2也调用了复制构造函数，因此我们应该尽可能的按引用传递，来避免时间和空间的上的花销
// StringBad ditto(old);
// StringBad metoo = old;
// StringBad also = StringBad(old);
//这三个都是调用了默认复制构造函数，但是！！！！！注意，默认的调用复制的是非静态成员的，复制的是成员的值！！！
//注意，如果成员本身就是类对象，那么将使用这个类的复制构造函数来复制成员对象，但静态函数并不受到影响，因为他们属于整个类
// StringBad * ptoS = new StringBad(old);
//StringBad(const StringBad &)

//赋值运算符
//功能：将一个已有的对象赋值给另一个对象的时候，使用重载的赋值运算符。注意区分上面的两个，第一个是复制构造函数，第二个是赋值运算符
//问题就在于，数据受损：和复制构造函数一样，他也是将str的地址复制了过去