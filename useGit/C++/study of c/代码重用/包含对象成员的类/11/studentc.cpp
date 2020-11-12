#include "/home/shenheng/c1/study of c/代码重用/包含对象成员的类/11/studentc.h"

double studentc::Average() const {
    if(scores.size() > 0)
        return scores.sum()/scores.size();
        //这样调用成员对象的接口
    else
        return 0;
}

const std::string & studentc:: Name() const{
    return name;
}



double & studentc::operator [] ( int i ){
    return scores[i];  //use  valarray<double> :: operator []()
}
double studentc::operator[](int i ) const{
    return scores [i];
}

//private
std::ostream & studentc::arr_out(std::ostream & os ) const{
    int i ;
    int lim = scores.size();

    if (lim>0)
    {
        for ( i = 0; i < lim; i++)
        {
            os<<scores[i]<<" ";
            if(i % 5 == 4)
                os<<std::endl;
        }
        if(i % 5 != 0)
            os<<std::endl;

        
    }
    else
        os << "empty array " ; 
    return os;
    
}

//friends
//输入的只能是name
std::istream & operator>>(std::istream & is , studentc & stu){
    is>>stu.name;
    return is;
}

std::istream & getline(std::istream & is , studentc & stu){
    getline(is , stu.name);
    return is;
}

std::ostream & operator<<(std::ostream & os , const studentc &stu){
    os<< "Scores for " << stu.name << ":\n";
    stu.arr_out(os);
    return os;
}

studentc::~studentc(){
    std::cout <<"Bye~~~"<<name<<std::endl;
}