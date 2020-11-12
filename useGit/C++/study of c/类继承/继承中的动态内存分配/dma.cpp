#include "/home/shenheng/c1/study of c/类继承/继承中的动态内存分配/dma.h"
#include <string>
#include <cstring>

baseDma::baseDma(const char * l , int r){
    lable = new char [std::strlen(l) + 1];
    std::strcpy(lable , l);
    rating = r;
}

//常规复制构造函数：重新分配空间
baseDma::baseDma(const baseDma & rs){
    lable = new char [std::strlen(rs.lable) + 1];
    std::strcpy(lable , rs.lable);
    rating = rs.rating;
}

baseDma::~baseDma()
{
    delete []   lable;
}

baseDma & baseDma::operator=(const baseDma & rs){
    if(this == &rs)
        return *this;
    
    delete [] lable;
    lable = new char [std::strlen(rs.lable) + 1];
    std::strcpy(lable , rs.lable);
    rating = rs.rating;
    return * this;
} 

std::ostream & operator<<(std::ostream & os , const baseDma & rs){
    os << "Lable : "<< rs.lable << std::endl;
    os << "Rating : "<< rs.rating<<std::endl;
    return os;
}

//未使用动态分配内存的类
lacksDma::lacksDma(const char * c ,  const char * l , int r  ) : baseDma(l ,r){
    std::strncpy (color , c , 39);
    color[39] = '\0';
}

lacksDma :: lacksDma(const char * c ,const baseDma & rs) : baseDma(rs){
    std::strncpy(color , c , COL_LEN - 1);
    color [COL_LEN-1 ] = '\0';

}

std::ostream & operator<<( std::ostream & os , const lacksDma & ls ){
    os << (const baseDma & ) ls ;
    os << "Color is :" << ls .color << std::endl;
    return os;
}

//使用了动态内存分配
hasDma::hasDma(const char * s ,  const char * l  , int r )
                    :baseDma(l ,r)
{   
    style = new char [std::strlen(s) + 1];
    std::strcpy(style , s);
}

hasDma::hasDma(const char * s , const baseDma & rs)
                    :baseDma(rs)
{
    style = new char [std::strlen(s) + 1];
    std::strcpy(style , s);
}

hasDma::hasDma(const hasDma& rs)
                    :baseDma(rs)//调用基类复制构造函数处理共享的基类数据，注意，这里传入的是继承类对象，因为基类的指针和引用可以指向继承类对象向上转换
{
    style = new char [std::strlen(rs.style) + 1];
    std::strcpy(style , rs.style);    
}

//析构函数只用处理自己的部分
hasDma::~hasDma()
{
    delete [] style;
}

hasDma & hasDma::operator=(const hasDma & rs){
    if(this == &rs)
        return *this;
    
    baseDma::operator=(rs);//使用基类的赋值运算符处理基类的部分数据
    delete [] style;
    style = new char [std::strlen(rs.style) + 1];
    std::strcpy(style , rs.style);

    return * this;    
}  

std::ostream & operator<<(std::ostream & os ,const hasDma & hs)
{
    os << (baseDma & ) hs ;
    os << "Style :" << hs.style<<std::endl;
    return os;
}
//这个重载的运算符只能够访问自己的数据成员，那如何访问基类的rating和lable呢？
//答案是在里面调用基类的友元即可
//因为友元不是基类的函数，因此不能用地址限制符取选择调用哪一个的运算符，所以使用强制转换