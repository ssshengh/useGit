#include <iostream>
#include <fstream>
#include<cstring>
#include<cstdlib>   //for exit()

//追加文件，打开app与out模式
const char * file = "data.txt";

int
main()
{
    using namespace std;

    char ch;//show initial  contents

    ifstream fin;
    fin.open(file);

    //读取现有的文件里的内容
    if (fin.is_open())
    {
        cout<<"Here are the current contents of the "
                <<file<<" file:\n";
        while(fin.get(ch))
            cout<<ch;
        fin.close();
    }
    

    //add new names
    ofstream fout(file,ios::out | ios::app);
    //out打开文件以便写入，app追加到文件尾
    if (!fout.is_open())
    {
        cerr<<"can't open "<<file<<" file for output. \n";
        exit(EXIT_FAILURE);
    }
    cout<<"Enter guest names (enter a blank line to quit) : \n";
    string name;
    while (getline(cin,name) && name.size()>0)//注意这种getlin方法，第一个参数可以为istream
    {
        fout<<name<<endl;
    }
    fout.close();

    //show revised file
    fin.clear();
    fin.open(file);
    if(fin.is_open())
    {
        cout<<"Here are the new contents of the "
                <<file<<" file:\n";
        while(fin.get(ch))
            cout<<ch;
        fin.close();
    }
    cout<<"Done. \n";




}