#include <iostream>
#include <vector>
#include<array>
#include <cstring>

using namespace std;

/***
 * vector & array是数组的替代品，是一种动态数组，可以在运行阶段设置二者的长度
 * 可在末尾附加新数据，也可以在中间插入数据
 * 基本上是用new创建数组的替代品，自动完成了new于delete
 * v ector功能强大，但是问题在于付出了效率的代价，如果使用确切大小的数组，还是建议使用数组，但不那么方便和安全
 * 有鉴于此，c++多了一个叫array的数组，长度固定，使用栈存储（静态内存分配  ），而不是动态存储的堆
 * 
*/


int main(){
    vector<int> vi;
    int n ;
    cin >> n;
    vector <double> di(n);//创建储存n个double数据的动态数组
    for (int i = 0; i < di.size(); i++)
    {
        cout<< "Please cin to di []"<<endl;
        cin>>di[i];
    }
    

    for(int i = 0; i< di.size(); i++){
        cout<<"print di:"<<di[i]<<endl;
    }

    array<int,5> ai;
    array<double ,3 > ci = {1.2,2.1,3.4};//3和5的位置不能是变量



    return 0;
}