#ifndef  VECTOR_H_
#define  VECTOR_H_
#include <iostream>

namespace VECTOR2dim
{
    class Vector2dim
    {
    public:
        enum Mode {RECT , POL};//直角坐标系还是极坐标系

    private:
        double x ;   //水平分量
        double y;   //垂直分量
        double length;  //矢量长度
        double  ang;      //角度，单位是度不是弧度
        Mode mode;

        //private methods 帮助设置私有值
        void setLen();
        void setAng();
        void setX();
        void setY ();
    public:
        Vector2dim();
        ~Vector2dim();

        Vector2dim(double n1 , double n2 , Mode mode = RECT);
        void reSet(double n1 , double n2 , Mode mode = RECT);

        //获取坐标值、角度以及长度
        double xval () const { return x;}
        double yval() const { return y;}
        double lenVal() const {return length;}
        double angVal() const {return ang;}

        //设置模式
        //设置为极坐标系
        void SetPolar();
        //设置为直角坐标系
        void SetRect();

        //重载运算符
        Vector2dim operator+ (const Vector2dim & v ) const ;
        Vector2dim operator- (const Vector2dim & v ) const;
        Vector2dim operator - () const ;
        Vector2dim operator *(double n) const ;

        //友元
        friend Vector2dim operator * (double n, const Vector2dim & v);
        friend std::ostream & operator<< ( std::ostream & os , const Vector2dim & v);

    };
    

} // namespace VECTOR2dim


#endif