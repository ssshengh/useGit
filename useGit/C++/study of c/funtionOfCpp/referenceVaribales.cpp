#include <iostream>

/**
 * 不能对voide类型定义引用：int z ;    void &ea = z;
 * 不能对数组定义引用： int a[3];       int &a = a;
 * 不能定义类型的引用：int &ra = int
*/

void swapv (int a , int b);
void swapp(int * p , int * q);
void swapv (int a , int b);

//使用引用传递进函数的时候应该尽可能使用const，可以避免无意修改了变量，使得函数可以处理const或者非const的，或者能够引导函数正确生成使用临时变量
//引用最大的用处可能就是用于结构 和类 这些东西 这也是为什么它诞生
int main() {
    using namespace std;
    //引用不是指针！！！！不能直接对堆进行引用！！
    //int &p  =  new int(2)非法
    int * pp1 = new int(202);
    int & ppp = *pp1;//可以这么用，把引用指向指针指的数据
    int *& ppp2 = pp1;//或者这么指向指针的引用

    cout<<"pp1 地址为"<<pp1<<endl;



    using namespace std;
    int rats = 101;
    int & rodents = rats;   //就相当于  int * const pr = &rats
    //现在的&不再是取地址，而是引用符号，使得rats 和 rodents 可以互换，指向相同的值和内存单元
    //这意味着如果rodents++ 将有两个元素改变
    rodents ++;
    cout<<"After ++ the value of rats is "<< rats<<endl;
    cout<< "now the value of rodents is "<<rodents<<endl;
    cout << "and now the both location is " << &rats << " ...."<< &rodents<<endl;

    int * prats = &rats;
    //现在，rodents 和 *part 还有rats可以互换   同样的 &rats == &rodents == prats
    //所以引用看起来很像指针，事实上，不是，首先它必须先被赋值，还有很多差别
    //就算后面给他再赋值一个int变量，他也会带着rats一起改变

    return 0;
}


/**
 * 引用的一大用处是为了传递给函数————按引用传递
 * 和按值传递最大的区别是：按值传递在函数内调用的形参新创建了一个调用的实参的拷贝，而引用是直接使用这个实参
 * 下面有三种方法访问原始数据：指针、引用和一种不太合适的办法
*/
//交换两个数的值
void swapr(int &a , int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swapp(int * p , int * q)
{
    int temp ;
    temp = *p;
    *p = *q;
    *q = temp;

}

//值传递，很不合适，外面定义的用来换的两个数是不会被换的
void swapv (int a , int b)
{
    int temp ;
    temp = a;
    a = b;
    b =temp;
}