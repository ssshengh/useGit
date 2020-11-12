#include "/home/shenheng/c1/study of c/代码重用/数组模板实例和非类型参数/arraytp.h"

//模板的多功能性：模板可以用作基类也可以用作组件类，还可以用作其他模板的类型参数
//即可以用数组模板实现栈模板（可以继承也可以包含   ），可以用数组模板来构造数组
#include<iostream>

int main(){
    arraytp<int , 10> sums;
    arraytp< arraytp<int , 5> , 10> twodee;//相当于十个数组，每个大小为5的数组，排列顺序是10*5而不是5*10

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            twodee[i][j] = j;
            std::cout << twodee[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}