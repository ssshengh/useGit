#include "/home/shenheng/c1/study of c/usingClass/VectorClass/Vector2dim.cpp"

//原则：如果一个方法最后得到了一个新的对象，应该首先考虑能不能使用构造函数。这能保证得到的对象格式是正确的

int main(){
    using std::cout;
    
    VECTOR2dim::Vector2dim v1 (3.0 , 4.0);
    VECTOR2dim::Vector2dim v2 (26.0,30.0,VECTOR2dim::Vector2dim::Mode::POL);//注意枚举的调用

    using namespace VECTOR2dim;
    cout<<v1<<'\n';
    cout<<v2<<'\n';

    // cout<<""

}