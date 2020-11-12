#include <iostream>
#include "/home/shenheng/c1/study of c/basicClass/stock00.h"


Stock::Stock()
{
    company = "No name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string & co , long n , double pr)
{
    company = co;
    if(n<0)
    {
        std::cout<<"Number of shares can't be negative; "
                    <<company<<" shares set to 0 . \n";
        shares = 0;

    }//防止公司的股票为负数
    else    
        shares = n;
    share_val = pr;
    setTol();
}


Stock::~Stock(){
    std::cout << "Fucking memory is deleted~ "<< "Bye~~"<<company<<'\n';
}

void Stock::acquire(const std::string & co , long n , double pr )
{
    company = co;//可以通过公有函数方文私有内容
    if(n<0)
    {
        std::cout<<"Number of shares can't be negative; "
                    <<company<<" shares set to 0 . \n";
        shares = 0;

    }//防止公司的股票为负数
    else    
        shares = n;
    
    share_val = pr;
    setTol();
}


void Stock::buy(long num , double price)
{
    if(num<0)
    {
        std::cout<<"Number of shares purchased can't be negative ;"
                <<"Transaction is aborted .\n";
        
    }
    else
    {
        shares += num;
        share_val = price;
        setTol();
    }
    
}

void Stock::sell(long num , double price)
{
    using std::cout;
    if(num < 0){
        cout<< "Number of shares sold can't be negative."
                <<" Transaction is aborded. \n";
    }
    else if(num > shares){
        cout<<"You can not sell the shares more than you have !"
                <<"Transaction is aborted . \n";
    }
    else{
        shares -= num;
        share_val = price;
        setTol();
    }
}

void Stock::update(double price)
{
    share_val = price;
    setTol();

}

void  Stock::show () const
{
    using std::cout;
    using std::ios_base;

    ios_base::fmtflags orig = cout.setf(ios_base::fixed , ios_base::floatfield);//设置科学计数法和定点计数法，并将其标记赋值给orig
    std::streamsize prec = cout.precision(3);//注意这些赋值方法


    std::cout<<"Company:"<<company
                    <<" Shares: "<<shares<<'\n'
                    <<" Share price: $"<<share_val
                    <<" Total worth: $"<<total_val<<".\n";

    cout.setf(orig,ios_base::floatfield)   ;
    cout.precision(prec);
}


 const Stock & Stock::topval(const Stock &s) const
 {
    
     if(s.total_val > total_val)
        return s;
    else
        return *this;
 }