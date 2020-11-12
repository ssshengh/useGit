#include<iostream>

using namespace std;

int main() {

    cout<<"1234567890\n";//字符串，显示在一个宽度等于字符串长度的字段中

    char16_t  k = 'k';
    int t = 273;
    cout<<k<<":\n";
    cout<<t<<":\n";
    cout<<-t<<":\n";

    cout<<"set to hex mod\n";
    cout<<t<<"            "<<"(decimal)\n";
    cout<<hex<<t<<"             "<<"(hexadecimal)\n";
    cout<<oct<<t<<"              "<<"(octal)\n";

    //c++不会截断数据！！！！
    //设置函数setf() 可以去查具体方法
    cout.setf(ios::ios_base::showbase);//显示基数前缀
    cout.fill('*');//改变填充
    cout.width(10);//对第一个拓宽
    cout<<hex<<t<<" :now the hexadecimal is"<<endl;
    
    //最好用的是集成了setf的标准控制符
    cout.width(20);
    cout<<left<<hex<<t<<" let us see see\n";

    

    return 0;
}