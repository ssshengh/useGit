#ifndef  STOCK00_H_
#define STOCK00_H_
#include <string>


/**股票类
 *  \param company : 公司名字
 * \param shares : 股票数量
 * \param share_val : 股票支数
 * \param total_val : 股票总价值
 * 
*/
class Stock
{
private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    //设置总价
    void setTol(){ total_val = shares * share_val;}
    //内联函数，其被要求在每一个文件中都被定义，因此短小的最好直接放在类申明中，长一点的放在头文件中定义


public:
    Stock();//一般需要定一个默认构造函数，并赋予一定的值
    Stock(const std::string & co , long n , double pr);//和java一样，参数中不能直接为私有变量名字
    ~Stock();
    //获取股票价格信息
    //param: co为公司名称    n 股票支数   pr 股票价格
    void acquire(const std::string & co , long n , double pr);
    //买入股票
    //@param : num 买入支数      price 股票改变后的价格
    void buy(long num , double price);

    //售卖股票
    //@param : num 卖出支数   price 改变后的价格
    void sell(long num , double price);

    //更新股价
    //@param : price  更新后的价格
    void update(double price);

    //显示信息
    //只要类方法不修改对象，我们就定义为const，这样可以使得const对象可以调用它
    void show() const;

    /**
     * 用于比较两个对象的total的大小，可以定义一个，但是作为函数头被调用的对象难以称呼，因此出现了this指针
     * this指针本质上是一个指向函数头代表的对象的地址,这个函数中this指向一个const类型的stock对象，和结构体一样，对象也可以被这么用，如果是const的函数头，那this指向的对象将不可被改变
     * @param s: 用于和调用的对象比较的对象
     * @return  ：*this:指向一个Stock类型的对象。以.调用的话，那就是调用的那个对象
    */
   const Stock & topval(const Stock &s) const;

};

//public和友元函数可以访问私有变量

#endif