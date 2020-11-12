#include <iostream>
#include<cstring>

using namespace std;
//注意关注  ！！！！！！！！！！ 自动存储，静态存储以及动态存储
char * getname(void);
//new 和delete不妨在一起不是一个好的思路，但这个例子说明时可以这么干的
int main(){
    char * name;

    name = getname();
    //创建了一个指针，将指针函数取道的名字所存的地址赋值给他
    //现在的问题是，在函数里new的指针如何清除
    cout<< name <<" at " << (int *)name<<endl;
    delete [] name;//这个括号很关键！！！！！！！！！！函数内部new出来的是带括号的

    name = getname();
    cout<<name << " at "<< (int*) name<< endl;
    delete [] name;

    return 0;

}


/***这个函数主要是要求输入一个数，并将其拷贝到一个指针所指的内存空间里
 * 指针函数，返回一个char* 指针（char类型的指针）
 * 注意看函数里面，最后return的是一个同类型的指针
 * 
*/
char * getname(){
    char temp [80];//这个东西只在运行时函数生命周期里存在，函数结束了就不再存在了----->动态存储
    //这也是为什么要new一个新的指针来存储数据，因为控制权回到main后，main中name指向的地址将很快被其他的东西使用了
    cout<<"Please enter last name :"<<endl;

    cin>>temp;

    char *pn = new char[strlen(temp)+1];
    strcpy(pn, temp);

    return pn;

}