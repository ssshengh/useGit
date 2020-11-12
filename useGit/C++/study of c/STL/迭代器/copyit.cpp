#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

void output (const std::string  s){std::cout << s << " ";}

int main(){
    int casts[12] = {6,5,8,4,82,52,651,3,5,1,4};
    std::vector<int >  dice (12);//如果是10就会内存泄漏，因为copy并不考虑根据拷贝的值来调整目标容器的长度
    std::copy(casts , casts+12 , dice.begin());//copy前两个参数确定要复制的元素的范围，第三个参数是表示要复制到什么位置，前两个参数最好是输入迭代器，第三个最好是输出迭代器
    //这里会覆盖dice里面的内容
    std::cout << "接下来看看是否拷贝成功，使用输出迭代器，利用cout输出到屏幕："<<std::endl;
    std::ostream_iterator <int , char> out_iter (std::cout, "$");//第一个模板参数是输入的发送给输出流的类型，第二个是输出流使用的字符类型，另一种选择是wchar_t_
                                                                                                                        //第一个参数是ostream对象，第二个是分隔符
    std::cout <<"首先把输出的内容拷贝到流中 ："<<std::endl;
    std::copy(dice.begin() , dice.end()-1 , out_iter);//可以看出超尾最后的元素用0来填充，或者超出了向量的范围，那么就只能把拷贝过去额多余空间用0满上，也不止0，填充了随机数
    //至少防止了溢出
    std::cout <<'\n';
    std::cout <<"使用反向迭代器，注意方向：\n";
    std::copy(dice.rbegin() , dice.rend() , out_iter);
    std::cout <<"\n***************接下来使用定义的反向迭代器*****************\n";
    std::vector<int>::reverse_iterator ri;
    for(ri = dice.rbegin() ; ri != dice.rend() ; ri++)
        std::cout << *ri <<" ";
    std::cout <<'\n';


    std::cout <<"***************最关键的可能是，能用函数就尽量不要显式声明迭代器，避免犯错******************"<<'\n';
    std::string s1[4] ={"f1", "f2" , "f3" , "f4"};
    std::string s2[2] = {"b1" , "b2"};
    std::string s3[2] = { "s1" , "s2"};
    std::vector<std::string> words(4);
    std::copy(s1 , s1+4 , words.begin());
    std::cout <<"***************使用foreach输出***************"<<'\n';
    std::for_each(words.begin() , words.end(), output);//只能是函数
    std::cout <<'\n';

    std::copy(s2 , s2+2 , std::back_insert_iterator<std::vector<std::string>> (words));  
    //std::back_insert_iterator<std::vector<std::string>>  iter(words)       是一个只允许用于在尾部快速插入的容器，必须用容器类型声明，以便使用对应方法，此外用容器初始化
    std::for_each(words.begin() , words.end() , output);//可以看见，并未覆盖，而是在尾部插入了
    std::cout <<'\n';
    std::copy(s3 , s3+2 , std::insert_iterator<std::vector<std::string>> (words , words.begin()+1));//随机插入还需要一个指示插入位置的参数
    std::for_each(words.begin() , words.end() , output);//可以看见，并未覆盖，而是在头部过一个插入了
    std::cout <<'\n';   
    
}
