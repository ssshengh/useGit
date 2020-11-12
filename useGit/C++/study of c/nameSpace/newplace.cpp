#include<new>
#include<iostream>

const int BUF = 512;
//默认全局变量的链接性是外部的，但const的全局变量是内部的
const int N = 5;
char buffer[BUF];

int main(){
    using namespace std;

    double *pd1, *pd2;
    int i;

    cout<<"Calling new and placement new : \n";
    pd1 = new double[N];//正常的new
    pd2 = new (buffer) double[N];//定位new运算符,确实将数组pd2放入了buffer中，然而他们类型不同，pd2是double，buffer是char指针
    for(i = 0; i< N ; i++)
        pd2[i] = pd1[i] = 1000+20.0*i;
    
    cout<< "Memory adresses: \n" << " heap: "<<pd1  //获取堆中的pd1的地址
            <<"   static: "<< (void* )buffer <<endl;     //获取数组的地址
    cout<<"Memory contents : \n";

    for ( i = 0; i < N; i++)
    {
        cout<<pd1[i]<<" at "<<&pd1[i]<< " ; ";
        cout<<pd2[i]<<" at "<<&pd2[i]<<endl;
    }
    


    cout<<"\nCalling new and placement new a second time : \n";
    double *pd3, *pd4;
    pd3 = new double[N];//正常的new
    pd4 = new (buffer) double[N];//定位new运算符
    for(i = 0; i< N ; i++)
        pd3[i] = pd4[i] = 1000+40.0*i;
    cout<<"Memory contents : \n";

    for ( i = 0; i < N; i++)
    {
        cout<<pd3[i]<<" at "<<&pd3[i]<< " ; ";
        cout<<pd4[i]<<" at "<<&pd4[i]<<endl;
    }
    //这里可以看出，pd3新创建了一个地址存储数据，但是pd4只是接着buffer的初始地址存储数据，哪怕这个地址被pd2用过，它并不检查，这个负担给了程序员


    cout<<"\nCalling new and placement new a third time : \n";
    delete [] pd1;//释放了内存后，重新new，可以看见可以重新使用被释放的内存
    pd1 = new double[N];//正常的new
    pd2 = new (buffer+N*sizeof(double)) double[N];//定位new运算符
    for(i = 0; i< N ; i++)
        pd2[i] = pd1[i] = 1000+60.0*i;
    for ( i = 0; i < N; i++)
    {
        cout<<pd1[i]<<" at "<<&pd1[i]<< " ; ";
        cout<<pd2[i]<<" at "<<&pd2[i]<<endl;
    }
    //这里可以看出，使用了偏移量后，在被存储的区域后继续存储，而没有占用之前用过的区域

    delete  [] pd1;
    delete [] pd3;
    //不能delete定位new，因为定位new本质上指向的时buffer的静态内存块，不在new-delete的管理范围内
}