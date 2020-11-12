#include <iostream>

using namespace std;

int main(){

    //注意，常量指针未必指向的值是一个常量，只是说对于指针来说它是常量
    int age = 28;
    const int * pToAge = &age;
    age  = 30;
    //*pToAge = 30    wrong!!

    //l另一个微妙的问题：
    int age1 = 30;
    pToAge = &age1;
    //我们是不能修改pToage指向的内存块内的值，但我们可以修改指向的内存块
    //但！！！！ 仍然不能使用pToAge来修改它指向的值，现在是30

    int n = 10;
    const int * ps = &n; //a pointer to const int
    int * const finger = &n; //a const pointer to int    这种是指针内存储的地址也不唔唔修改
    //finger和*ps是const       
    //但是*finger 和 ps 不是


    


    //可以把const变量地址赋值给const指针，但不能赋值给常规指针
    const int num = 100;
    const int * pToNum  = &num;
    //int * P = &num        wrong!
    //const指针也不应该赋值给非const指针


}