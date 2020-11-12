#include <iostream>
using namespace std;

struct fun
{
    /* data */
    int num;
    int denom;
};


int main(){ 

    cout<<endl;
    fun pi;
    pi.num = 22;
    pi.denom =17;
    ((fun*)&(pi.denom))->num = 12;
    cout<<((fun*)&(pi.denom))->num<<endl;
    cout<<((fun*)&(pi.denom))->denom<<endl;
    ((fun*)&(pi.denom))->denom = 33;
    cout<<((fun*)&(pi.denom))->denom<<endl;
    cout<<sizeof(pi)<<"is the size of pi"<<endl;//结构体的内存大小应该是8字节，两个int，所以pi.denom的位置应该是第5字节
    cout<<"the location of num is:"<<&pi.num<<"...and the location of denom is :"<<&pi.denom<<endl;
    cout<<"now pi.denom is:"<<pi.denom<<"....and emmm now pi.num is:"<<pi.num<<endl;

    char ch = 'A';
    short s = ch;
    printf("%d",s);

    //无符号的如下，有符号的，短变长是正数高位补0，负数高位补1，长变短截去高位 
    cout<<"低位转高位,按位复制，高位补0"<<endl;
    short s1 = 29+23+20;
    int i = s1;
    printf("%d",i);
    cout<<endl; 

    cout<<"长转短，截取高位变成0"<<endl;
    int i1 = 223+221+26+20;
    short s2 = i;
    printf("%d",s2);
    cout << endl;

    // 操作内存
    int ii = 37;
    float ff = *(float*)&ii;  //&取地址，（）内强制转换地址为float*类型，再把这个地址变成float输出其中的值
    cout<<"数值"<<ii<<"地址"<<ff<<endl;

    double du = 3.1416;
    char ch1 = *(char*)&du;
    cout << "数值"<<du<<"char类型地址"<<ch1<<endl;
    short s3 = *(short*)&du;
    cout << "数值"<<du<<"char类型地址"<<s3<<endl;
    double du2 = *(double*)&du;
    cout << "数值"<<du<<"char类型地址"<<du2<<endl;

    cout<<endl;


 cout<<"1111111111111111"<<endl;
    //指针在内存中的布局
    int x = 5;
    int *p1 = &x;
    int* *p = &p1; //指向指针的指针
    //double **q = &p1; 报错，指向int的指针的指针应该也是int指针类型
    int ***w = &p;
    cout<<"The data of x is:"<<x<<".The location of x is p1 :"<<p1<<". The location of p1 is p :"<<p<<".The location of p is w: "<<w<<endl; 
    delete p1;
    cout<<"The location of x (p1) is null after deleting"<<p1<<endl;
    
    int arr[5];
    arr[3] = 128;
    ((short*)arr)[6]    = 2;
    cout << "aa"<<arr[3]<<endl;
    cout<<"1111111111111111"<<endl;
    

}