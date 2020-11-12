//模板类的局限：比如对于T为结构时，<符号不成立
//解决方法：1、显示具体化   2、重载运算符

//对于一个函数名，可以有非模板函数、模板函数、具体化函数以及其重载
//具体化优先于常规模板，非模板优先于这二者

#include<iostream>

//void swap(T &a, T &b );
struct job
{
    char name[40];
    double salary;
    int floor;
};


template < typename T>
void Swap(T &a , T &b );

template<> void Swap<job>(job &j1 , job &j2);

void show (job &j);

/**注意！！！！！！！！！！
 * 在代码中含有函数模板本身并不会生成函数定义，它只是一个用于生成函数定义的方案
 * 编译器使用模板为特定类型生成函数定义时，得到的时模板实例（instantiation）‘
 * 比如Swap模板并非函数定义，但使用int的模板实例时函数定义
 * 这也被称为隐式实例化
 * c++也允许显示实例化
*/

/**警告！！！！
 * 在同一个文件或者转换单元中使用显示实例化和具体化会出错
 * template void Swap<int>(int , int)          和具体化的差别在于template后没有<>
*/

int main()
{
    using namespace std;

    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield); //科学计数法
    int i = 10, j =20;
    cout<< " i : "<< i << " , and j is "<< j<< ".\n"   ;
    cout<< "using the generated int swap : \n";
    Swap( i , j);
    cout<< " i : "<< i << " , and j is "<< j<< ".\n"   ;


    job si = {"sisi" , 19000.21 , 7};
    job qian = { "shiqian", 17000.21 , 8};
    cout<< " Before swaping :\n ";
    show(si);
    show(qian);
    Swap(si,qian);

    cout<< " After swapping : \n";
    show(si);
    show(qian);


}


template < typename T>
void Swap(T &a , T &b )
{
    T temp;
    a = temp;
    a = b;
    b = temp;

}

template<> void Swap<job>(job &j1 , job &j2)//交换job结构里的除name外的
{
    double t1;
    int t2;

    t1 = j1.salary;
    j1.salary = j2.salary;
    j2.salary = t1;

    t2 = j1.floor;
    j1.floor = j2.floor;
    j2.floor = t2;
}

void show (job &j)
{
    using namespace std;
    cout<<j.name << " : $"<<j.salary
            <<" on floor "<<j.floor<<endl;
}