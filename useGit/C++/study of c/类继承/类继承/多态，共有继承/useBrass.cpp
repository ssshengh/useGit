#include "/home/shenheng/c1/study of c/类继承/类继承/多态，共有继承/brass.cpp"
# include <iostream>

int main(){
    Brass piggy("lla Pigg", 381299,4000.00);
    BrassPlus Hoggy("Hory Hoggy" , 382288 , 3000.00);
    //用对象调用
    piggy.viewAcct();
    Hoggy .viewAcct();

    std::cout <<"借个贷："<<'\n';
    Hoggy.Deposit(1000.0);
    Hoggy.viewAcct();
    std::cout <<"**********************取钱"<<'\n';
    Hoggy.WithDraw(300.84);
    Hoggy.viewAcct();


    const int CLIENTS = 4;
    //这是一个存储指针的指针数组，因此delete应该对每一个delete
    Brass * p_clients[CLIENTS];
    p_clients[0] = new Brass ("Jack Jone" , 5689522 , 25522.00);
    p_clients[1] = new BrassPlus("Das Hon" , 51412, 5000.00);
    p_clients[2] = new Brass();
    p_clients[3] = new BrassPlus();

    std::cout <<"**************** see 0"<<'\n';
    p_clients[0] ->viewAcct();
    std::cout <<"**************** see 1"<<'\n';
    p_clients[1]->viewAcct();
    std::cout <<"**************** see 2"<<'\n';
    p_clients[2]->viewAcct();
    std::cout <<"**************** see 3"<<'\n';
    p_clients[3]->viewAcct();

    for (int i = 0; i < CLIENTS; i++)
    {
        delete p_clients[i];
    }
    //虚析构使得我们可以调用对应于指针指向的类型的析构函数
    //如果不是虚的那将会只调用对应于指针类型的析构函数，那将是只是BRASS类的析构，静态联编

    //静态联编：编译时，确认调用的究竟是哪个代码块，但现在已经很难了，因为virtual使得编译器无法确定到底是哪个的方法
    //所以现在使用动态联编：
        //现在先说说指针和引用类型的兼容性：可以从上面的指针数组中看出，我们定义的Brass类型的指针可以指向继承类，这成为继承类的向上类型转换
        //  而如果是反过来的话，除非显示的转换，一般是禁止向下类型转换的，因为逆了is-a关系，而且一般也不安全，比如一个empolyer类派生了一个singer类，允许向下隐形转换的话，可能会将指向singer的指针指向了employee的地址，并用这个地址调用singer的方法，employee也有这个方法的话，救出问题了
    //动态联编通过virtual使得编译器可以在运行的时候，通过指针指向的对象的地址而不是指针的类型，确认是哪个对象
    //为什么还需要静态联编呢？这是C++的原则问题：不要为不使用的特性付出代价——————>在继承类中重新使用基类的方法时，尽量设置为虚的

    //编译器处理虚函数的方法：给每个对象添加了一个隐藏成员——虚函数表

    //虚函数的注意事项
        //构造函数不能虚
        //析构函数，只要是基类就显示声明一个虚的，不然会调用默认的静态联编
        //友元不能虚，因为不是类成员
        //如果派生类没有重新定义函数，那将会使用基类版本
        //如果派生类重新定义函数时，改变了参数列表，那该方法会彻底覆盖基类方法，使得基类方法无法调用
            //如果是要重新定义基类中的方法，那一定要和原来的原型一模一样，除非是返回值是指针的类型，可以指向基类的指针改为指向继承类
            //如果是基类中重载了方法，那继承类中应该重新定义所有的方法，不然会隐藏其他基类的方法
}