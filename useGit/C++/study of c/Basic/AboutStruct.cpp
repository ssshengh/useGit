#include <iostream>
using namespace std;

struct fun
{
    /* data */
    int num;
    int denom;
    float money;
    string name;
};

struct inflatable
{
    /* data */
    char name[20];
    float volum;
    double price;

};//结构体同时含有以上的类型

union  uni
{
    /* data */
    int int_val;
    long long_val;
    double double_val;
};//共用体是，只能同时存在一种类型，为int就不能为double，因此存储为最大类型的存储长度

struct aboutYear
{
    int year;
};


int main(){


    fun pi = {22,7,360.87,"sisi"};//结构体内存的分配是，遵守大小为其中最大的基本数据类型的整数倍
    ((fun*)&(pi.denom))->num = 12;
    ((fun*)&(pi.denom))->denom = 33;
    cout<<"now pi.denom is:"<<pi.denom<<"....and emmm now pi.num is:"<<pi.num<<endl;

    //即使是数组，也能够成员赋值
    fun f1 = pi;
    bool  b1 = (f1.denom == pi.denom);
    cout<<"是否相等："<<b1<<endl;


    cout<<"测试含数组的结构的结构数组"<<endl;
    inflatable in[10];
    in[0] = {};//赋值为空，全部位上为0
    cout<< "空赋值时情况:"<<in[0].name[0]<<"为其数组情况："<<in[0].price<<in[0].volum<<endl;

    //指针数组结构体的创建
    aboutYear s01 , s02 ,s03;
    s01 = {10};
    s02 = {100};
    s03 = {101};

    aboutYear *arp[3] = {&s01,&s02,&s03};//arp是一个指针数组，那里面的元素全是指针，那我按照正常数组调用，就是在使用指针
    cout<<"使用指针数组，就按照普通数组来用，但是里面存的指针就可以了"<<endl;
    cout<<arp[1] ->year<<endl;
    aboutYear **ppa = arp;//不用&了，arp本身就是一个地址
    //既然是个数组，那么我也可以用一个指针指向它的第一个元素
    cout<<"使用指针数组的指针"<<endl;
    cout<<(*ppa)->year<<endl;
    //!!!!!!!!!!!!!!!!!!注意 括号必不可少，因为*ppa ->year 其实是将*用于ppa->year 这会导致错误
    cout<<(*ppa +1 )->year<<endl;
}