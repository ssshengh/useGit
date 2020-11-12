#include "/home/shenheng/c1/study of c/代码重用/包含对象成员的类/11/studentc.cpp"

#include <iostream>

using std::endl;
using std::cin;

void
set(studentc & stu , int n);

const int pupils = 3;
const int quizzes = 5;//课的数目

int main() {
    studentc ada[pupils] = {
        studentc(quizzes), studentc(quizzes) , studentc(quizzes) 
    };

    int i;
    for(i = 0 ; i<pupils ; i++)
        set(ada[i], quizzes);
    std::cout <<"\n Students' List : \n";
    for(i = 0 ; i<pupils ; i++)
        std::cout <<ada[i].Name()<<endl;
    std::cout<<"\n Results :";

    //std::cout <<ada[i].Average()<<endl; 加上这句就会调用不知名内存，有可能因为，i其是在for里是被拷贝了来改变的，原本的i并没有值

    for (int j = 0; j < pupils; ++j)
    {
        std::cout <<endl << ada[j];
        std::cout <<"average: " <<ada[j].Average()<<endl;
    }
    

}


void
set(studentc & stu , int n){
    std::cout <<"Please enter student's name :";
    getline(cin , stu);//注意，这里是重载了的getline函数
    std::cout <<"Please enter "<<n<<"quiz scrores :\n";
    for(int i = 0 ; i< n ; i++)
        cin>>stu[i];//注意这两个运算符均被重载了
    while(cin.get() != '\n')
        continue;

}