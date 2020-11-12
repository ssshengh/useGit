
template <typename AnyType>
void swap (AnyType &a , AnyType &b)
{
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}

//Override
template <typename AnyType>
void swap(AnyType &a , AnyType &b, int c)   
{
    AnyType temp;
    for (int i = 0; i < c; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
    
}