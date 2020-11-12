#include <iostream>
//#include "/home/shenheng/c1/study of c/nameSpace/nameSP.h"
#include "/home/shenheng/c1/study of c/nameSpace/nameSp.cpp"//只导入h文件显示为定义，两个一起导入就重复定义了

void other(void);
void another(void);

int main() {
    using debts :: Debt;
    using debts :: showDebt;

    Debt golf = { {"Benny", "Gota"} , 120.0};
    showDebt(golf);

    other();
    another();

}

void other(void)
{
    using std::cout;
    using std::cin;
    using std::endl;

    using namespace debts;
    Person dg = {"Doodles", "Gliy"};
    cout<<endl;
    Debt zippy[3];
    int i;

    for(i = 0; i<3 ; i ++)
        getDebt(zippy[i]);
    
    for(i = 0 ; i<3 ; i ++)
        showDebt(zippy[i]);

    cout<< "Total Debts is :  $"<<sumDebts(zippy, 3)<<endl;
    return;
}

void another(void)
{
    using  pers::Person;
    Person Collector = { "Milo" , "Right"};
    pers::showPerson(Collector);
    std::cout<<std::endl;

}