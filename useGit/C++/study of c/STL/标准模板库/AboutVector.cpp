#include <iostream>
#include <vector>
#include <string>

template<typename T>
void show(std::vector<T> &  vv){
    for(auto it = vv.begin() ; it!=vv.end() ; it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}


const int NUM = 5;
int main()  {
    std::vector<int> counter = {1,2,3,4,5};
    std::vector<std::string>  name ={
        "Time",
        "IMSI",
        "cellID",
        "nxRV",
        "nxTx"
    };
    std::cout <<"the size of vector is :"<<counter.size()<<std::endl; 

    int sizeOfCounter = counter.size();//这里可以为double、long啥的
    int sizeOfName = name.size();
    
    if(sizeOfCounter == sizeOfName)
        for (int i = 0; i < sizeOfCounter; i++)
        {
                if(i%3 == 0)
                    std::cout << name[i]<<std::endl;//重载了[]
        }


    //迭代器的使用
    std::vector<std::string>::iterator itOfName ;//迭代器本质上是一个广义指针
    itOfName = name.begin();
    std::cout <<*(++itOfName)<<std::endl;

    name.push_back("Sisi");
    name.push_back("Hengheng");
    show(name);
    name.erase(name.begin() , name.begin() +3);//可以看见是左闭右开，不包含第四个元素
    //如果里面的元素改为itOfName的话，那么会内存泄漏，并不清楚为什么！！！！！！！！！！！！！！
    show(name);
}