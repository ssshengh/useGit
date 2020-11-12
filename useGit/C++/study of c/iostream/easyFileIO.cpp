#include<iostream>
#include<fstream>

int
main(){
    using std::cin;
    using std::cout;
    //输出时必须创建一个ofstream对象来管理输出流
    std::ofstream fout,tout; //程序将创建两个缓冲区
    fout.open("//home//shenheng//c1//dataToread//data.txt");//这种方法无法读入路径
    //打开文件
    //由于cout也是一样的ofstream类型，所以对cout所有操作都可以对fout使用并输入文件
    //同样的，流状态检查也可以用于这两个东西，没有消息就是好消息，出现问题就是相应位置置1了


    fout<<"hello sisi !";//默认将文件里面的清空了
    fout.close();
//注意！！！！ 这里并没有删除流，只是断开流，可以接到其他文件上



    //输出时必须创建一个ifstream对象来管理输入流
    std::ifstream fin,tin;
    fin.open("data.txt");
    char ch;
    fin>>ch;
    cout<<ch<<" is ch \n";


    char buf[80];
    //fin>>buf;
    fin.getline(buf,80);
    cout<<buf<<" is the file context"<<std::endl;

    std::string line;
    getline(fin,line);
    cout<<line<<"  string \n";
    //可以看见缓冲区被用完了，最后一个读不出任何数据
    fin.close();
    //就比如这里，fin的缓冲区并没有被删除


}