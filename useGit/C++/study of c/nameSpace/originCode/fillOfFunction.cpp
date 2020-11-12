#include <iostream>
#include "/home/shenheng/c1/study of c/nameSpace/hFile/coordin.h"
#include<cmath>

using namespace std;

/**
 * 由于单定义原则，在这里重新定义waring时错误的
 * double   waring = 0.8    wrong!!!
*/
//static double waring = 0.8;//但可以通过内部链接性的satic变量进行定义，其作用域在本文件里，会屏蔽那个全局链接的变量
//不过导入了文件之后似乎不行,因为导入了文件其实，他们就是一个文件了，违反了单定义

int disk = 100;

polar rectToPolar (rect xypos)
{
    polar answer;

    answer.distance = sqrt( xypos.x * xypos.x + xypos.y * xypos.y);
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}

void showPolar(polar dapos)
{
   const double RtoD = 57.27577951;
    cout<<waring<<endl;
    cout<<"distance = "<<dapos.distance;
    cout<<", angle = "<<dapos.angle * RtoD;
    cout<<" degress . \n";
}

