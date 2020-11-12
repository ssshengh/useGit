#include <iostream>
#include<string>
#include <sstream>

int main(){
    using namespace std;
    //七种构造函数使用范例：
    string one("sisi daKeAi!!");
    std::cout << one <<endl;
    string two(20 , '#');   
    std::cout << two << endl;
    string three (one);
    std::cout <<three <<endl;
    string four;
    four = two + three;
    std::cout <<four<<endl;
    char all[] = "All's well that ends well";
    string five(all , 20);
    std::cout << five<<endl;
    string six(all+6 , all +10);//两个指针之间的数据,因为
    std::cout << six<<endl;
    string seven (&five[6] , &five[10]);//对象名不同于数组名，不会被看为一个地址，因此five不是指针，five+6没有意义，但是five[6]是一个char，使用&可以取出地址
    std::cout << seven <<endl;
    one+='!' ;
    std::cout << one<<endl;

    istringstream isin (five);
    
    string s;


    while (isin >>s)
    {
        std::cout << s <<endl;
        long r = atol(s.c_str());
        std::cout << s.c_str()<<endl;
    }
    
    std::cout << "***************************************\n"<<"string输入"<<endl;
    //c风格字符串三种方式：char info[100] ;     cin>>info;     cin.getline(info);         cin.get(info , 100);
    string sstuff;
    std::cin >>sstuff;
    cout.fill('&');
    std::cout << "sstuff is :" <<sstuff <<endl;
    getline(cin , sstuff);//流里面的东西已经进去了，就空了，所以后面输入的是沙都没有,但是一次输入的只是空格外的东西,这里的输入不以空格为界
    std::cout << "sstuff is :" <<sstuff <<endl;
    string sstuff1;
    getline(cin , sstuff1 , '%');//设置边界,因为对于c风格字符串，其读取函数是istream类型方法，但是string的是个独立的函数，所以，对前者，cin是调用者，对后者是参数
    std::cout << "sstuff1 is :" <<sstuff1 <<endl;


    std::cout <<"****************************************\n"<<"接下来看看如何增大字符串"<<endl;
    string empty;
    string small = "bit";
    string larger = "Elephants are a girls best friends ";
    cout<<"Size:\n";
    std::cout <<"\tempty :"<<empty.size()<<endl;
    std::cout <<"\tsmall :"<<small.size()<<endl;
    std::cout <<"\tlarger: "<<larger.size()<<endl;
    cout<<"Capacity:\n";
    std::cout <<"\tempty :"<<empty.capacity()<<endl;
    std::cout <<"\tsmall :"<<small.capacity()<<endl;
    std::cout <<"\tlarger: "<<larger.capacity()<<endl;
    empty.reserve(50);
    std::cout <<"\tempty :"<<empty.capacity()<<endl;
}