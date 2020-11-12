#include <iostream>
#include<fstream>
#include<cstdlib>   //for exit()

//执行的时候就将编译后的文件作为命令使用就可以了,编译一个a.out
//a.out  data1.txt data.txt

int main(int argc, char * argv[]){
//argc：命令行中参数个数，包含命令本身
//argv：指向一个指向cahr的指针。是一个指针数组，其中的指针指向命令行参数，argv[0]是一个指针，指向存储第一个命令行参数的字符串的第一个字符
//eg:   wc report report1 report2
//则argc = 4， argv[0] = wc      argv[1] = report1

    using namespace std;

    for (int i = 0; i < argc; i++)
    {
        std::cout<<argv[i]<<endl;
    }//逐行打印命令行参数

    if(argc == 1 )
    {
        cerr<<"Usage: "<<argv[0]<<" filename[s]\n";//错误消息是第一个，a.out data.txt data1.txt 的话会是a.out
        exit(EXIT_FAILURE);
    }

    ifstream fin;
    long count;
    long total = 0;
    char ch;

    for (int file = 0; file < argc; file++)
    {
        fin.open(argv[file]);//把流连到argv[file]上
        if (!fin.is_open())
        {
                cerr<<"could not open "<<argv[file]<<endl;
                fin.clear();
                continue;
        }
        count = 0;
        while(fin.get(ch))
            count++;//计算里面的字符

        cout<<count<<" characters in"<<argv[file]<<endl;
        total+=count;
        fin.clear();          //使用clear是无害的，在不必要的时候也可以使用
        fin.close();        //断开流
        

    }
    cout<<total<<" character in all file \n";
    return 0;


}
