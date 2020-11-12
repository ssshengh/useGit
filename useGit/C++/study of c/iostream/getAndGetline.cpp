#include <iostream>

using namespace std;
const int LIMIT = 255;//限制输入字符

int
main(){
    char  input[LIMIT];

    cout<<"please enter a string by cin.getline():"<<endl;
    cin.getline(input,LIMIT,'#');//输入的string，长度，以及分界符
    cout<<"now see the input :"<<input<<endl;

    char ch;
    cin.get(ch);
    cout<<"the next input character is : "<< ch<<'\n';
    //可以看见这里得到的字符其是就是前一个字符串分界符之后的第一个字符，它丢弃了分界符，这是和gerline的主要区别

    if(ch != '\n')
        cin.ignore(LIMIT,'\n');//读取并丢弃直到指定字符，或者文件末尾（默认值EOF）
//把之前输入的全部丢弃
    cout<<"enter a string from cin.get() :"<<'\n';
    cin.get(input , LIMIT ,'#');
    cout<<"now the input is: "<< input<<endl;

    cout<<"*****************"<<'\n';
    cin.get(ch);
    cout<<"the next character is "<<ch<<endl;
    //get没有丢弃分界符，而将#留在了输入流中，在后面被读取了出来

    //get()在不设置的时候，默认遇到换行符号取消输入，如果对输入的东西的格式不对也会返回false
    //这里就是设置流状态检查了
}