#include "/home/shenheng/c1/study of c/类继承/类继承/类继承基本概念及注意点/tableTenn0.h"
#include <iostream>

tableTennisPlayer :: tableTennisPlayer(
    const string & fn  , 
    const string & ln ,
    bool ht ): firstName(fn) , lastName(ln) , hasTable(ht){}
//另一种更好的做法，此外，我们标准string类来储存字符串，更为灵活方便，也更为安全专业
    // firstName = fn;
    // lastName = ln;
    // hasTable = ht;

void tableTennisPlayer::Name()  const{
    std::cout <<lastName<<" , "<<firstName<<'\n';
}

tableTennisPlayer::~tableTennisPlayer(){
    std::cout <<"白白咯～～"<<lastName << "  " <<firstName<<'\n';
}


//继承类的方法：
//构造函数的几个注意点：因为程序创建对象的时候，首先创建基类对象然后在创建继承类对象，因此必须有基类的构造函数
//如果：后面没有显示调用基类构造函数，那么会调用基类的默认构造函数
//
RatedPlayer::RatedPlayer(unsigned int r , const string & fn  , 
                                                    const string & ln  ,bool ht ) : tableTennisPlayer(fn , ln , ht)
{
    rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r , const tableTennisPlayer & tp)
        :tableTennisPlayer(tp) ,rating(r)
{
//第二种构造方法，调用了，基类的默认复制函数
}

RatedPlayer::~RatedPlayer()
{
    std::cout <<"白白咯～～～"<<std::endl;
}