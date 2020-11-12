#include <iostream>
#include<cstring>


using namespace std;
/***
 * * 使用new创建结构数组
 *      在运行时传键数组优于在编译时创造数组，对结构也一样
*/
struct  inflatable
{
    char name[20];
    float volum;
    double price;
};

    



/**
 * 
 * 可能最关键的一点就是下面ps那个
 * 当它指向一个char数组的时候，直接调用他时得到一个字符串
 * 但是用&调用他得到的是数组的地址
 * 用(int *)强制转换后，得到的是指针的地址
*/

//警告：在将字符串读入程序时，应该是使用一个已经被分配的内存地址：new过的指针，或者是数组名！！！！！！！！！！！！！！
//警告！！！！ 应该使用strcpy或者strncpy，而不是赋值运算符来将字符串赋值给数组
int main(){

        //指针使用结构体
    inflatable * pa = new inflatable;
    cout<<"Please enter the name in to the struct pointed by pa " << endl;
    cin.get(pa->name,20);//看如何输入进结构体
    cout<<"Please enter the volume in to the struct pointed by pa " << endl;
    cin>> (*pa).volum;
    //cin.get(pa->volum);//看如何输入进结构体
    cout<<"Please enter the price in to the struct pointed by pa " << endl;
    cin>>pa->price;//看如何输入进结构体

    cout<<"the name is "<< pa->name<<endl;
    cout<<"the valum is " << (*pa).volum << endl;
    cout << "price is " << pa->price<<endl;
    delete pa;

    char animal [20] = "bear";
    const char * bird = "wren";
    //c++无法保证字符串wren被唯一的存储，如果程序中存在多个wern的话，可能会存在多个副本
    //而把bird 令为const的优点是，无论如何bird所指向的位置内的内容都不能被改变，它是唯一一个指向这个wern的副本

    char *ps;

    //cin << ps  很愚蠢的操作，并没有初始化ps，输入的话就不知道具体应该存在哪个位置

    cout<< "the location of animal [] is :" << &animal<<endl
            <<"the meaing of animal is :"<< animal<<endl;
    cout<<endl << "the location of bird is :" << &bird <<endl;
    cout<<"the meaing of bird is : "<< bird<< endl; //这个提醒我们，我们可以通过指针直接得到字符串，而其地址需要利用转换才能（int*）得到
    //指针当作数组来用了。

    cout<<endl<<"please enter animal which length less than 20: "<<endl;
    cin>> animal;
    ps = animal;//这种操作才是对的，不能直接cin进ps

    cout<<"now the pointer ps which point to animal[] is :"<<ps<<endl;
    cout<<"where is the ps?"<<endl;
    cout<< "the location of int is the location of pointer of ps: "<<&ps<<endl;  //ps -------> animal[0]  
    cout<<"the location of char is the location of animals :"<<(int *) ps<<endl;
    //char类型的指针得到的就是字符串的内容，若要看字符串的位置，需要将其转变为另一种类型的pointer
    

    //要获得字符串的副本，必须先分配内存：申明一个数组或者new一个指针
    cout<<endl<<"animal is "<<animal<<"bedore using syrcpy the location of ps is :"<<(int *)ps<<endl;
    cout<<"ps is "<<ps<<"bedore using syrcpy the location of aniaml is :"<<(int *)animal<<endl;
    //注意！！！ 这儿的位置是一样的，因为ps指向animal


    ps = new char [strlen(animal)+1];//输入的字符串未必能够填满所有预留的内存，所以求取字符串长度，new一个合适的内存
    strcpy(ps , animal);//把输入的animal直接赋值给ps是不行的，只是改变了ps指向的地址，失去了访问新分配地址的机会

    cout<<"the contents after strcpy is :"<< ps<<endl;
    cout<<endl<<"animal is "<<animal<<"after using syrcpy the location of ps is :"<<(int *)ps<<endl;
    cout<<"ps is "<<ps<<"after using syrcpy the location of aniaml is :"<<(int *)animal<<endl;
    //注意！！！ 但是这儿的位置不一样，因为是把animal拷贝过去到了ps，而ps的位置重新被new过了
    //这儿就多了两个副本！！！！！                      
    delete ps;



    return  0;
}