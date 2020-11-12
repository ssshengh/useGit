#include <iostream>
#include <string>
#include <new>

using namespace std;
const int BUF = 512;

class JustTesting
{
private:
    string words;
    int number;
public:
    JustTesting(const string & s = "Just Testing" , int n =0)
    {
        words = s;
        number = n;
        cout << words << " Constructed\n";
    }
    ~JustTesting(){cout << words << " 成功啦！\n";}
    void show() const { cout<< words << " , "<<number<<endl; }
};

int main(){
    char * buffer = new char[BUF];
    JustTesting * pc1,  * pc2;

    pc1 = new (buffer) JustTesting;//定位new
    pc2 = new JustTesting("思思大可爱" ,20);

    cout<<"内存块地址是从这开始的,"<<"buffer："<<(void *)buffer<<"            而堆在："<<pc2<<endl;
    cout<<"内存中内容,注意一个在堆中\n";
    cout<<pc1 <<" :  ";
    pc1->show();
    cout<<pc2<<" : ";
    pc2->show();

    std::cout <<'\n';
    JustTesting *pc3, *pc4;
    pc3 = new (buffer) JustTesting("bad idea" , 6);
    //(buffer + sizeof(JustTesting))
    pc4 = new JustTesting("横横爱思思", 20);
    cout<<"内存中内容,注意一个在堆中\n";
    cout<<pc3 <<" :  ";
    pc3->show();
    cout<<pc4<<" : ";
    pc4->show();

    pc3->~JustTesting();
    pc4->~JustTesting();
    delete pc2;
    delete pc4;
    delete [] buffer;
//和之前的教训一样，在利用定位new的时候，程序员应该负责管理在缓冲区中使用的内存地址，要使用两个不同的单元，必须是两个不同的地址
//如果是使用new来为对象分配地址，一定要确保被delete，就算是定位new，但是形式却不一样
//虽然这里delete [] buffer也带走了这块内存，但是是二者一起被带走的


}