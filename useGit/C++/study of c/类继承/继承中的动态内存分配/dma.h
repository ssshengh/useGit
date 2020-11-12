#ifndef  DMA_H_
#define DMA_H_

/**
 * 在继承中，使用new造成的动态内存分配的结果，主要有两种情况
 * 第一种是派生类不使用new：这种情况下不需要重新显示定义析构、赋值、复制。因为默认的这三个会调用基类的这三个来处理属于基类的内容，因此我们在里面使用string时不用考虑内存释放的问题
 * 第二种是派生类使用new：这种的析构、复制构造函数以及赋值运算符均需要特定的方法定义，最主要的思路在于如何如何区分派分类里面属于基类的部分
*/

#include <iostream>

class baseDma
{
private:
    char *lable;//基类使用动态分配内存
    int rating;

public:
    baseDma(const char * l = "null" , int r = 0 );
    baseDma(const baseDma & rs);
    virtual ~baseDma();
    baseDma & operator=(const baseDma & rs);
    friend std::ostream & operator<<(std::ostream & os , const baseDma & rs);

};

//没有使用动态内存分配
class lacksDma : public baseDma
{
private:
    enum{ COL_LEN = 40};
    char color[COL_LEN];
public:
    lacksDma(const char * c = "blank" ,  const char * l = "null" , int r = 0 );
    lacksDma(const char * c ,const baseDma & rs);
    
    //甚至可以不用定义析构函数

    friend std::ostream & operator<<(std::ostream & os , const lacksDma & ls);
};

//使用了动态内存分配
class hasDma : public baseDma
{
private:
    char * style;
public:
    hasDma(const char * s = "none" ,  const char * l = "null" , int r = 0);
    hasDma(const char * s , const baseDma & rs);

    //显式定义复制构造函数
    //hasDma只能访问自己的数据，必须调用baseDma的复制构造函数来处理共享的baseDma数据
    hasDma (const hasDma & rs);

    //显式定义析构函数
    //派生类析构函数，自动调用基类的析构函数，因此其应该关注于清理派生类构造函数分配的空间。依赖于baseDma的析构函数释放label的空间
    ~hasDma();

    //显示定义赋值符号
    //作为hasDma的方法，它只能访问hasDma的数据
    //然而，派生类的显式赋值必须负责所继承的baseDma的基类对象的赋值，可以显式调用基类赋值运算符完成
    hasDma & operator=(const hasDma & rs);

    //三个同名的友元处理
    friend std::ostream & operator<<(std::ostream & os , const hasDma & hs);
};


#endif

