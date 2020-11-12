#include <iostream>

using namespace std;

int
main(){
    //cin,读取从非空白字符开始，到与目标类型不相同的第一个字符之间的所有内容
    char *ss = new char[20];
    int distance;
    char forever;
    // cin>>ss>>distance>>forever;
    // cout<<ss<<" is in:"<<(long *)ss<<endl;

    int sum = 0;
    int input;

    while (cin>>input)
    {
        sum+=input;
    }
    cout<<"the last input is :"<<input<<endl;
    cout<<"the all input added is "<<sum<<endl;
//输入读入不合理的字符的时候，cin会返回false，比如输入 200，100，-100e，可以看到sum是200

    //如果想要继续读取就需要把刘状态设置位良好‘
    cin.clear();
    //但导致循环终止的不匹配输入仍旧留在了输入队列中，程序必须跳过它，有两种办法
    while (cin.get() != '\n')//丢弃剩余部分
            continue;
    cin>>input;
    // while(!isspace(cin.get()))
    //         continue;                              在参数是空白的时候才返回true



    





    //现在，我们控制流状态来捕获上述的异常
    cin.exceptions(ios_base::failbit);//设置后，下面的cin会将流状态与exception比较，如果这里某一位被设置，而当前cin中的某一位也因为错误输入设置就会抛出异常
    //cin.exceptions(ios_base::badbit | ios_base::eofbit);
    cout<<"enter numbers:"<<endl;
    try
    {
        while(cin >> input){
            sum+=input;
        }
    }
    catch(ios_base::failure & bf)
    {
        cout << bf.what() << '\n';
        cout<<"O! the horror!\n";
    }
    


}