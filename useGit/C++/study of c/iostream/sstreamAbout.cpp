#include <iostream>
#include<sstream>
#include<string>

using namespace std;
//内核格式化
int main(){

    ostringstream outstr;
    //string msg = outstr.str() 会冻结该msg，使得无法写入
    //可以通过这个来读入string对象中的格式化信息
    string hdisk;
    cout<<" Enter the name of your hard disk:";
    getline(cin,hdisk);
    int cap;
    cout<<" Enter its capacity in GB: ";
    cin>>cap;

    outstr<<" The hard disk :"<<hdisk<<" has a capasity of "<<cap<<" GB.\n";//把这些string数据存入了outstr
    string result = outstr.str();//把存入的数据冻结在result中
    cout<<result;


    string love = "Hengheng love sisi so much in everyday !";
    istringstream instr(love);//将一个istringstream对象与string关联起来
    string word;
    while (instr>>word)
    {
        cout<<word<<endl;
    }//可以一串字符一串字符的读入
    
}