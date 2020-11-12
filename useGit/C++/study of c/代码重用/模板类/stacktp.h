#ifndef  STACKTP_H_
#define STACKTP_H_

//模板类注意点：模板类的具体实现需要和声明在同一文件夹下
//                              模板类不能单独编译，一定要与特定实例化一起使用

template<typename Type>
class stacktp
{
private:
    enum{SIZE = 10};
    //Type item{MAX};
    int top;
    //改进后可以接收指针的版本：
    Type * items;
    int stackSize;
public:
    //stacktp();
    // bool isEmpty();
    // bool isFull();
    // bool push(const Type & item);
    // bool pop(Type & item);
    //改进后
    explicit stacktp(int ss = SIZE);
    stacktp(const stacktp & st);
    ~stacktp(){delete [] items ;}
    bool isEmpty(){return top == 0 ;  }
    bool isFull() {return top == stackSize  ;}
    bool push(const Type & item);
    bool pop(Type & item);
    stacktp& operator=(const stacktp & st);
};

template<typename T>
stacktp<T>::stacktp(int ss ) : stackSize(ss) , top (0)
{
    items = new T [stackSize];
}

//重载复制构造函数
template <class Type>
stacktp<Type>::stacktp(const stacktp & st){
    stackSize = st.stackSize;
    top = st.top;
    items = new Type [stackSize];
    for (int i = 0; i < top; i++)
    {
        items[i] = st.items[i];
    }
    
}

template<class T>
bool stacktp<T> :: push(const T & item){
    if (top<stackSize)
    {
        items[top++] = item;
        return true;
    }else
        return false;
    
}

template<class T> 
bool stacktp<T> :: pop(T & item){
    if (top > 0)
    {
        item = items[--top];
        return true;
    }else 
        return false;
    
}

template<class T> 
stacktp<T> & stacktp<T> :: operator=(const stacktp & st )//注意返回值类型和原型中不一样，原型中进行了缩写。
{
    if(this == &st)
        return *this;
    delete [] items;

    stackSize = st.stackSize;
    top = st.top;
    items = new T [stackSize];
    for (int i = 0; i < top; i++)
    {
        items[i] = st.items[i];

    }

    return *this;
    
}













#endif