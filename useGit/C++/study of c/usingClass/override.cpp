//重载运算符在很多时候很有用，而且很符合oop思想
#include "/home/shenheng/c1/study of c/usingClass/myTime.cpp"
#include <iostream>
#include <fstream>

//友元出现的原因：total = coding * 6.2; 等价于total = coding.operator*(6.2); 
//但是coding和6.2的位置不能被改变
//两种解决办法：一是告诉每个人遵守这种格式，第二种就是非成员函数，显式的调用两个参数


int main(){
    using std::cout;
    using std::endl;

    Time plan;
    Time coding(2,40);
    Time fixing(5,55);

    cout<<"Plan Time is :";
    plan.show();
    cout<<'\n';
    cout<<"coding Time is :" ;
    coding.show();
    cout<<'\n';
    cout<<"Fixing Time is :";
    fixing.show();
    cout<<'\n';

    Time total = coding+fixing;
    cout<<"The total Time is : ";
    total.show();
    cout<<'\n';

    total = coding * 6.2;
    //total = coding.operator*(6.2); 等价
    cout<<"The * is:";
    total.show();
    cout<<'\n';

    total = coding - fixing;
    cout<<"the - is :";
    total.show();
    cout<<'\n';

    cout<<"Now we use the cout : " <<total;

    std::ofstream fout;
    fout.open("test.txt");
    fout<<"由于ofstream对ostream的继承，我们也可以直接输入文件里 :"<<total;
    fout.clear();
    fout.close();

}

