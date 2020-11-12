#include <iostream>
#include<cstring>
using namespace std;

int main()
{
    /*
    数组的定义与处理
    */
    double arrs[4]  {1.2e4 , 1.6e4, 1.8e4};  //c++11 可以这么干
    arrs[3] = 2.08;
    std::cout<<"hello, world"<<std::endl;
    std::cout<<arrs[0] <<"\n"<<arrs[1]<<"\n"<<arrs[3]<<std::endl;
    std::cout<<"***************************************************************************"<<std::endl;

    /*
      字符串
    
     char str1[15];
    std::cin>>str1;
     short size1 = sizeof(str1);
     std::cout<<"数组长度是"<<size1<<"数组里字符串长度是\n"<< strlen(str1) << std::endl;
     std::cout<<"***************************************************************************"<<std::endl;
     */
    //另一种输入方式，按行输入
    short size2 = 20;
    char name[20];
    char grades[size2];
    string wage {"大傻瓜  ！！"};
    
    cout<<"请输入名字:\n"<<endl;
    (cin>>name).get();
    cout<<"请输入成绩:\n"<<endl;
    cin.getline(grades, size2);
    cout<<name<<"同学"<<",你的成绩是："<<grades<<endl;
    cout<<name<<"是个"<<wage<<"\n长度是"<<sizeof(wage)<<endl;
    std::cout<<"***************************************************************************"<<std::endl;


     /*
     结构
     */
    struct percen
    {
        /* data */
        char16_t name[];
        float ID;
        double grade;
    };
    

    return 0;
}
