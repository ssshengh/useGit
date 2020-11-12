#include <iostream>
#include "python3.8/Python.h"
#include <stdio.h>

int main(){
    using std::cout;
    using std::endl;
    int a = 521;
    int b = 125;
    int c = a + b;
    cout << "Standard exception: " <<c<<endl;

    // python is here
    //Py_SetPythonHome(L"/usr/bin/python3.8/");
    Py_Initialize();                          //初始化python解释器，告诉编译器要用的python编译器
    PyRun_SimpleString("print('hello word! my name is python')");       //调用python文件
    Py_Finalize();
}
//g++ -std=c++11 -ggdb3 -O0 -pedantic-errors -Wall -Wextra   -fpie $(python3-config --cflags --embed) -o 'test.out'   'test.cpp' $(python3-config --embed --ldflags)