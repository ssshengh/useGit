#include <iostream>
#include<cstring>
using namespace std;

int main()
{
    double value1 = 1000;
    cout<<&value1<<endl;
    cout<<"************************"<<endl;

    double *p_value;
    p_value = &value1;
    cout<<*p_value<<"位于："<<p_value<<endl;

    /**成对用*/
    double * p3 = new double [3];
    p3[0] = 0.2;
    p3[1] = 0.4;
    p3[2] = 0.6;
    cout<<"p3[1] is"<<p3[1]<<endl;
    p3 = p3 +1 ;
    cout<<"now p3 [0] is"<<p3[0]<<"and p3[1] is";
    cout<<p3[1]<<endl;
    p3 = p3 -1;  //指针指回去   因为加减是移位，增加或减少指向类型的字节数
    delete [] p3;

    char chr ='A';
    int i = chr;
    cout<<"0000000000000000000000000000"<<endl;
    cout<< chr<<i<<endl;

    cout<<"========";

    return 0;
}
