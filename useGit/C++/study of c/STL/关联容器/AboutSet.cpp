//C++中的关联容器包含了set、multiset——><set>     还有 map、multimap——><map>
//set的键与值类型相同，键是唯一的，后者一个键可能有多个值，map与之类似，不同之处在于，键和值不一定类型一样
//二者基于树实现

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

int main(){
    using namespace std;
    const int N = 6;
    string s1[N] = {"buffoon", "thinkers" ,"for " , "heavy" , "can" , "for"};
    string s2[N] = {"metal" , "any" , "food" , "elegent" , "deliever" , "for"};

    set<string, less<string>> A(s1 , s1+N);//第二个参数是可选的，用以决定用于排序的方法，默认是less，也就是说，创建了set后就默认排序了
    set<string> B(s2, s2+N);
    
    ostream_iterator<string , char> out(cout , " ");//输出迭代器，允许使用cout来显示信息，第一个参数指出了被发送到输出迭代器的内容，第二个指出了输出流使用的类型
    cout<<"A : ";
    copy(A.begin() , A.end() , out); //可以看见被排序了
    cout<<endl;
    cout<<"B : ";
    copy(B.begin() , B.end() , out);
    cout<<endl;

    cout<<"集合求并：\n";
    set_union(A.begin() , A.end() , B.begin() , B.end(), out);//最后一个参数可以用于输出，理论上可以用第三个参数的迭代器Begin但是不可以，因为是常量迭代器，不是输出迭代器
    cout<<endl;
    cout<<"集合求交：\n";
    set_intersection(A.begin() , A.end(), B.begin() , B.end() , out);
    cout<<endl;
    cout<<"集合求差：\n";
    set_difference(A.begin() , A.end() , B.begin() , B.end() , out);
    cout<<endl;

    set<string> C;
    cout<<"集合运算后插入一个新的set这么干：\n";
    set_union(A.begin() , A.end() , B.begin() , B.end() ,
                            insert_iterator<set<string>> (C , C.begin()));  
    copy(C.begin() , C.end() , out);
    cout<<endl;

    string s3 ("hangry");
    cout<<"插入怎么干：\n";
    C.insert("s3");
    C.insert(s3);
    copy(C.begin() , C.end() , out);
    cout<<endl;
    C.erase("for");
    copy(C.begin() , C.end() , out);

    cout<<"Range : \n";
    copy(C.lower_bound("ghost") , C.upper_bound("spook") , out);
    //前者返回一个迭代器，指向第一个不小于该键的成员，后者返回一个迭代器，返回第一个不大于该键的成员


}