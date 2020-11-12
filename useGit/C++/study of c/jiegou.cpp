#include <iostream>
#include<cstring>
using namespace std;

struct percen
{
    /* data */
    char name[20];
    float ID;
    double grade;
};

int main()
{
    percen pp = {
        "ren yi",
        521799,
        89

    };
    
    cout<<pp.name<<"身份是\n"<<pp.ID<<"\n成绩是"<<pp.grade<<endl;
    cout<<"***************************"<<endl;

    //结构数组
    percen ppp[2] = 
    {
            {"shenheng", 100084,91},
            {"renyi", 521799,90}
    };
    cout<<ppp[0].name<<"身份是\n"<<ppp[1].ID<<"\n成绩是"<<ppp[0].grade<<endl;
    cout<<"***************************"<<endl;


/*枚举*/
enum color {red, green,blue,black,wihte};
color co = red;
cout<<co<<endl;
cout<<"*******************************"<<endl;




    return 0;
}