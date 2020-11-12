#include "/home/shenheng/c1/study of c/类和动态内存分配/StringBad.h"
#include <cstring>
//8够好的类

//静态成员初始化！！！！！不能在类声明中初始化，因为声明只是描述了如何分配内存，但并不实际分配
//但有一个例外，静态数据类型为整形或者枚举型的const
int StringBad::num_strings = 0;

StringBad::StringBad (const char * ch)  {
    len = std::strlen(ch);//获取长度
    str = new char[len + 1];//注意，在这里为对象分配的内存地址
    std::strcpy(str , ch);
    num_strings++;
    std::cout <<num_strings<<"号string：\""<<str  
                    <<"\" 对象被创建\n";
}

//默认构造创建为C++字符串
StringBad::StringBad ()  {
    // len =4;//获取长度
    // str = new char[4];//注意，在这里为对象分配的内存地址
    // std::strcpy(str , "C++");
    // num_strings++;

    //改为简单的～
    num_strings++;
    len = 0;
    str = new char[1];
    str[0] = '\0';

    std::cout <<num_strings<<"号string："<<str  
                    <<"\" 对象被创建\n";
}

//默认复制函数
StringBad::StringBad(const StringBad & st){
    num_strings++;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str,st.str);
    std::cout <<num_strings<<"号string："<<str  
                    <<"\" 对象被创建\n";
}

//默认赋值函数
StringBad & StringBad::operator=(const StringBad & st){
    if(&st == this)//注意，st不是一个指针
        return *this;
    delete [] str;//如果是赋值给自己，那就走不出上一部，如果地址一样，那这一步把地址释放出来
    len = st.len;
    str = new char[len+1];
    std::strcpy(str , st.str);
    num_strings ++;

    std::cout <<num_strings<<"号string："<<str  
                    <<"\" 对象被创建\n";
    return *this;


}

StringBad & StringBad::operator=(const char * ch){
    delete [] str;
    len = std::strlen(ch);
    str = new char[len+1];
    std::strcpy(str , ch);
    std::cout <<++num_strings<<"号string："<<str  
                    <<"\" 对象被创建\n";

    return *this;

}


StringBad::~StringBad(){
    std::cout <<"\""<<str<<"\" 对象被释放,";
    num_strings--;
    std::cout <<num_strings<<"个对象剩余\n";
    delete [] str;//关键来了，在这里释放每个对象使用的内存空间,而且声明中使用了[],所以这里也要有
}

std::ostream & operator<<(std::ostream & os , const StringBad & st){

    os<<st.str;
    return os;
}



//新加的函数
//作为友元便于我们用常规字符串和对象作比较
bool operator<(const StringBad & s1, const StringBad & s2){
    return (std::strcmp(s1.str,s2.str)<0);
} 
bool operator>(const StringBad & s1, const StringBad & s2){
    return s2<s1;
}
bool operator==(const StringBad & s1, const StringBad & s2){
    return (std::strcmp(s1.str , s2.str) == 0);
}


char & StringBad::operator [] (int i){
    return str[i];
}
const char & StringBad::operator [] (int i) const{
    return str[i];
}

std::istream & operator>>(std::istream & s1,  StringBad & s2){
    char temp [StringBad::CINLIM];
    s1.get(temp , StringBad::CINLIM);
    if(s1)
        s2 = temp;
    while(s1 && s1.get() != '\n')
        continue;
    return s1;
}