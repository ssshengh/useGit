#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;

class stack
{
private:
    enum{MAX = 10};//默认的枚举底层是int类型，其作用域为整个类，但不会创建数据成员，此外为了解决类里面枚举里有相同元素的，注意作用域内枚举
    //在类里面定义常量还可以用static const存到静态区里去，单纯的const并不行
    Item items[MAX];
    int top;
public:
    stack();
    ~stack();

    bool isEmpty() const;
    bool isFull() const;

    bool push(const Item & item);

    bool pop(Item & item);
};


#endif