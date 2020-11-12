#include <iostream>
#include<cmath>

using namespace std;

/**
 * 值传递给结构有几个好的地方：可以按照整体作为数据对象来当作基本类型来处理、可以传递地址、还可以按引用传递
 * 
*/

struct travelTime
{
    int hours;
    int mins;
};//这种小的结构体最好就是通过值传递，因为太大的结构体按值传递会消耗很多空间和时间
//用到的全局变量
const int minsPerHour = 60;
//用到的函数有：
travelTime sum(travelTime t1 , travelTime t2);
void showTime(travelTime t);

//直角坐标系
struct  rect
{
    double x;
    double y;

};
//极坐标系
struct  polar
{
    double distance;
    double angle;
};

//使用两个函数来完成直角坐标系转换为极坐标系
void showPolar (polar dapos);//显示极坐标
void showPolar (const polar * pda);//调用结构地址，由于不需要改变地址内的参数，所以使用const
polar rectToPolar (rect xypos);
void rectToPolar ( const rect * pxy , polar * pda);

int main(){

    travelTime day1 = {5,45};
    travelTime day2 = {3,59};

    travelTime trip = sum(day1, day2);
    cout<< "Two days total :";
    showTime(trip);

    rect rplace;
    polar pPlace;

    cout<<"please enter the x and y values :";
    while (cin>>rplace.x>>rplace.y)
    //注意这种istream流的输入方式，根据是否输入成功返还一个bool值
    //它可以输入任何符合要求的字符
    //但若已经输入了，要在循环里重新输入的话，需要先cin.clear()
    {
        // pPlace  = rectToPolar(rplace);
        // showPolar(pPlace);
        // cout << "please enter next two members (q to quit) :";
        rectToPolar(&rplace,&pPlace);
        showPolar(&pPlace);
        cout<<"please enter next two member (q to quit )";
        
    }
    cout<<"done\n";

    


    return 0;
}






travelTime sum(travelTime t1 , travelTime t2){
    travelTime total;

    total.mins = (t1.mins+t2.mins)%minsPerHour;
    total.hours = (t1.mins+t2.mins)+t1.hours+t2.hours;

    return total;
}

void showTime(travelTime t){
    using namespace std;

    cout<<t.hours<<" hours , "<<t.mins<<" minutes\n";
}


void showPolar (polar dapos){
    using namespace std;

    const double    radToDeg = 57.29577951;//180/pi的近似值
    //c++里存储的是弧度值，转化位角度需要乘以180/pi

    cout<<"distance is "<<dapos.distance;
    cout<<", angle = "<<dapos.angle * radToDeg;
    cout<<" degrees \n";

}

void showPolar (const polar * pda) 
{
    using namespace std;

    const double redToDeg = 57.29577951;
    cout<< "distance is : " <<pda->distance;
    cout<< ", angle is : " <<pda->angle;
    cout <<"degrees \n";
}


polar rectToPolar (rect xypos)   {
    polar answer;

    answer .distance = 
                sqrt(xypos.x*xypos.x+xypos.y*xypos.y);
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}

void rectToPolar ( const rect * pxy , polar * pda)
{
    using namespace std ;
    pda->distance = sqrt(pxy->x * pxy->x + pxy->y*pxy->y);
    pda->angle = atan2(pxy->y , pxy->x);
}