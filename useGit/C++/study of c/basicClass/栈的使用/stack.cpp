#include "/home/shenheng/c1/study of c/basicClass/栈的使用/stack.h" 

stack::stack()
{   
    top = 0;
}

stack::~stack()
{
}

bool stack::isEmpty() const{
    return top == 0;
}

bool stack::isFull() const{
    return top == MAX;
}

bool stack::push(const Item & item)
{
    if(top < MAX)
    {
        items[top++] = item;
        return true;
    }else
        return false;
}

bool stack::pop(Item &item){
    if (top>0)
    {
        item = items[--top];//关键！！！！！ 用的前缀--
        return true;
    }else
        return false;
    
}