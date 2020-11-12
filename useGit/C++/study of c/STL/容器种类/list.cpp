#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

void out_int (int n ) { std::cout << n << " ";} 

int main(){
    using namespace std;
    list <int> one(5,2);//5个2

    int stuff[5] = {1,2,3,4,7};
    list<int> two ;
    two.insert(two.begin() , stuff, stuff+5);
    int more [6] = {6,3,4,2,3,54};
    list<int> three ;
    three.insert(three.end() , more , more+6);
    
    cout<<"first :";
    for_each(one.begin() , one.end() , out_int);
    cout<<endl<<"second :";
    for_each(two.begin() , two.end() , out_int);
    cout<<endl<<"third:";
    for_each(three.begin() , three.end(), out_int);

    three.remove(2);
    cout<<endl<<"after remove 2 third:";
    for_each(three.begin() , three.end(), out_int);
    three.splice(three.begin() , one);

    //three.splice(three.begin() , a); wrong 必须是容器才能加进来
    cout<<endl<<"after splips begin third:";
    for_each(three.begin() , three.end(), out_int);

    three.unique();//压缩相同的元素
    cout<<endl<<"after unique begin third:";
    for_each(three.begin() , three.end(), out_int);
    //排序，必须排序后才能合并
    three.sort();
    two.sort();
    three.merge(two);
    cout<<endl<<"after merge begin third:";
    for_each(three.begin() , three.end(), out_int);

}