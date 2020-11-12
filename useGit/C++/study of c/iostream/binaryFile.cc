#include<iostream>
#include<fstream>
#include<iomanip>
//三个常用方法：setw()设置宽度             setprecision()设置精度           setfill()设置填充
#include<cstdlib>

//文本格式是，将所有内容存储为字符   <<这个运算符所干的事情
//二进制格式是，存为字符的ASCII码表示

//文本格式便于读取，可以使用编辑其或者文字处理器来处理，可以方便的将文本从一个计算机系统传到另一个计算机系统
//二进制对于数字来说很精确，不会有转换误差和舍入误差，以二进制格式保存数据的速度更快

struct planet
{
    char name[20];
    double population;
    double g;
};

//get得到的字符只要不为换行符号就一直读取,并且丢弃了换行符号之前的内容，cin.get()可以读取缓冲区
inline void eatline () { while (std::cin.get() != '\n') continue;}

const char *file = "//home//shenheng//c1//dataToread//binary.dat";

using namespace std;
int 
main()
{
    planet p1;
    cout<<fixed<<endl;//定点计数法

    //显示文件里原本的内容
    ifstream fin;
    fin.open(file,ios_base::in  | ios::binary);// | ios_base::binary
    //有些系统并不接受binnary类型

    if (fin.is_open())
    {
        cout<<"The current context in the file is :"<<'\n';
        //注意读取方法！！
        while (fin.read(((char *)  &p1) , sizeof (p1)))   //结构体也可以使用sizeof，注意前面一定要强制转缓
        {
            cout<<setw(20)<<p1.name<< " : "
                    <<setprecision(0)<<setw(12)<<p1.population
                    <<setprecision(2)<<setw(6)<<p1.g<<endl;
        }
        fin.close();

    }
    

    //输入新的内容
    ofstream fout;
    fout.open(file,ios_base::out | ios_base::app  | ios::binary);// | ios_base::binary

    if(!fout.is_open())
    {
        cerr<< " cant't open the : " <<file <<" for output\n";
        exit(EXIT_FAILURE);
    }

    cout<<"Please enter planet name (enter a blank line to quit) : \n";
    cin.get(p1.name,20);//get不跳过空白
    while (p1.name[0] != '\0')
    {
        eatline();
        cout<< "Please enter the population is :";
        cin>>p1.population;
        cout<<" Please enter the gravity is :";
        cin>>p1.g;
        eatline();

        fout.write((char*)&file , sizeof(p1));
        cout<< " Please enter planet name (enter a blank line to quit): \n";
        cin.get(p1.name,20);
    }
    fout.close();


    //显示文件
    fin.clear();//别忘了clear一下
    fin.open(file, ios_base::in);// | ios_base::binary
    if(fin.is_open())
    {
        cout << "Here are the new contents of the "<< file<< " file:\n";
        while (fin.read((char*)&p1 , sizeof(p1)))
        {   
            cout<<setw(20)<<p1.name<< " : "
                    <<setprecision(0)<<setw(12)<<hex<<p1.population
                    <<setprecision(2)<<setw(6)<<p1.g<<endl;
            
        }
        fin.close();
    }

    cout<<" Its OK!";
    return 0;
}