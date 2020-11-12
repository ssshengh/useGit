#include "/home/shenheng/c1/study of c/usingClass/类的自动转换和强制类型转换/stonewt.h"
#include <iostream>
using std::cout;

stonewt::stonewt(double lbs){
    stone = int(lbs) / LBS_PER_STN;    //强制将double类型转变为int，失去一些精度
    pdsLeft = int(lbs) % LBS_PER_STN + lbs - int(lbs);  //将int上升为double
    pounds = lbs;
}

 stonewt::stonewt(int stn, double lbs){
    stone = stn;
    pdsLeft = lbs;
    pounds = stn * LBS_PER_STN + lbs;  //石转化为磅
}

stonewt::stonewt(){
    stone = pounds = pdsLeft =0;
}

stonewt::~stonewt(){
    std::cout <<"Bye~~~"<<'\n';
    
}

void stonewt::show_lbs() const {
    std::cout <<pounds<<" pounds \n";
}
void stonewt::show_stn() const{
    std::cout <<stone<<" stone, "<<pdsLeft<<" pounds \n";
}

stonewt::operator double() const {
    return pounds;
}
stonewt::operator int() const {
    return int (pounds + 0.5);
}