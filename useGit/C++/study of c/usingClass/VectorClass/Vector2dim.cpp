#include "/home/shenheng/c1/study of c/usingClass/VectorClass/Vector2dim.h"
#include <cmath>

using std::sin ;
using std::cout ;
using std::sqrt ;
using  std::sin;
using std::atan; 
using std::atan2;
using std::cos;


namespace VECTOR2dim
{
    const double RadToDeg = 45/ atan(1.0);

    //private methods 
    void Vector2dim::setLen()
    {
        length = sqrt(x*x + y*y);
    }
    void Vector2dim::setAng()
    {
        if(x == 0.0 && y == 0.0)
            ang = 0.0;
        else
            ang = atan2(y,x);
    }
    void Vector2dim::setX(){
        x = length * cos(ang);
    }
    void Vector2dim::setY(){
        y = length * sin(ang);
    }

    //public methods
    Vector2dim::Vector2dim(){
        x = y = ang = length = 0.0;
        mode = RECT;
    }
    Vector2dim::Vector2dim(double n1, double n2 , Mode from){
        mode = from;
        if(from == RECT)
        {
            x = n1;
            y = n2;
            setLen();
            setAng();
        }
        else if(from == POL)
        {
            length = n1;
            ang = n2/RadToDeg;
            setX();
            setY();

        }
        else
        {
            cout<<" 并不正确的输入，即将重置坐标为00，坐标系重置为直角坐标"<<'\n';
            x=y=ang=length = 0;
            mode = RECT;
        }
        
        
    }

    //重置坐标系为直角坐标系（默认）或者极坐标系
    void Vector2dim::reSet(double n1 , double n2 , Mode from){
        mode = from;
        if(from == RECT)
        {
            x = n1;
            y = n2;
            setLen();
            setAng();
        }
        else if(from == POL)
        {
            length = n1;
            ang = n2/RadToDeg;
            setX();
            setY();

        }
        else
        {
            cout<<" 并不正确的输入，即将重置坐标为00，坐标系重置为直角坐标"<<'\n';
            x=y=ang=length = 0;
            mode = RECT;
        }
    }

    Vector2dim ::~Vector2dim(){
        cout<<" 俺走喽～～"<<'\n';
    }

    void Vector2dim::SetPolar(){
        mode = POL;
    }
    void Vector2dim::SetRect(){
        mode = RECT;
    }

    //重载运算符
    Vector2dim Vector2dim::operator+(const Vector2dim &v) const{
        return Vector2dim(x+v.x ,y+v.y);//很好的避免了对于极坐标系第二次写代码
    }
    Vector2dim Vector2dim::operator-(const Vector2dim & v) const {
        return Vector2dim(x-v.x, y-v.y);
    }

    //重置方向
    Vector2dim Vector2dim::operator-() const{
        return Vector2dim(-x,-y);
    }
    Vector2dim Vector2dim::operator*(double n) const{
        return Vector2dim(x*n,y*n);
    }

    //友元函数

    Vector2dim operator*( double n, const Vector2dim & v ){
        //参数顺序对调的话，就存在了二义性！！！！
        return v*n;
    }
    //注意，友元函数不再类的作用区域类，所以必须使用 Vector2dim::RECT，所以else也永远不会被执行
    std::ostream & operator<<(std::ostream &os , const Vector2dim & v)
    {
        if(v.mode == Vector2dim::RECT)
            os<<"(x,y) is : ("<<v.x<<" , "<<v.y<<")";

        else if(v.mode == Vector2dim::POL)
        {
            os<<"(L,a) is : ("<<v.length<<" , "<<v.ang*RadToDeg<<")";
        }
        else
        {
            os<<"Vector is invaliable";
        }
        return os;
        
    }


} // namespace VECTOR2dim
