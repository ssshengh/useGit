#include <iostream>
#include<cstring>

//通过函数原型设置默认参数，在大部分时候使用那个参数而偶尔使用其他的时候很有效

char * left(const char * str , int n =1);
// 希望返回一个新的字符串，所以函数头是char*
//希望原始字符串不变，所以使用const
//n 默认为1

const int ARR_SIZE = 80;
int main(){

    char * stt;
    char str[ARR_SIZE] ;
    std::string * s1;
    std::string  sisi= "sisi";
    //stt = &sisi; string不能赋值给一个char指针
    s1 = &sisi;



    return 0;
}