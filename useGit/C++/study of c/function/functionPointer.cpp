#include <iostream>

double betsy(int lns);
double pam (int lns);
void estimate(int lines , double  (*pf)(int));


//(*pf)和函数名pf等价
int main()
{
    //double (*pf)(int);//声明一个函数指针，意味着pf指向一个参量位int，返回值为double的函数
    //double  *pf(int)    由括号优先级较高决定了这个是返回指针的函数，而上面是函数指针

    //process (think )   process 函数调用函数think()
    //process(think())  process 函数调用函数think()的返回值
 
    using namespace std;
    int code;

    cout<< " How many lines of code do you need? ";
    cin>>code;
    cout<<"Here's Betsy estimate : \n";
    estimate(code,pam);
 
    return 0;
}

double betsy(int lns)
{
    return 0.05*lns;

}

double pam (int lns)
{
    return  0.3*lns+0.004*lns*lns;
}

/**调用函数的好处在于，可以统一的利用estimate函数计算时间
* 其他人只需要写自己的pam或者betsy，就可以扔进来计算时间
*/
void estimate(int lines , double (*pf)(int))
{
    using namespace std;
    cout<<lines << " lines will take ";
    cout << (*pf)(lines) <<" hours \n";
}