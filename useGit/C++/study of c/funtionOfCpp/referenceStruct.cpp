#include <iostream>
#include<cstring>
//别忘了程序清单8.8

struct freeThrows
{
    std::string name;
    int made;
    int attempts;
    float percent;

};

/**
 * 为什么使用引用？
 *  double m = sqrt(16.0)    cout << sqrt(25.0);  实际上是先把4.0复制到一个临时位置，然后再赋值给m      然后把5复制到某个临时位置
 * 但用引用的话，效率会高很多
*/

/**
 * 注意的大问题！！！！
 * 函数返回一个指向临时变量的引用（newguy），函数运行完毕后将不再存在
 * 同样的，避免使用指向临时变量的指针
*/
// const freeThrows  & fr clone(freeThrows & ft)   
// {
//     freeThrows newguy;
//     newguy = ft;
//     return newguy;
//     这种是绝对不行的大问题，函数运行后，就没有它了，但如果函数头没有&的话
//将会生成一个临时的储存空间储存这个临时的变量，使得可以在main'里面赋值给某一个结构体  对类也一样

//     freeThrows * pt;
//     *pt = ft;
//     return  *pt;
//     这是一种解决办法
//     第一句声明了一个指向无名结构的指针pt，*pt就是该结构
//     上述代码似乎会返回该结构
//     但事实上，只是返回了这个结构的引用！！！！！！！！！！！！！！！
//     所以可以这么用
//     freeThrows  & jolly = clone(three);
// }
//容易忘记这被隐式new的空间






void display (const freeThrows & ft) ;
void setPc(freeThrows & ft);
freeThrows & accumulate (freeThrows & target , const freeThrows & source);


int main()
{
    freeThrows one = {"one" , 13 ,14};//都没有赋值percent，可以看见被令为了0
    freeThrows two =  {"two" , 10,16};
    freeThrows three = {"three",5,9};
    freeThrows four = {"four",10,100};
    freeThrows team = {"team" , 0 ,0};
    freeThrows dup ;//并没有初始化，全部变成0

    display(dup);//可以看到，打印出来的是随机赋值
    setPc(one);//由于ft是引用形参，所以实际上是设置了one.percent
    display(one);//显示内容，并不修改
    accumulate(team , one);//只修改了team ,并没有修改one
    display(team);

    //use return value as argument
    display(accumulate (team, two));//修改了team，由于accumulate是引用结构类型，所以其返回值其是就是team原值
    //等效于   accumulate(team,two)     +     display(team)

    accumulate(accumulate(team,three),four);//上述逻辑也可以用于这句
    display(team);

    dup = accumulate(team,four);//正如所预期的，team的值被赋值给了dup

    accumulate(dup,four) = four;//一种独特的赋值，但如果按值返回，就会编译错误！！！！！！！！！！！！！！！！！ 因为被赋值的拷贝不知道在那里




}


//利用const 防止误修改结构体
void display (const freeThrows & ft)    
{
    using std::cout;

    cout<<"Name : " <<ft.name<<'\n';
    cout<< " Made :" <<ft.made<<'\t';
    cout<<" Attmempts :" << ft.attempts<<'\t';
    cout<<" Percent : " << ft.percent << '\n';


}

void setPc(freeThrows & ft)
{
    if(ft.attempts != 0)
        ft.percent = 100.0f *float(ft.made)/float(ft.attempts);
    else
        ft.percent = 0;

    
}

//结构体引用函数，将原结构体添加到目的结构体
//返回的其是就是target原本的值的改变
//如果函数头没有&   那么返回值是target，即传入的team的拷贝！！！！！！！！！！！！！！
freeThrows & accumulate (freeThrows & target , const freeThrows & source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    setPc(target);
    return target;//光看这句话不能知道target是引用结构，但函数类型指明了这一点
}