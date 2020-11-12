#include <iostream>
using namespace std;

int main(){

    short s = 2^9+2^3+2;
    cout<<s<<"***********"<<endl;
    int i = 5;
    float f = i;
    cout<<"f is"<<f<<"*****"<<endl;
    printf("%f",f);
    

    int i1= 37;
    float f1 = *(float*)&i1;
    cout<< f1<<endl;
    cout<<"***";
    cout<<"wagesb"<<endl;

    string str;
    (cin>>str).get();
    return 0;
}