#include <iostream>
#include <string>

//可以使用多个类型参数，可以默认类模板参数（但不能默认函数模板参数），但二者都能默认非类型参数的值
template<class T1 , class T2 = int > 
class pairs
{
private:
    T1 a;
    T2 b;
public:
    T1 & first();
    T2 & second();
    T1 first() const {return a;}    
    T2 second() const {return b;}
    pairs(const T1 & aval , const T2 & bval ) : a(aval) , b(bval){}
    pairs(){}
    ~pairs(){std::cout <<"bye bye ~~~~~~~~~~~";}
};

template<class T1 , class T2  >
T1 & pairs<T1 , T2 > ::first()
{
    return a;
}

template<class T1 , class T2 >
T2 & pairs<T1 , T2 > ::second()
{
    return b;
}

int main(){
    using std::string;
    //注意点一：构造函数需要使用pairs<string>来调用
    pairs<std::string , int> rating[4]={
        pairs<string> ("first" , 5),
        pairs<string> ("scend" , 4),
        pairs<string> ("third" , 3),
        pairs<string> ("four" , 2)
    };
    //注意点二：sizeof需要用pairs<string>来传参得到具体的个数，可以看到，分子是整个数组的数组的大小，分母是模板的大小，每个模板的大小一样
    int joins = sizeof(rating)/sizeof(pairs<string>);
    std::cout << "Rating: \t Eatery\n";
    for(int i = 0 ; i < joins ; i++)
        std::cout <<rating[i].second() <<":\t "
                            <<rating[i].first()<<std::endl;
    std::cout <<"Oops! Revised rating: \n";

    //注意点三：通过公有函数，可以访问私有元素，即first返回a，我可以重新给a赋值
    rating[3].first() = "change!";
    rating[3].second() = 33;
    std::cout <<rating[3].second() <<":\t "
                            <<rating[3].first()<<std::endl;

}