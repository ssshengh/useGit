#include <iostream>
using namespace std;

    /***
     * delete原则：
     * long * fellow;
     *   *fellow = 232233;
     * 这种是绝对禁止的，因为储存器不知道fellow具体指向什么地址，就会乱指，并解释为储存232233的地址，就会存很多。造成一种难以追踪的bug
     * 原则二：
     *              如果new数组的时候使用了方括号，时方的时候也需要。没有的话，释放的时候不能有
     * 
    */
int main(){
    //* dereferencing   解除引用
    //指针最关键的可能是：在使用的时候，一定要先赋值一个地址

    
    int * pn = new int;//new最关键的地方在于告诉计算机需要准备多少内存
    //pn实际指向一个数据对象（这个对象指一个“东西”），是一块内存块。所以变量也是数据对象，但pn指向的内存不再是变量

    int higgens = 100;
    int * pt = &higgens;
    //和上面的对比一下，下面这个可以用指针pt调用也可以用&higgens调用，但是上面的就只能通过pn调用

    double d1 = 100001.01;
    double * pd = new double;
    *pd = 100001.01;//哪怕数值相同，这两个都存于不同位置
    //这也是为什么要给指针定义类型，器是它只储存了地址的开始，而没有指出其类型
    cout<<"double value is :"<<*pd<<" in the location of "<<pd
                << "in which size of "<<sizeof(pd)<<endl;
    cout <<"the location of same value in d1 is "<<&d1<<" which value is "<<d1<<endl;

    // delete pt;
    // delete pd;

    //一般来说，对于管理小的内存对象不需要用到指针，。但大型数据：数组、string、结构体使用new就更好
    //正常来说，数组创建分为两个
    //静态联编：在编译过程中创建数组，编写时需要指定数组大小
    //动态联编 ：在运行时创建数组，如果需要程序才会给数组分配内存

    double *p3 = new double[3];//p3指向数组第一个元素的位置，可以直接用指针操作数组，这是最关键的
    p3[0] = 0.2;
    p3[1] = 0.3;
    p3[2] = 0.4;

    cout<<"location of p3 is :"<<p3<<endl;
    cout << "p3[1] is: "<<p3[1]<<endl;
    double * LocationOfP3 = &p3[2];
    cout <<"location of p3[2] is : "<<LocationOfP3<<endl<<endl;

    cout<<"lets try to see the different between pointer and dataGroup"<<endl;
    double wage[3] = {100.1 , 200.2 , 3000.3};
    short stacks[3] = {3,2,1};
    double *pToWage = wage;
    short *pToStacks = stacks;
    cout<<"数组名是第一个元素地址"<<&stacks<<endl;

    //注意一个问题，&stacka是一个数组的地址，+1会是加6，而&stacks[1]是第一个元素地址，和前一个一样，但是+1会是+6
    cout<<endl<<"the location of stacks is :" << &stacks<<endl;
    cout<<"the location of stacks[0]+1 is:"<< &stacks[0]+1<<endl;
    cout<<"the location of stack +1 is :"<<&stacks+1<<endl<<endl;

    cout<<"the location of wage is :"<<&wage<<endl; 
    cout<<"`the location of pTowage is:"<<pToWage<<endl;
    pToWage += 1;
    cout<<"move 1 :"<<pToWage<<" and now the location of wage[1] is :"<<&wage[1]<<endl;//可以看出偏移了一个double的位置
    pToStacks +=1 ;
    cout<<"move 1 :"<<pToStacks<<" and now the location of wage[1] is :"<<&stacks[1]<<endl;//可以看出偏移了一个double的位置
    cout<<pToStacks[2]<<endl;//不行
    cout<<*(pToStacks+1)<<endl;//通过+1可以顺着访问，但是没办法利用动态数组的方法访问‘
    cout<<stacks[2]<<endl;

    cout<<endl<<"对数组使用sizeof得到的时数组的长度，对指针使用是得到指针的长度，哪怕指针指向数组"<<endl;
    cout<<sizeof(stacks)<<"是数组的长度，"<<sizeof(pToStacks)<<"是指针的长度，该指针指向第一个数组元素"<<endl;
/***
 * 一般来说不要创建两个指针指向同一个内存块，因为会增加错误释放的风险
 * 但是对于返回函数的指针等，使用另一个指针确实很有道理
*/


    return 0;
}//这个时