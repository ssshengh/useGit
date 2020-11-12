#include "/home/shenheng/c1/study of c/usingClass/类的自动转换和强制类型转换/stonewt.cpp"
#include  <iostream>

void display (const stonewt & st , int n){
    for(int i = 0 ; i < n ; i++){
        std::cout <<"wow!";
        st.show_stn();
    }
}


int main(){
    stonewt incognito = 275;//先将int转化为了double,再调用第一个构造函数进行类型转换
    stonewt wolfe(285.7);//这种初始化等同于 wolfe = 285.7
    stonewt taft(21,8);
    
    std::cout <<"The incognito weight:";
    incognito.show_stn();
    std::cout <<"The wolfe weight:";
    wolfe.show_stn();
    std::cout <<"The taft weight:";
    taft.show_lbs();

    incognito = 276.8;
    taft =325;
    std::cout <<"After dinner the weight is changed.\n";
    std::cout <<"the incognito is :";
    incognito.show_stn();
    std::cout <<"The taft is :";
    taft.show_lbs();

    //注意重点！！！
    display(taft,2);
    display(422,2);//&st遇到一个int类型的变量寻找有没有一个只传入int的构造函数，没有的话就调用了传入double那个，再！！！转换为一个对象！！


    double p_wt = taft;
    std::cout <<p_wt<<" equals ";
    taft.show_stn();
}