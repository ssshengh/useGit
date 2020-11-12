#ifndef  STONEWT_H_
#define STONEWT_H_

//这个类可以将榜转换为英石

class stonewt
{
private:
    enum{LBS_PER_STN = 14};   //每石14磅
    int stone;                                      //总石数
    double pdsLeft;   //部分磅
    double pounds;  //磅里的总重
public:
    //只有一个参数的构造函数，可以用于类的隐式转换，对于另一个传入两个参数的构造函数就不能使用转换类型
    stonewt(double lbs);
    //然而如果第二个参数能够被给予一个默认值，那类的对象就可以用来转换int，但是这并不总是好的，会有意外的类型转换，c++使用explicit来禁止隐式转换
    //但仍然可以显式转换
    explicit stonewt(int stn , double lbs = 0);
    stonewt();
    ~stonewt();
    void show_lbs() const;
    void show_stn() const;

    //转换函数，用于将对象转换为基本类型
    operator int() const;
    operator double() const;

};

#endif