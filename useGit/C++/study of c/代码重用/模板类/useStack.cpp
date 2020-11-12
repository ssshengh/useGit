#include "/home/shenheng/c1/study of c/代码重用/模板类/stacktp.h"
#include<iostream>
#include<string>
#include<cctype>
#include <cstdlib>  //rand()  srand()
#include<ctime>   //for time()

const int num = 10;

/**
 * 实现的场景是：Plodson有一车文件
 *                                  如果收取篮空，则把文件中最上面一个放入收取篮
 *                                  如果——是满，则取出收取篮中最上面的文件，放入发出篮
 *                                  如果既不空也不满，那就50%概率取出车中的下一个文件放入收取篮，或者处理收取篮最上面的文件放入发出篮
*/


int main(){
    //在这里是几个错误使用指针栈的示例，揭示了，设计模板的教训，不要盲目使用模板

    // stacktp<char *> st;//但现在的版本，就直接不能通过编译，

    // char * po;//char po[40]  或者 char * po = new char [40]一样的会失败
    // std::cin >> po; //程序崩溃，因为仅仅创建了指针，没有创建用于保存输入字符串的空间
    // st.push(po);
    // std::cout <<po;
   
    std::srand(std::time(0));//随机话rand
    std::cout <<"Please enter stack size : ";
    int stackSize;
    std::cin >> stackSize;

    std::cout <<"Test rand()%2: "<< std::rand()%2<<std::endl;
    std::cout <<"rand%2 (bool) :"<<bool(std::rand() % 2)<<std::endl;//要么0要么1
    //创建一个空栈，收取篮
    stacktp<const char * > st(stackSize);

    //总文件,指针数组，存储了十个文件的地址，这些地址的类型是char* 所以可以压入栈
    const char * in[num] = {
        "1: Hand GIGI " , "2: KiKi sama" , "3: BiBi Rocker " , "4: DiDi Ishtar ",
        "5: Wolf KK" , "6: Prof Kob" , "7: JIJI lal" , "8: Sisi My Love" , "9: HengHeng SiSi love", "10: Nisa Macj" 
    };

    //发出篮，存储文件数量和总文件数一致
    const char * out[num];

    int processed = 0;//从收取篮中取出的文件
    int nextIn = 0 ;
    while (processed < num)
    {
        if(st.isEmpty())
            st.push(in[nextIn++]);//先push再加加
        else if(st.isFull())
            st.pop(out[processed++]);
        else if(std::rand() % 2 && nextIn <num)   //50-50的概率
            st.push(in[nextIn++]);
        else
            st.pop(out[processed++]);

    }

    for(int i = 0 ; i < num ; i++)
        std::cout <<out[i]<<std::endl;
    
    
    

}