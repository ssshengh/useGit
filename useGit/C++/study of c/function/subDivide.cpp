#include <iostream>
const int LEN = 66;//实际长度是65  第66个数用于存储结束符号
const int Divs = 6;//递归层数

void subDivide(char ar[] , int low , int high , int levl);

int main()
{
    char ruler[LEN];
    int i;

    for(i = 1 ; i< LEN -2 ; i++)
        ruler[i] = ' ';

    ruler[LEN - 1] = '\0';//字符串结束符号
    int min = 0;
    int max = LEN-2;

    ruler[min] = ruler[max ] = '|';
    std::cout<<ruler<<std::endl;
    //第一层，只有两个的时候

    for(i= 1 ; i<= Divs ; i++)
    {
        subDivide(ruler,min,max,i);//递归的在中间划线
        std::cout<<ruler<<std::endl;
        for(int j = 1 ;j < LEN-2 ; j++)
        {
            ruler[j] = ' ';

        }

    }
    return  0;

}

void subDivide(char ar[] , int low , int high , int levl)
//levl 控制递归层数，减少到1的时候结束递归
{
    if(levl == 0)
        return ;

    int mid = (high+low)/2;
    ar[mid] = '|';
    subDivide(ar,mid,high,levl-1);
    subDivide(ar,low,mid,levl-1);

}