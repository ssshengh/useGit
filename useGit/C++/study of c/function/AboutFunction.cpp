#include <iostream>

using namespace std;

/**
 * C++的函数，返回值可以是除了数组外的所有：整形、浮点数、指针，甚至结构或者对象！
 * 但是不能是数组，不过nb''的是！！！ 可以把数组作为结构或对象的组成部分返回
 * 
*/

/**
 * 函数原型，必须的东西，可以帮助编译器检查输入参数的类型
 * 输入的参数最好是被定义了类型的，防止被进行参数转化
 * 
*/
void n_char(char , int);
int sum_arr(int[] , int);
//将数组传递的潜在含义是，讲数组的地址、元素种类传递给了函数。而传递值的时候，传递的是一个值的拷贝，这个区别很大！！！！！！！！！！！
//因为这意味着在函数内部可能会修改数组，为解决这个问题，可以定义位 const int arr[]      其意义在于在函数内部不能修改数组
int sum_arr(const int * begin , const int * end);


int main(){

    int times ;
    char ch;

    cout<<"Please enter a character :";
    cin>>ch;
    //不用cin.get(ch) 或者是ch = cin.get()来一个个的读入，因为这两个会把空格和换行符也读入
    while (ch != 'q')
    {
        cout<<"Please enter an integer: ";
        cin>> times;

        n_char(ch,times);

        cout<<"\nPlease enter another character or press the "
                        "q-key to end";

        cin>>ch;
    }

    cout<<"the value of times is : "<<times<<endl;
    cout<<"buy\n";

    
    //函数调用
    const int ArSize = 8;
    int cookies[ArSize] = {1,2,4,6,7,8,125,64};
    int sum = sum_arr(cookies,cookies+ArSize);
    int sum1 = sum_arr(cookies+3,cookies+ArSize);

    return 0;
}

//将外部的参数（实参）传递给函数的形参（参量）
void n_char (char c , int n){
    while (n-- >0)
    {
        cout<< c;
    }
    
}

//int arr[] 等价于 int* ar  当且仅当在函数头里二者相同，因为外面的话，无法用数组来声明指针，而且&一个数组是数组整个内存的地址，+1会+很多，指向数组的指针则只加一个元素的地址
//约定是，函数中指向一个数组用前者，指向一个值的位置用后者
//此外，对于两种定义，arr[3] & ar[3]都是访问第四个元素
//arr[i] == *(ar+i)
//&arr[i] == ar+i            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!记住这两个恒等式
int sum_arr(int arr[],int n){
    int total = 0;
    cout<<sizeof(arr)<<"是函数里的传入的数组的大小，可以看出，其只是一个指针的大小，而不是整个数组的大小"<<endl;
    for (int i = 0; i < n; i++)
    {
        total += arr[i];        

    }
    return total;
}//用另一个参数来传递数组的大小，不要用int arr[size]


/**
 * 使用首尾指针来操作数组计算其大小！！！
 * 
 * 
*/
int sum_arr(const int * begin , const int * end){
    //注意顺序，end-begin是个整数值，代表了数组大小
    const int * pt;

    int total = 0;
    for (pt = begin; pt != end; pt++)//注意这里！！
    {
        total = total + *pt;
    }
    

}