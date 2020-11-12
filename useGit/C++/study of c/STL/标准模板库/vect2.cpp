#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct review
{
    std::string title;
    int rating;
};

void ShowReview(const review & re)
{
    std::cout << "可爱思思："<< re.rating << " ~ "<<re.title<<std::endl;
}

void show (const std::vector<review> & rv ){
    std::cout << "存储结构的向量大小为 ："<<rv.size()<<std::endl;
    int size = rv.size() ;
    for(int it = 0 ; it<size ; it++)
    {
        //std::cout << "可爱思思："<< rv[it].rating << " ~ "<<rv[it].title<<std::endl;              //出来会乱码
        ShowReview(rv[it]);//一样的乱码,但是原因不在这里，再之前for中把其压入ector时压进去的就不对
    }
}


//用于排序使用sort
bool WorseThan(const review & r1 , const review & r2 ){
    if(r1.rating>r2.rating)
        return true;
    else
        return false;
}

bool operator<(const review & r1 , const review & r2)
{
    if(r1.title < r2.title)
        return true;
    else if(r1.title == r2.title && r1.rating < r2.rating)
        return true;
    else
        return false;
}

int main(){
    std::vector<std::string>  name= {
        "11a",
        "22b",
        "33c",
        "44d",
        "55e"
    };

    std::string s;
    review rr[int(name.size())];
    int ra = 0;

    std::vector<review> rrv;//注意vector也可以用来存储结构

    for(std::vector<std::string>::iterator it=name.begin() ; it!=name.end() ; it++)
    {
        //把数据压入一个结构数组，也压入一个向量
        std::istringstream isin(*it);
        getline(isin , s);
        rr[ra].title = s;
        rr[ra].rating = ra;

        std::cout <<"s is :" <<s << "*********";
        std::cout <<" OK *** rr[] :"<<rr[ra].title << " : "<<rr[ra].rating<<std::endl;
        rrv.push_back(rr[ra]);//这种才对，因为放在后面ra已经改变了，指向的是结构数组的空空间，随机赋值了
        ra++;
        //rrv.push_back(rr[ra]);//这种压进去的有问题，乱码的
        // review item {s , ra};   //或者这种
        // rrv.push_back(item);
    }
    std::cout << s<<std::endl;//可以看出，最后的s里面只有一个元素,流中前面的元素已经被处理了

    //接下来使用Vector
    std::cout <<"****************接下来使用Vector****************"<<'\n';
    std::cout << "存储结构的向量大小为 ："<<rrv.size()<<std::endl;
    show(rrv);
    int num = rrv.size();

    std::cout <<"****************另一种表示法****************"<<'\n';
    std::vector<review> ::iterator itOfReview;
    for ( itOfReview = rrv.begin(); itOfReview != rrv.end(); itOfReview++)
    {
        ShowReview(*itOfReview);
    }
    std::cout << "这种表示法还可以用for-each替换"<<std::endl;
    //for_each(rrv.begin() , rrv.end() , show()); show 需要能够返回true或false
    
    //拷贝函数调用
    std::vector<review> old_list(rrv);
    std::cout <<"****************插入两个新元素，于末尾****************"<<'\n';
    rrv.insert(rrv.end() , old_list.begin()+2 , old_list.end()-1);//用另一个vector插入
    show(rrv);
    std::cout <<"****************交换vector之后****************"<<'\n';
    rrv.swap(old_list);
    show(rrv);


    std::cout <<"****************排序如何完成？函数对象！****************"<<'\n';
    sort(rrv.begin() , rrv.end() , WorseThan);//worsehan在前一个元素大于第一个的时候返回true,本质上是sort使用时所比较的元素必须存在比较符号
    //所以另一种办法就是重新定义<来使用sort
    show(rrv);
    sort(rrv.begin() , rrv.end());
    show(rrv);

    std::cout <<"****************java版for-each****************"<<'\n';
    double a[6]= {1.02 , 2.13, 3.231 ,4.89 ,89.2 , 12.123 };
    std::vector<double>  price;
    for(double x : a){
        std::cout << x <<" ";
        price.push_back(x);
    }  
    std::cout <<'\n';
    for(auto x : price)
        std::cout << x << " ";
    std::cout << '\n';

    std::cout <<"建议!!! 尽量使用java风格迭代容器或者容器内的for_each方法处理细节"<<std::endl;
}
//迭代器有五种，关键在于，不同的容器的迭代器不一样，不同的迭代器能够使用的操作也有差别，同时也有层次结构，所以需要随时查查那张表