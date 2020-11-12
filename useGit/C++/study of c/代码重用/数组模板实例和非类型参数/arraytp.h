#ifndef  ARRAYTP_H_
#define ARRAYTP_H_

#include <iostream>
#include<cstdlib>

//注意T为类型，n是一个int类型的参数，这种参数指定了特殊的类型而不是用作泛型名，就被称作非类型（表达式
//该参数的地址与大小均不可变，可以是整形、枚举、引用或者指针：即double不可以，但是double*可以
//与一般来说的我们使用构造函数分配内存地址来构造函数大小的方法来说
//这个方法能够在使用小型数组的时候提高运行速度，但是会生成许多自己的模板
//此外，构造函数的方法能够方便的将一个尺寸的数组赋值给另一个尺寸的数组，也可以创建数据大小可变的类，更通用
template <class T , int n>
class arraytp
{
private:
    T ar[n];
public:
    arraytp() {}
    explicit arraytp(const T & v );
    virtual T & operator [](int i);
    virtual T operator[](int i) const;
};

template<class T , int n>
arraytp<T , n > ::arraytp(const T & v){
    for (int  i = 0; i < n; i++)
    {
        ar[i] = v;
    }
    
}

template<class T , int n > 
T & arraytp<T , n > ::operator[](int i ){
    if(i<0 || i>=n)
    {
        std::cerr<<"Error in array List : "<< i <<" is out of range. \n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i];
}


template<class T , int n > 
T  arraytp<T , n > ::operator[](int i )  const {
    if(i<0 || i>=n)
    {
        std::cerr<<"Error in array List : "<< i <<" is out of range. \n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i];
}

#endif