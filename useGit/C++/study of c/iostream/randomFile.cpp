#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

const int LIM = 20;

struct planet
{
    char name[20];
    double population;
    double g;
};

//get得到的字符只要不为换行符号就一直读取,并且丢弃了换行符号之前的内容，cin.get()可以读取缓冲区
inline void eatline () { while (std::cin.get() != '\n') continue;}
const char *file = "//home//shenheng//c1//dataToread//binary.dat";

int main(){

    using namespace std;


    // fin.seekg(112);//第一个参数类型streampos，是相对于文件开始处的位置，这里就是文件的第113字节
    // fin.seekg(30,ios_base::beg);//文件开始后的第30个字节
    // fin.seekg(-1,ios_base::cur);//上移一个字节
    // fin.seekg(0,ios_base::end);//去到文件末尾 

    planet p1;

    cout<<fixed<<endl;//定点计数法

    //显示文件里原本的内容
    fstream finout;
    finout.open(file, ios_base::in | ios_base::out | ios_base::binary);//读写模式
    //有些系统并不接受binnary类型，比如这个

    int ct = 0;


    if (finout.is_open())
    {   
        finout.seekg(0);//指针指向文件开头
        cout<<"The current context in the file is :"<<'\n';
        //注意读取方法！！

        while (finout.read(((char *)  &p1) , sizeof (p1)))   //结构体也可以使用sizeof，注意前面一定要强制转缓
        {
            cout<<ct++<<" : "<<setw(LIM)<<p1.name<< " : "
                    <<setprecision(0)<<setw(12)<<p1.population
                    <<setprecision(2)<<setw(6)<<p1.g<<endl;
        }

        if(finout.eof())//用eof标志来判断是否达到文件尾部
            finout.clear();//clear eof flag 重置流状态后，可以重新打开eof，就可以再次访问该文件
        else
        {
            cerr<<" Error in reading "<< file << " .\n";
            exit(EXIT_FAILURE);
        }
        

    }
    else
    {
        cerr<< " Can not open file : "<<file<< " . And bye~ \n";
        exit(EXIT_FAILURE);
    }

    //改变记录
    cout<< " Enter the record number you wish to change : ";
    long rec;
    cin >> rec;
    eatline();
    if (rec<0 || rec>=ct)
    {
        cerr<< " Invalid record number. bye~~ ";
        exit(EXIT_FAILURE);
    }
    streampos place = rec* sizeof(p1);//用这个数乘以数据结构长度，可以获取字节位置
    finout.seekg(place);//指针指过来
    if (finout.fail())
    {
        cerr<< " Error on attempted seek \n";
        exit(EXIT_FAILURE);

    }
    
    finout.read( (char*) & p1, sizeof(p1));
    cout<< " Your selection is :\n";
    cout<<rec<<" : " <<setw(LIM) <<p1.name << " : "
            <<setprecision(0)<<setw(12)<<p1.population
            <<setprecision(2)<<setw(6)<<p1.g<<endl;

    if(finout.eof())
        finout.clear();
    
    cout<<"Enter the planet name :";
    cin.get(p1.name,LIM);
    eatline();
    cout<< "Please enter the population is :";
    cin>>p1.population;
    cout<<" Please enter the gravity is :";
    cin>>p1.g;
    eatline();
    
    finout.seekg(place);//指针回到之前的位置
    finout.write( (char*) &p1 , sizeof(p1));
    if (finout.fail())
    {
        cerr<<"Error on attemptede write";
        exit(EXIT_FAILURE);

    }
    

        //显示文件
    ct = 0;
    finout.seekg(0);

    cout << "Here are the new contents of the "<< file<< " file:\n";
    while (finout.read((char*)&p1 , sizeof(p1)))
    {   
        cout<<ct++<<" : "
                <<setw(LIM)<<p1.name<< " : "
                <<setprecision(0)<<setw(12)<<hex<<p1.population
                <<setprecision(2)<<setw(6)<<p1.g<<endl;
        
    }
    finout.close(); 
    cout<< " Done!";

}