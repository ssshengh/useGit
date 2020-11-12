#include <iostream>
#include "/home/shenheng/c1/study of c/nameSpace/hFile/coordin.h"
#include "/home/shenheng/c1/study of c/nameSpace/originCode/fillOfFunction.cpp"
#include  <cmath>

using namespace std;

/**
 * 这两个都是静态变量，不同的是，第一个可以在其他文件中调用（外部链接型），后一个只有在本文件中使用，内部链接性
 * x,db,pi在开始的时候就被零初始化，不管程序是否显式的零初始化了它
 * 接下来，才进行正常初始化
 * 但要初始化pi必须等到atan函数被链接时且程序执行时
*/
int x = 0;//也可以在头文件中定义
static double db = 10.88;
const double  pi = 4.0*atan(1.0);



/**
 * 引用申明外部变量，并不分配储存空间，关键词extern
 * c++中变量只能有一次定义，因此可以定义申明也可以引用申明
*/
extern double waring;//不是常量，时可以被改变的
//const int aa = 100;在使用头文件包含进来之后，aa的作用域就是这些文件的所有了，只有一个文件可以有其申明，而其他文件只能有引用
extern const int aa ;

int main(){
    rect rplace;
    polar pplace;

    cout<< " Enter the x and y values :";
    while (cin>>rplace.x>>rplace.y)
    {
        pplace = rectToPolar(rplace );
        showPolar(pplace);
        cout << "next to numbers is : (q to quit)";
    }

    cout<< waring<<endl;
    cout<<" Bye~ \n";
}