#include <iostream>
using namespace std;

unsigned int c_int_str(const char * str, char ch);


int main(){
    //C风格字符串：
    char ghost[15] = "glloping";
    //char * str = "glumphing"; 或者这个，但是c11后不能用了

}

unsigned int c_int_str(const char * str, char ch){
    unsigned int count = 0;

    while (*str)
    //这么用是因为，c风格字符串最后一个是空值字符
    {
        if(*str == ch)
            count++;

        str++;//每一次的位置向后偏移一个char位
    }
    return count;
    
}