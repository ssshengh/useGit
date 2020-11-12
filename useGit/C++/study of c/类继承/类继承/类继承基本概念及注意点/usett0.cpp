#include "/home/shenheng/c1/study of c/类继承/类继承/类继承基本概念及注意点/tableTenn0.cpp"
#include <iostream>

//派生类和基类之间有三个关系：派生类对象可以使用基类的方法、二是基类指针可以在不进行显式转换的情况下指向派生类对象、三时能将基类对象初始化为派生类对象
void show(const tableTennisPlayer & rt){
    std::cout <<"Name :";
    rt.Name();
    std::cout <<" \n table:";
    if(rt.HasTable())
        std::cout <<"yes\n";
    else
        std::cout <<"No\n";
}//有趣的地方在于在里，如果我们传入一个派生类对象，那该函数也能正确执行


int main(){
    tableTennisPlayer player1("淼淼", "龙" , true);
    tableTennisPlayer player2("横横" , "申" , false);
    player1.Name();
    player2.Name();

    RatedPlayer rplayer1(140,   player1 );
    RatedPlayer rplayer2(140, "aaa" ,"my" , true);
    //引用的兼容性让我们可以用派生类初始化基类对象
    tableTennisPlayer olaf(rplayer2);//匹配的构造函数是tableTennisPlayer(RatePlayer &)并没有定义这个构造函数，但是，有参数是tableTennisPlayer &的，可以看出了原因了，和上面一样

    rplayer1.Name();
    std::cout <<rplayer2.RateGet()<<" is the grades";   

    // RatedPlayer * pr1 = player1;
    // RatedPlayer &rr  = player1;  不可以将派生类的指针指向基类
    tableTennisPlayer *pr = &rplayer1;
    tableTennisPlayer &rr = rplayer1;//引用也可以
}